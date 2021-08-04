//  VAM --- Video Assisted Measurement of Animals
//	Copyright( C ) 2016  Márton Szemenyei  

//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	( at your option ) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.

#pragma warning(push, 0)
#include <torch/script.h>
#include <torchvision/vision.h>
#pragma warning(pop)
#include "MarkerWindow.h"
#include <qpainter.h>
#include <qscrollbar.h>

// This has to defined here, since including the torch header in the header messes with Qt (they both define slot, but differently)
static torch::jit::script::Module model;

MarkerWindow::MarkerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// default values
	unmarkedID = new QStringListModel();
	currentProject = NULL;

	imgIndices.resize(VAMMaxVideos);
	pointIndices.resize(VAMMaxVideos);

	// Load neural net
	try {
		// Deserialize the ScriptModule from a file using torch::jit::load().
		
		model = torch::jit::load("./model.pt");
		model.eval();

		// Read model definition
		QFile model_def("./model_def.txt");

		if (!model_def.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("Model definition"),
				tr("Model definition file 'model_def.txt' not found."));
		}

		QTextStream in(&model_def);

		// Read up header line and the line of the filename
		auto numbers = in.readLine().split(",");
		for (auto number : numbers)
		{
			keypointDefs.push_back(number.toInt());
		}

		NNLoaded = true;
		VAMLogger::log("NN Loaded");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		QMessageBox::warning(this, tr("No model"), tr("The neural network model is not found. Automatic keypoint detection will be disabled."));
		//QMessageBox::warning(this, tr("No model"), e.what());
		NNLoaded = false;
		VAMLogger::log("NN Load failed");
	}

	// Setup window
	resetWindow();
}


MarkerWindow::~MarkerWindow(void)
{
	// Delete model
	delete unmarkedID;
}

void MarkerWindow::show()
{
	// Read image - otherwise show crashes
	VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
	currentImg = imgRead(ImgPathList[imgIdxMap[currentImgIndex]], currentMeasurement.getA()[imageIdx], currentMeasurement.getD()[imageIdx]);

	// Fill image with black if faild to load
	if (!currentImg.data)
		currentImg = cv::Mat(cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()), CV_8UC1, cv::Scalar(0, 0, 0));
	
	// Call parent function
	QMainWindow::show();

	// Display image (if not called the image size will be wrong)
	showImage();
}


void MarkerWindow::resetWindow()
{
	// setup UI
	ui.setupUi(this);

	// Default values
	measurementModified = false;
	measData = false;
	markerSelectionMode = false;
	currentDBIdx = 0;
	currentSchemaIdx = 0;
	currentImgIndex = 0;
	currentPointIndex = 0;
	imgCntThresholds.resize(4, 0);
	scale = 1;
	selectedIdx = -1;
	measurementName = QString("");

	// Enable crosshair
	ui.imageLabel->paintCrosshair = true;

	// Set tip for marker selection
	ui.tipLabel->setText(markerSelectionMode ? VAMTranslatedStrings::measTipMove() : VAMTranslatedStrings::measTipZoom());

	// Connect signals and slots for the UI
	connect(ui.actionSave, &QAction::triggered, this, &MarkerWindow::saveMeasurement);
	connect(ui.actionSave_as, &QAction::triggered, this, &MarkerWindow::saveAsMeasurement);
	connect(ui.actionSelection_mode, &QAction::triggered, this, &MarkerWindow::markerModeChanged);
	connect(ui.actionPrevious_Image, &QAction::triggered, this, &MarkerWindow::prevImage);
	connect(ui.actionNext_image, &QAction::triggered, this, &MarkerWindow::skipImage);
	connect(ui.imagesRemList, &QListView::doubleClicked, this, &MarkerWindow::listDoubleClicked);
	connect(ui.actionErase_points, &QAction::triggered, this, &MarkerWindow::redoImage);
	connect(ui.actionDone, &QAction::triggered, this, &MarkerWindow::close);

	connect(ui.autoCorrection, &QCheckBox::stateChanged, this, &MarkerWindow::autoCorrChanged);

	connect(ui.confBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MarkerWindow::confidenceChanged);

	connect(ui.imageLabel, &CustomLabel::mousePressed, this, &MarkerWindow::imageClicked);
	connect(ui.imageLabel, &CustomLabel::mouseMoved, this, &MarkerWindow::imageHovered);

	connect(ui.imageScrollArea, &CustomScrollArea::wheelTurned, this, &MarkerWindow::resizeImage);

	// Add image label to the scroll area
	ui.imageScrollArea->setWidget(ui.imageLabel);
	//ui.imageScrollArea->setWidgetResizable( true );

	// Set focus
	setFocusPolicy(Qt::StrongFocus);
	this->setFocus();

	// Setup window buttons
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
}

void MarkerWindow::setupUI()
{
	// Setup string list and list view
	unmarkedID->setStringList(IDList);
	ui.imagesRemList->setModel(unmarkedID);

	// Hide rows that are finished
	for (int i = 0; i < currentMeasurement.getMarked().size(); i++)
	{
		//ui.imagesRemList->setRowHidden(i, currentMeasurement.getMarked()[i]);
		if(currentMeasurement.getMarked()[i])
			unmarkedID->setData(unmarkedID->index(i), IDList[i] + VAMTranslatedStrings::doneStr());
	}

	ui.imageLabel->setAlignment(Qt::AlignCenter);

	// Setup checkbox
	bool temp = measurementModified;
	ui.autoCorrection->setChecked(currentMeasurement.getAutoCorrect());
	measurementModified = temp;
}

void MarkerWindow::saveMeasurement()
{
	if (measurementName.isEmpty())
	{
		// Prompt for file
		measurementName = /*QFileDialog::getSaveFileName( this, tr( "Save Measurement" ),*/ currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas"/*, tr( "VAM Measurement (*.meas)" ) )*/;

		if (measurementName.isEmpty())
			return;

		VAMLogger::log("New meas save");

		// Notify main window of new measurement
		emit newData();
	}

	VAMLogger::log("Meas save");

	// Save measurement
	currentMeasurement.save(measurementName);

	currentProject->addMeasurement(currentMeasurement);
	emit dataUpdate();

    std::remove((measurementName + ".tmp").toStdString().c_str());
	measurementModified = false;
}

void MarkerWindow::saveAsMeasurement()
{
	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isMeasNew, currentProject, _1);
	if (!getName(tr("New Measurement"), tr("Enter Name:"), tr("Please specify a name!"), tr("A measurement with this name already exists!"), text, func))
		return;

	// Set new measurement name
	currentMeasurement.setName(text);
    
    QString oldName = measurementName;

	// Prompt for file
	measurementName = /*QFileDialog::getSaveFileName( this, tr( "Save Measurement" ),*/ currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas"/*, tr( "VAM Measurement (*.meas)" ) )*/;

	if (measurementName.isEmpty())
		return;

	VAMLogger::log("Meas save as");

	// Notify main window of new measurement
	emit newData();

	// Save measurement
	currentMeasurement.save(measurementName);

	currentProject->addMeasurement(currentMeasurement);
	emit dataUpdate();
    
    std::remove((oldName + ".tmp").toStdString().c_str());
	measurementModified = false;
}

void MarkerWindow::confidenceChanged(int val)
{
	// Only if there is a valid measurement
	if (currentMeasurement.getCnt() && !imgIdxMap.empty() && currentMeasurement.getConfidence(imgIdxMap[currentImgIndex]) != val)
	{
		// Modify measurement
		measurementModified = true;

		// Set confidence
        currentMeasurement.setConfidence(imgIdxMap[currentImgIndex], val);
        currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" +".tmp");

		VAMLogger::log("Confidence set");
	}
}

void MarkerWindow::markerModeChanged()
{
	// Toggle mode
	markerSelectionMode = !markerSelectionMode;

	VAMLogger::log("Marker mode: " + QString::number(markerSelectionMode));

	// Tell the image label whether to draw the crossheir
	ui.imageLabel->paintCrosshair = !markerSelectionMode;

	// Show the selection tip
	ui.tipLabel->setText(markerSelectionMode ? VAMTranslatedStrings::measTipMove() : VAMTranslatedStrings::measTipZoom());

	// Reset selection
	selectedIdx = -1;

	// Redraw markings
	drawMarkings();
}

void MarkerWindow::autoCorrChanged(bool val)
{
	// Modify measurement
	measurementModified = true;
    currentMeasurement.setAutoCorrect(val);
    currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" +".tmp");

	VAMLogger::log("Auto corr: " + QString::number(val));

}

Measurement MarkerWindow::getCurrentMeasurement() const
{
	return currentMeasurement;
}

bool MarkerWindow::setCurrentMeasurement(const Measurement &value, bool schemdbChange)
{

	VAMLogger::log("Set current measurement");

	// Setup variables
	currentMeasurement = value;
	measurementName = currentMeasurement.getFileName();

	// Get index of the database and the schema used
	currentDBIdx = currentProject->getDBList()->stringList().indexOf(currentMeasurement.getDB().getName());
	currentSchemaIdx = currentProject->getSchemaList()->stringList().indexOf(currentMeasurement.getSchema().getName());

	// Exit if there's something wrong and they don't exist (This should never happen, since the main window checks this too)
	if (currentDBIdx < 0 || currentSchemaIdx < 0)
	{
		VAMLogger::log("No schema or DB. THIS IS BAD... THIS SHOULD NEVER HAPPEN");

		QMessageBox::critical(this, tr("Error"), tr("The schema or the database used by this measurement is not loaded."));
		this->close();
		return false;
	}

	// Get current schema and DB
	currentSchema = currentProject->getSchema(currentSchemaIdx);
	currentDB = currentProject->getDB(currentDBIdx);

	// Check NN vs schema point defs
	auto ptCnts = currentSchema.pointCounts();
	int ptSize = 0;
	for (int i = 0; i < ptCnts.size(); i++)
	{
		if (ptCnts[i] == 0)
			break;
		ptSize++;
	}
	if (ptSize != keypointDefs.size())
	{
		NNLoaded = false;
		VAMLogger::log("Number of Images doesn't match. NN Disabled.");
	}
	else
	{
		for (int i = 0; i < keypointDefs.size(); i++)
		{
			if (ptCnts[i] != keypointDefs[i])
			{
				NNLoaded = false;
				VAMLogger::log("Number of points doesn't match. NN Disabled.");
				break;
			}
		}
	}

	// Read camera files
	std::vector<cv::Mat> A(currentDB.getVideoCnt()), d(currentDB.getVideoCnt());
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
	{
		cv::FileStorage fs((currentProject->getAbsProjLib() + "/Database/cam" + QString::number(i) + ".yaml").toStdString(), cv::FileStorage::READ);
		fs["cam"] >> A[i];
		fs["dist"] >> d[i];
	}
	currentMeasurement.setA(A);
	currentMeasurement.setD(d);

	// Read Image lists
	IDList = QStringList(currentDB.getIDs());
	ImgPathList = QStringList(currentDB.getImages());
    
    if (IDList.size() != ImgPathList.size())
    {
        VAMLogger::log("Corrupt DB");
        QMessageBox::critical(this, tr("Error: Corrupt Database"), tr("The Database file has been corrupted. Please fix the still database!"));
        return false;
    }

	// Check if image files exist
	for (QString imgPath : ImgPathList)
	{
        if (!VAMFileAgent::openFile(imgPath))
		{
			VAMLogger::log("Missing images");
			QMessageBox::critical(this, tr("Error: Image files missing"), tr("One or more image files are missing from the hard drive. Please fix the still database!"));
			return false;
		}
	}

	// Get image counts
	for (int i = 1; i < VAMMaxVideos; i++)
	{
		imgCntThresholds[i] = imgCntThresholds[i - 1] + currentDB.getCnt(toIdx(i - 1));
	}
	imgCnt = currentDB.getCnt();

	// See if there's data in the measurement
	measData = false;

	for (int i = 0; i < currentMeasurement.getMarkedCnt(); i++)
	{
		if (currentMeasurement.getFirstUnset(i) != 0)
		{
			measData = true;
			break;
		}
	}

	// Check if the database or the schema have changed ---- NOTE: both functions return true if measData if false
	bool dbDiff = dataBaseChanged();
	bool schDiff = schemaChanged();


	VAMLogger::log("Current meas new: " + QString::number(!measData) + " db changed: " + QString::number(dbDiff) + " schema changed: " + QString::number(schDiff));

	// If yes, then setup the markings (if measData was false, then default markings will be created)
	if (dbDiff || schDiff)
	{
		for (int i = 0; i < VAMMaxVideos; i++)
		{
			currentMeasurement.setPoints(currentSchema.pointModels[i]->stringList(), toIdx(i));
		}
		setupMarkings();
	}

	// Setup remaining variables
	currentImgIndex = 0;
	currentPointIndex = 0;
	imgDone = currentMeasurement.getMarkedCnt();
	imgRem = imgCnt - imgDone;

	// If the measurement was modified we set the flag
	measurementModified = measData && (dbDiff || schDiff || schemdbChange);

	// Setup image index map
	imgIdxMap.resize(0);
	if (VAMOptions::VAMImageOrderingType == OrderByAnimal)
	{
		std::vector< std::vector< int >> v(VAMMaxVideos);

		int maxSize = 0;
		for (int i = 0; i < VAMMaxVideos; i++)
		{
			int currSize = currentDB.getCnt(toIdx(i));
			v[i].resize(currSize);
			std::iota(v[i].begin(), v[i].end(), imgCntThresholds[i]);
			if (currSize > maxSize)
			{
				maxSize = currSize;
			}
		}


		for (size_t n = 0; n < maxSize; ++n)
		{
			for (int i = 0; i < VAMMaxVideos; i++)
			{
				if (n < v[i].size()) imgIdxMap.push_back(v[i][n]);
			}
		}

		/*// Setup new vectors
		std::vector< QString > tempP( currentDB.getCnt() ), tempID( currentDB.getCnt() );
		for( int i = 0; i < currentDB.getCnt(); i++ )
		{
			tempP[ i ] = ImgPathList.at( imgIdxMap[ i ] );
			tempID[ i ] = IDList.at( imgIdxMap[ i ] );
		}

		// Setup new lists
		ImgPathList.clear();
		IDList.clear();
		for( int i = 0; i < currentDB.getCnt(); i++ )
		{
			ImgPathList.push_back( tempP[ i ] );
			IDList.push_back( tempID[ i ] );
		}*/
	}
	else
	{
		imgIdxMap.resize(currentDB.getCnt());
		std::iota(imgIdxMap.begin(), imgIdxMap.end(), 0);
	}

	// Setup UI
	setupUI();

	return true;
}

Project *MarkerWindow::getCurrentProject() const
{
	return currentProject;
}

void MarkerWindow::setCurrentProject(Project *value)
{
	currentProject = value;
}

void MarkerWindow::adjustScrollBar(QScrollBar *scrollBar, double factor, double pos)
{
	// If the zoom scale changed by factor, we multiply the current position by it
	scrollBar->setValue(int(factor * scrollBar->value()
		// And offset it according to the center of the zooming
		+ ((factor - 1) * scrollBar->pageStep() * pos)));
}

void MarkerWindow::resizeImage(double factor, QPointF pos)
{
	VAMLogger::log("Resize");

	// If there's no image, we return
	if (!ui.imageLabel->pixmap())
	{
		scale = 1;
		return;
	}

	// We don't allow more than 3x zoom 
	if (scale * factor > 3)
	{
		return;
	}

	// We don't allow zooming out either
	if (scale * factor < 1)
	{
		factor = 1.0 / scale;
		scale = 1;
	}
	else // Adjust scale
		scale *= factor;

	VAMLogger::log("Scale: " + QString::number(scale));

	// Adjust x and y scrollbars
	adjustScrollBar(ui.imageScrollArea->horizontalScrollBar(), factor, pos.x() / ui.imageScrollArea->size().width());
	adjustScrollBar(ui.imageScrollArea->verticalScrollBar(), factor, pos.y() / ui.imageScrollArea->size().width());

	// Draw markings
	drawMarkings(factor);
}

void MarkerWindow::closeEvent(QCloseEvent *event)
{
	// Prompt for save if the measurement was modified
	if (measurementModified)
	{
		VAMLogger::log("Prompt for measurement save");
		QMessageBox msgBox;
		msgBox.setText(tr("The current measurement has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Save");
			saveMeasurement();
			emit closed();
			event->accept();
		}
		else if (ret == QMessageBox::Cancel)
		{
			VAMLogger::log("Cancel");
			event->ignore();
			return;
		}
		else
		{
            VAMLogger::log("Discard");
            std::remove((measurementName + ".tmp").toStdString().c_str());
			emit closed();
			event->accept();
		}
	}
	else
	{
		VAMLogger::log("Bye");
		emit closed();
		event->accept();
	}
	// Destroy window (A window is alays created using new)
	delete this;
}

void MarkerWindow::keyPressEvent(QKeyEvent *event)
{

	// We only handle key events in selection mode and if there is a selected marker
	if (markerSelectionMode && selectedIdx > -1)
	{
		VAMLogger::log("Key press: " + QString::number(event->key()));

		// Get values equivalent of one pixel on the image
		double xPix = 1.0 / (double)ui.imageLabel->size().width();
		double yPix = 1.0 / (double)ui.imageLabel->size().height();

		// Get position of the selected mark
		Point currPt = currentMeasurement.getMark(imgIdxMap[currentImgIndex], selectedIdx);

		switch (event->key())
		{
			// Undo selection
		case Qt::Key_Escape:
			selectedIdx = -1;
			break;
		case Qt::Key_Backspace:
			// Delete
			removePoint();
			break;
		case Qt::Key_Delete:
			// Delete
			removePoint();
			break;
		case Qt::Key_A:
			// Move point
			currPt.x -= xPix;
			currentMeasurement.setMark(currPt, imgIdxMap[currentImgIndex], selectedIdx);
			measurementModified = true;
			break;
		case Qt::Key_D:
			// Move point
			currPt.x += xPix;
			currentMeasurement.setMark(currPt, imgIdxMap[currentImgIndex], selectedIdx);
			measurementModified = true;
			break;
		case Qt::Key_W:
			// Move point
			currPt.y -= yPix;
			currentMeasurement.setMark(currPt, imgIdxMap[currentImgIndex], selectedIdx);
			measurementModified = true;
			break;
		case Qt::Key_S:
			// Move point
			currPt.y += yPix;
			currentMeasurement.setMark(currPt, imgIdxMap[currentImgIndex], selectedIdx);
			measurementModified = true;
			break;

		}
        currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" +".tmp");
		// Update marker draing
		drawMarkings();
	}
}

void MarkerWindow::resizeEvent(QResizeEvent * event)
{
	// Update marker drawings
	drawMarkings();
}


void MarkerWindow::prevImage()
{
	VAMLogger::log("Prev img: " + QString::number(currentImgIndex));
	// Decrease image cntr
	currentImgIndex--;
	// Display image
	showImage(true);
}

void MarkerWindow::skipImage()
{
	VAMLogger::log("Next img: " + QString::number(currentImgIndex));
	// Increase image cntr
	currentImgIndex++;
	// Display image
	showImage(true);
}

void MarkerWindow::listDoubleClicked(QModelIndex curr)
{
	VAMLogger::log("Next img: " + QString::number(currentImgIndex));
	// Increase image cntr
	currentImgIndex = curr.row();
	// Display image
	showImage();
}

void MarkerWindow::redoImage()
{
	VAMLogger::log("Reset img: " + QString::number(currentImgIndex));

	// Undo marked status
	currentMeasurement.setMarked(imgIdxMap[currentImgIndex], false);

	// Show in list of remaining images
	ui.imagesRemList->setRowHidden(imgIdxMap[currentImgIndex], false);
	unmarkedID->setData(unmarkedID->index(imgIdxMap[currentImgIndex]), IDList[imgIdxMap[currentImgIndex]]);
	

	// If the image was finished, adjust counters
	if (currentMeasurement.getFirstUnset(imgIdxMap[currentImgIndex]) == -1)
	{
		VAMLogger::log("It was finished");
		imgRem++;
		imgDone--;
	}

	// Modified
	measurementModified = true;

	// Get point cound --- NOTE: Etalon images always have two points
	int pCnt = currentSchema.pointCnt(getImageIdx(imgIdxMap[currentImgIndex]));
	if (hasEtalon(true))
		pCnt += 2;
	if (isGlobalEtalon(true))
		pCnt = 2;

	// Reset points
	for (int i = 0; i < pCnt; i++)
	{
		currentMeasurement.setMark(Point(currentMeasurement.getMark(imgIdxMap[currentImgIndex], i).getName(), -1, -1), imgIdxMap[currentImgIndex], i);
	}
    
    currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" +".tmp");
	// Display image
	showImage();
}

void MarkerWindow::imageClicked(const QPoint &p)
{
	VAMLogger::log("Image click");

	// Get size of the image currently displayed
	double xScale = ui.imageLabel->size().width();
	double yScale = ui.imageLabel->size().height();

	// If in selection mode
	if (markerSelectionMode)
	{
		// Starting values for minimum finding
		double minDist = 400;
		int selectedPt = -1;

		int pointCnt = currentMeasurement.getPointCnt(imgIdxMap[currentImgIndex]);

		// Find point closest to the click
		for (int i = 0; i < pointCnt; i++)
		{
			// Get point
			Point pt = currentMeasurement.getMark(imgIdxMap[currentImgIndex], i);

			// If point is set
			if (pt.x > -1)
			{
				// Get distance -- NOTE: Point coordinates are stored in the range [0,1] (realtive to the image) to make them scale independent
				double dist = (pt.x - p.x() / xScale)*(pt.x - p.x() / xScale) + (pt.y - p.y() / xScale)*(pt.y - p.y() / xScale);

				// We require the minimum distance to fall below a threshold
				if (dist < minDist && dist < 0.005)
				{
					selectedPt = i;
					minDist = dist;
				}
			}
		}

		VAMLogger::log("Selected point: " + QString::number(selectedPt));

		// Set selection and redraw markings
		selectedIdx = selectedPt;
		drawMarkings();

		return;
	}

	// Marker set mode

	// Check for finished image
	if (currentPointIndex == -1)
	{
		// If it's not the last image, then increase image counter
		if (currentImgIndex != ImgPathList.size() - 1)
		{
			currentImgIndex++;
		}
        
        currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" +".tmp");
		// Display new images
		showImage();

		return;
	}

	// Measurement now contains data
	measData = true;
	measurementModified = true;

	VAMLogger::log("Marked point: " + QString::number(currentPointIndex) + " on image: " + QString::number(currentImgIndex));

	// Add mark
	currentMeasurement.setMark(Point(currentMeasurement.getMark(imgIdxMap[currentImgIndex], currentPointIndex).getName(), p.x() / xScale, p.y() / xScale), imgIdxMap[currentImgIndex], currentPointIndex);

	// Move to the next unset marker on the image
	currentPointIndex = currentMeasurement.getFirstUnset(imgIdxMap[currentImgIndex]);

	// If image is now finished
	if (currentPointIndex == -1)
	{

		VAMLogger::log("Image done");

		// This shouldn't happen
		if (currentImgIndex >= ImgPathList.size())
		{
			return;
		}

		// Change finished flags and list view
		currentMeasurement.setMarked(imgIdxMap[currentImgIndex], true);
		//ui.imagesRemList->setRowHidden(imgIdxMap[currentImgIndex], true);
		unmarkedID->setData(unmarkedID->index(imgIdxMap[currentImgIndex]), IDList[imgIdxMap[currentImgIndex]] + VAMTranslatedStrings::doneStr());

		// Change remaining and done counters
		imgRem--;
		imgDone++;

	}

	// Display new images
    int currX = ui.imageScrollArea->horizontalScrollBar()->value();
    int currY = ui.imageScrollArea->verticalScrollBar()->value();
	showImage();
    ui.imageScrollArea->horizontalScrollBar()->setValue(currX);
    ui.imageScrollArea->verticalScrollBar()->setValue(currY);
    
}

void MarkerWindow::imageHovered(const QPoint &p)
{
	// If in selection mode, we don1t display crosshair
	if (markerSelectionMode)
		return;

	// Tell the image label where the cursor is
	ui.imageLabel->x = p.x();
	ui.imageLabel->y = p.y();

	// Tell it to update itself (This will call the overwritten onPainEvent function)
	ui.imageLabel->update();

}

void MarkerWindow::drawMarkings(double factor)
{
	// Get the size of the image view
	// NOTE: factor is used when called after zooming: in this case the function is called BEFORE the label is resized, therefore markers will be in the wrong position

	// Determine resize factor
	float imgRatio = (float)currentImg.cols / (float)currentImg.rows;

	float labelRatio = (float)ui.imageScrollArea->viewport()->size().width() / (float)ui.imageScrollArea->viewport()->size().height();
	float resFact = imgRatio < labelRatio ? (float)ui.imageScrollArea->viewport()->size().height() * scale / (float)currentImg.rows :
		(float)ui.imageScrollArea->viewport()->size().width() *scale / (float)currentImg.cols;

	cv::resize(currentImg, currentDrawing, cv::Size(0, 0), resFact, resFact);

	// Decide wether use the marked image or the computed one
	bool useMarkerImage = currentMeasurement.getMarked()[imgIdxMap[currentImgIndex]] && !markerSelectionMode && !isGlobalEtalon(true);

	// Resize them
	if (useMarkerImage)
	{
		currentMeasurement.calculate(currentProject->getAbsProjLib(), imgIdxMap[currentImgIndex], currentDrawing);
	}

	// Resize image to fit the scroll area * the zoom factor
	ui.imageLabel->resize(currentDrawing.cols, currentDrawing.rows);
	double xScale = ui.imageLabel->size().width();
	double yScale = ui.imageLabel->size().height();
	//cv::resize( currentImg, currentDrawing, cv::Size( ui.imageScrollArea->viewport()->size().width() * scale, ui.imageScrollArea->viewport()->size().height() *scale ) );


		// Get number of points
	int pCnt = currentSchema.pointCnt(getImageIdx(imgIdxMap[currentImgIndex]));
	if (hasEtalon(true))
		pCnt += 2;
	if (isGlobalEtalon(true))
		pCnt = 2;

	// Draw all the points
	for (int i = 0; i < pCnt; i++)
	{
		// Get coordinates and name
		Point p = currentMeasurement.getMark(imgIdxMap[currentImgIndex], i);

		// Draw set points only
		if (p.x != -1)
		{
			// Scale coordinates to the image size
			p.x *= xScale;
			p.y *= xScale;

			// Color according to the selected status
			cv::Scalar color = selectedIdx == i ? cv::Scalar(255, 0, 0) : cv::Scalar(0, 0, 255);
			QColor currCol = QColor(color[2], color[1], color[0]);

			// Put point marker and name on the image
			cv::circle(currentDrawing, p, 4, color);
			//cv::putText( currentDrawing, p.getName().toStdString(), cv::Point( p.x + 10, p.y ), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, color );

			// Position text
			int textWidth = p.getName().size() * 10, textHeight = 17;
			int originX = p.x + 10, originY = p.y;
			if (originY < textHeight)
				originY = textHeight;
			if (originY + textHeight >= currentDrawing.rows)
				originY = currentDrawing.rows - textHeight - 1;
			if (originX + textWidth >= currentDrawing.cols)
				originX = currentDrawing.cols - textWidth - 1;

			drawText(currentDrawing, cv::Point(originX, originY), p.getName(), currCol);
		}
	}

	// Put image on the label and update it
	ui.imageLabel->setPixmap(QPixmap::fromImage(cvMatToQImage(currentDrawing)));
	ui.imageLabel->update();
}

QString MarkerWindow::getPointName()
{
	if (currentPointIndex != -1)
	{
		// If the image is etalon and not finished, return "etalon"
		if (hasEtalon(true) && currentPointIndex < 2)
			return tr("Etalon");

		// Otrherwise get the name of the point
		int offset = hasEtalon(true) ? 2 : 0;
		return currentSchema.getPoint(currentPointIndex-offset, getImageIdx(imgIdxMap[currentImgIndex])).getName();
	}
	// This is only reached if finished
	return tr("Finished");
}

bool MarkerWindow::isGlobalEtalon(bool idxMap)
{
	// Get image index
	int imgIdx = idxMap ? imgIdxMap[currentImgIndex] : currentImgIndex;

	// Decide image index (side or upper)
	VAMImageIndex DBPart = getImageIdx(imgIdx);

	int IDIdx = imgIdx - imgCntThresholds[DBPart];

	// Get etalon vector from the database
	auto indices = currentProject->getDB(currentDBIdx).getGlobalEtalonIndex();
	return std::find(indices.begin(), indices.end(), IDIdx) != indices.end();

}

bool MarkerWindow::wasGlobalEtalon(int index)
{
	// Returns if the indexth image in the measurement was an etalon
	if (index < 0) return false;
	return currentMeasurement.getMarkRow(index).size() ==2 && !currentMeasurement.getMark(index, 0).getName().compare("etalon");
}

bool MarkerWindow::hasEtalon(bool idxMap)
{
	// Get image index
	int imgIdx = idxMap ? imgIdxMap[currentImgIndex] : currentImgIndex;

	// Decide image index (side or upper)
	VAMImageIndex DBPart = getImageIdx(imgIdx);

	int IDIdx = imgIdx - imgCntThresholds[DBPart];

	// Get etalon vector from the database
	return currentProject->getDB(currentDBIdx).getEtalons()[IDIdx];

}

bool MarkerWindow::hadEtalon(const Measurement &oldMeas, int index)
{
	// Returns if the indexth image in the measurement was an etalon
	if (index < 0) return false;
	return (!oldMeas.getMark(index, 0).getName().compare("etalon") && !oldMeas.getMark(index, 1).getName().compare("etalon"));
}

bool MarkerWindow::dataBaseChanged()
{
	// sideImgIdx[ i ] contains the index of the ith image of the database in the measurement
	// If the measurement does not contain the image then the index is -1

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		imgIndices[i].resize(currentDB.getCnt(toIdx(i)));
		if (!measData)
		{
			// Then all indices are -1
			imgIndices[i].assign(imgIndices[i].size(), -1);
		}

	}

	if (!measData)
		return true;

	bool val = false;
	currentImgIndex = 0;

	// Check side images
	for (int j = 0; j < VAMMaxVideos; j++)
	{
		for (int i = 0; i < currentDB.getCnt(toIdx(j)); i++, currentImgIndex++)
		{
			// Get index of the ith side image
			imgIndices[j][i] = currentMeasurement.getIDs().indexOf(currentDB.getIDs(false)[i]);

			// If the etalon status changed, the image needs to be reset, even if it is present
			if (isGlobalEtalon() != wasGlobalEtalon(imgIndices[j][i]))
			{
				imgIndices[j][i] = -1;
				val = true;
				continue;
			}
			if (hasEtalon() != hadEtalon(currentMeasurement, imgIndices[j][i]))
			{
				val = true;
				continue;
			}

			// If the image is not present, then the database changed
			if (imgIndices[j][i] == -1)
				val = true;

		}
	}

	// Reset image counter
	currentImgIndex = 0;

	return val || (currentDB.getIDs(true).size() != currentMeasurement.getIDs().size());

}

bool MarkerWindow::schemaChanged()
{
	// Return var
	bool val = false;

	// SidePtIdx[ i ] contains the index of the ith point of the schema in the measurement
	// If the point is not in the measurement, the index is -1
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		pointIndices[i].resize(currentSchema.pointCnt(toIdx(i)));
		if (!measData)
		{
			// Then all indices are -1
			pointIndices[i].assign(pointIndices[i].size(), -1);
		}

	}

	if (!measData)
		return true;

	// Check side points
	for (int j = 0; j < VAMMaxVideos; j++)
	{
		if (currentDB.getCnt(toIdx(j)))
		{
			// Find the index of the first non-etalon image
			int index = currentDB.getCnt(toIdx(j));
			for (int i = 0; i < currentDB.getCnt(toIdx(j)); i++)
			{
				auto indices = currentDB.getGlobalEtalonIndex();
				if (std::find(indices.begin(), indices.end(), i) != indices.end())
				{
					index = i;
					break;
				}
			}

			// If there are non-etalon images
			if (index != currentDB.getCnt(toIdx(j)))
			{
				// Check if the names of points match
				int offset = (currentMeasurement.getMark(index, 0).getName() == "etalon") ? 2 : 0;
				for (int i = 0; i < currentSchema.pointCnt(toIdx(j)); i++)
				{
					pointIndices[j][i] = currentMeasurement.getPoints(toIdx(j)).indexOf(currentSchema.pointModels[j]->stringList().at(i));

					// If not, the schema changed
					if (pointIndices[j][i] == -1)
						val = true;
					else
						;
				}
			}
		}
	}

	// Return
	return val;
}

void MarkerWindow::copyMarkOrSetDefault(Measurement &oldMeas, int pIdx, int offSet, int offset2, int oldImgIdx, VAMImageIndex imageIdx)
{
	std::vector< int > &updatePtIdx = pointIndices[imageIdx];
	// If the point existed in the old measurement, we copy it
	if (updatePtIdx[pIdx - offSet] >= 0)
		currentMeasurement.setMark(oldMeas.getMark(oldImgIdx, updatePtIdx[pIdx - offSet] + offset2), currentImgIndex, pIdx);
	else // If not, we add default marks, and set the marked status to false, since there is at least one unmarked point
	{
		currentMeasurement.setMark(Point(currentSchema.getPoint(pIdx - offSet, imageIdx).getName(), -1, -1), currentImgIndex, pIdx);
		currentMeasurement.setMarked(currentImgIndex, false);
	}
}

void MarkerWindow::setupMarkings()
{
	// Backup old measurement
	Measurement oldMeas = currentMeasurement;
	std::vector< int > oldImgCnts(4,0);
	for (int i = 1; i < VAMMaxVideos; i++)
	{
		oldImgCnts[i] = oldImgCnts[i - 1] + oldMeas.getCnt(toIdx(i - 1));
	}

	// Resize measurement to fit current sizes
	currentMeasurement.resize(imgCnt, currentDB.getCounts(), currentSchema.pointCounts(), currentDB.getEtalons(), currentDB.getGlobalEtalonIndex());
	currentMeasurement.setIDs(currentDB.getIDs(true));
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
		currentMeasurement.setPoints(currentSchema.pointModels[i]->stringList(), toIdx(i));

	// For all images
	for (currentImgIndex = 0; currentImgIndex < imgCnt; currentImgIndex++)
	{
		// Setup auxiliary variables based on the image index (side vs upper)
		VAMImageIndex imageIdx = getImageIdx(currentImgIndex);
		int imageIndex = currentImgIndex - imgCntThresholds[imageIdx];
		int pointCnt = currentSchema.pointCnt(imageIdx);
		std::vector< int > &updateImgIdx = imgIndices[imageIdx];
		std::vector< int > &updatePtIdx = pointIndices[imageIdx];

		// If the current image is present in the old measurement
		if (updateImgIdx[imageIndex] >= 0)
		{
			// We set it to marked if it was in the old measurement and copy the confidence
			currentMeasurement.setMarked(currentImgIndex, oldMeas.getMarked()[updateImgIdx[imageIndex]]);
			currentMeasurement.setConfidence(currentImgIndex, oldMeas.getConfidence(updateImgIdx[imageIndex]));

			// If it is etalon we copy the two markings
			if (hasEtalon())
			{
				for (int j = 0; j < 2; j++)
				{
					if( hadEtalon(oldMeas, updateImgIdx[imageIndex] + oldImgCnts[imageIdx]) )
						currentMeasurement.setMark(oldMeas.getMark(updateImgIdx[imageIndex] + oldImgCnts[imageIdx], j), currentImgIndex, j);
					else
						currentMeasurement.setMark(Point("etalon", -1, -1), currentImgIndex, j);
				}
				if(isGlobalEtalon())
					continue;
			}

			// If not etalon, we copy all markings in the new schema
			int offset = hasEtalon() ? 2 : 0;
			int offset2 = pointCnt != oldMeas.getMarkRow(updateImgIdx[imageIndex] + oldImgCnts[imageIdx]).size() ? 2 : 0;
			for (int j = offset; j < pointCnt + offset; j++)
			{
				copyMarkOrSetDefault(oldMeas, j, offset, offset2, updateImgIdx[imageIndex] + oldImgCnts[imageIdx], imageIdx);
				
			}
			continue;
		}

		// If the current image is not in the old measurement, we add default marks and confidence
		currentMeasurement.setConfidence(currentImgIndex, 100);

		// If etalon
		if (hasEtalon())
		{
			currentMeasurement.setMark(Point("etalon", -1, -1), currentImgIndex, 0);
			currentMeasurement.setMark(Point("etalon", -1, -1), currentImgIndex, 1);
		}
		if( isGlobalEtalon() )
			continue;

// If not etalon default markings from the schema
int offset = hasEtalon() ? 2 : 0;
for (int j = offset; j < pointCnt + offset; j++)
{
	currentMeasurement.setMark(Point(currentSchema.getPoint(j - offset, imageIdx).getName(), -1, -1), currentImgIndex, j);
}
	}
}

void MarkerWindow::showImage(bool autoPredict)
{
	// Read image
	VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
	currentImg = imgRead(ImgPathList[imgIdxMap[currentImgIndex]], currentMeasurement.getA()[imageIdx], currentMeasurement.getD()[imageIdx]);

	// Fill image with black if faild to load
	if (!currentImg.data)
		currentImg = cv::Mat(cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()), CV_8UC1, cv::Scalar(0, 0, 0));

	if (autoPredict && NNLoaded && !hasEtalon(true) && !currentMeasurement.getMarked()[imgIdxMap[currentImgIndex]] )
	{
		predictMarkings();
	}

	// Set back and forward buttons enabled/disabled based on the image counter
	ui.actionPrevious_Image->setEnabled(currentImgIndex != 0);
	ui.actionNext_image->setEnabled(currentImgIndex < ImgPathList.size() - 1);

	// Display ID of current image
	ui.animalIDLabel->setText(IDList[imgIdxMap[currentImgIndex]]);

	// Display confidence of current image
	ui.confBox->setValue(currentMeasurement.getConfidence(imgIdxMap[currentImgIndex]));

	// Display name of the first unset point
	currentPointIndex = currentMeasurement.getFirstUnset(imgIdxMap[currentImgIndex]);
	ui.pointName->setText(getPointName());

	// Display number of images finished and remaining
	ui.imgDoneLabel->setText(QString::number(imgDone));
	ui.imgRemLabel->setText(QString::number(imgRem));

	// Compute aspect ratios
	float imgRatio = (float)currentImg.cols / (float)currentImg.rows;
	float labelRatio = (float)ui.imageScrollArea->viewport()->size().width() / (float)ui.imageScrollArea->viewport()->size().height();

	// Resize Label
	int wi = (imgRatio > labelRatio) ? ui.imageScrollArea->viewport()->size().width() : ui.imageScrollArea->viewport()->size().height() * imgRatio;
	int hi = imgRatio > labelRatio ? ui.imageScrollArea->viewport()->size().height() : ui.imageScrollArea->viewport()->size().width() / imgRatio;
	ui.imageLabel->resize(wi, hi);

	// Resize it to fit the image label
	cv::resize(currentImg, currentDrawing, cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()));

	// Draw markings
	drawMarkings();
}

void MarkerWindow::removePoint()
{
	// Return if there is no selection
	if (selectedIdx == -1)
		return;

	// Modified
	measurementModified = true;

	// If the image is finished, make it unfinished
	if (currentMeasurement.getFirstUnset(imgIdxMap[currentImgIndex]) == -1)
	{
		imgRem++;
		imgDone--;

		ui.imgDoneLabel->setText(QString::number(imgDone));
		ui.imgRemLabel->setText(QString::number(imgRem));
		ui.imagesRemList->setRowHidden(imgIdxMap[currentImgIndex], false);
		unmarkedID->setData(unmarkedID->index(imgIdxMap[currentImgIndex]), IDList[imgIdxMap[currentImgIndex]]);
		currentMeasurement.setMarked(imgIdxMap[currentImgIndex], false);
	}

	// Reset the selected mark
	currentMeasurement.setMark(Point(currentMeasurement.getMark(imgIdxMap[currentImgIndex], selectedIdx).getName(), -1, -1), imgIdxMap[currentImgIndex], selectedIdx);

	currentMeasurement.save(currentProject->getGenProjLib() + "/Measurements/" + currentMeasurement.getName() + ".meas" + ".tmp");
	// Get first unset point
	currentPointIndex = currentMeasurement.getFirstUnset(imgIdxMap[currentImgIndex]);
	ui.pointName->setText(getPointName());
}

void MarkerWindow::predictMarkings()
{
	cv::Mat resized;
	cv::Size newSize(512, (512.0 / currentImg.cols ) * currentImg.rows);
	cv::resize(currentImg, resized, newSize);
	cv::cvtColor(resized, resized, cv::COLOR_BGR2RGB);

	VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
	float imgSize = 1.0 / (512.0 * 256.0);

	cv::Mat padded;
	int padding = 256 - resized.rows;
	if (padding < 0)
	{
		int lPad, rPad;
		lPad = rPad = -padding / 2;
		if (padding % 2 == 1)
			lPad += 1;

		cv::Rect myROI(0, lPad, resized.cols, resized.rows + padding);
		padded = resized(myROI);
	}
	else {
		int lPad, rPad;
		lPad = rPad = padding / 2;
		if (padding % 2 == 1)
			lPad += 1;

		cv::copyMakeBorder(resized, padded, lPad, rPad, 0, 0, cv::BORDER_CONSTANT, cv::Scalar(0));
	}

	auto tensor_image = torch::from_blob(padded.data, { padded.rows, padded.cols, padded.channels() }, at::kByte);
	tensor_image = tensor_image.permute({ 2,0,1 });
	tensor_image = tensor_image.toType(c10::kFloat).mul(0.00392156862);
	tensor_image.to(c10::DeviceType::CPU);

	// Create a vector of inputs.
	std::vector < torch::jit::IValue > inputs;
	std::vector<torch::Tensor> input;
	input.push_back(tensor_image);
	inputs.push_back(input);
	inputs.push_back(imageIdx);

	try {
		// Execute the model and turn its output into a tensor.
		auto output = model.forward(inputs).toTuple()->elements()[1].toList().get(0).toGenericDict();
		
		auto bb = output.at("boxes").toTensor()[0];
		auto conf = output.at("scores").toTensor()[0].item().toFloat();

		auto pred = output.at("keypoints").toTensor();
		auto shape = pred.sizes()[0];
		if (shape > 1)
		{
			QMessageBox::warning(this, tr("This is a debug message"), tr("More than 1 BB"));
		}

		float bbSize = ((bb[3] - bb[1]) * (bb[2] - bb[0])).item().toFloat() * imgSize;
		if (conf < 0.8)
		{
			if (bbSize < 0.1)
			{
				QMessageBox::warning(this, tr("Uncertain result"), 
					tr("The neural network has not detected a cattle with high enough confidence. Please annotate this image manually!")
					+ " (" + QString::number(conf) + ", " + QString::number(bbSize) + ")");
				return;
			}
		}
						
		auto markings = currentMeasurement.getMarkRow(imgIdxMap[currentImgIndex]);

		for (int i = 0; i < markings.size(); i++)
		{
			auto kp = pred[0][i];
			auto x = kp[0].item<float>();
			auto y = kp[1].item<float>() - padding / 2.0;

			Point pt = currentMeasurement.getMark(imgIdxMap[currentImgIndex], i);
			currentMeasurement.setMark(Point(pt.getName(), x / 512.f, y / 512.f), imgIdxMap[currentImgIndex], i);
			
		}
		currentMeasurement.setMarked(imgIdxMap[currentImgIndex], true);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		QMessageBox::warning(this, tr("Run failed"), tr("The neural network run has failed"));
	}

	unmarkedID->setData(unmarkedID->index(imgIdxMap[currentImgIndex]), IDList[imgIdxMap[currentImgIndex]] + VAMTranslatedStrings::doneStr());

}
