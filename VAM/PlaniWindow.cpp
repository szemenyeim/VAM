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

#include "PlaniWindow.h"
#include <qpainter.h>
#include <qscrollbar.h>
#include "xlsxwriter.h"
#include <QtConcurrent/QtConcurrent>

PlaniWindow::PlaniWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// default values
	unmarkedID = new QStringListModel();
	currentProject = NULL;

	A.resize(VAMMaxVideos);
	d.resize(VAMMaxVideos);

	polygon.resize(1);
	etalonVals.resize(VAMMaxVideos);

	// Setup window
	resetWindow();
}


PlaniWindow::~PlaniWindow(void)
{
	// Delete model
	delete unmarkedID;
}

void PlaniWindow::show()
{
	// Read image - otherwise show crashes
	VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
	currentImg = imgRead(ImgPathList[imgIdxMap[currentImgIndex]], A[imageIdx], d[imageIdx]);

	// Fill image with black if faild to load
	if (!currentImg.data)
		currentImg = cv::Mat(cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()), CV_8UC1, cv::Scalar(0, 0, 0));

	// Call parent function
	QMainWindow::show();

	// Display image (if not called the image size will be wrong)
	showImage();
}


void PlaniWindow::resetWindow()
{
	// setup UI
	ui.setupUi(this);

	// Default values
	planiModified = false;
	currentImgIndex = 0;
	imgCntThresholds.resize(4, 0);
	scale = 1;
	method = 0;
	brushSize = 20;
	thresh = 10;
	roiSet = false;
	eraseMode = false; 
	floodFilling = false;
	polygon[0].clear(); 
	fillCenter = cv::Point(-1, -1);

	ui.methodBox->addItem(tr("Polygon"));
	ui.methodBox->addItem(tr("Circular brush"));
	ui.methodBox->addItem(tr("Square brush"));
	ui.methodBox->setCurrentIndex(method);
	
	QFont font = ui.msgLabel->font();
	font.setPointSize(24);
	font.setBold(true);
	ui.msgLabel->setFont(font);

	ui.brushBox->setValue(brushSize);
	ui.addremToggle->setChecked(eraseMode);

	// Disable crosshair
	ui.imageLabel->paintCrosshair = false;

	// Connect signals and slots for the UI
	connect(ui.actionSave, &QAction::triggered, this, &PlaniWindow::savePlani);
	connect(ui.actionExport, &QAction::triggered, this, &PlaniWindow::exportPlani);
	connect(ui.actionPrevious_Image, &QAction::triggered, this, &PlaniWindow::prevImage);
	connect(ui.actionNext_image, &QAction::triggered, this, &PlaniWindow::skipImage);
	connect(ui.imagesRemList, &QListView::doubleClicked, this, &PlaniWindow::listDoubleClicked);
	connect(ui.actionClear_image, &QAction::triggered, this, &PlaniWindow::redoImage);
	connect(ui.actionDone, &QAction::triggered, this, &PlaniWindow::close);

	connect(ui.pushButton, &QPushButton::clicked, this, &PlaniWindow::applyPolygon);
	connect(ui.segBtn, &QPushButton::clicked, this, &PlaniWindow::segment);
	connect(ui.floodBtn, &QPushButton::clicked, this, &PlaniWindow::floodFill);
	connect(ui.rectBtn, &QPushButton::clicked, this, &PlaniWindow::setROI);
	connect(this, &PlaniWindow::segmDone, this, &PlaniWindow::segmentationFinished);
	connect(ui.clearBtn, &QPushButton::clicked, this, &PlaniWindow::clearPoints);

	connect(ui.threshSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged), this, &PlaniWindow::threshChanged);

	connect(ui.helpBtn, &QPushButton::clicked, this, &PlaniWindow::help);

	connect(ui.addremToggle, &QRadioButton::clicked, this, &PlaniWindow::eraseModeChanged);

	connect(ui.weightBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &PlaniWindow::weightChanged);
	connect(ui.brushBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &PlaniWindow::brushSizeChanged);

	connect(ui.methodBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &PlaniWindow::methodChanged);

	connect(ui.imageLabel, &CustomLabel::mousePressed, this, &PlaniWindow::imageClicked);

	connect(ui.imageScrollArea, &CustomScrollArea::wheelTurned, this, &PlaniWindow::resizeImage);

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

void PlaniWindow::setupUI()
{
	// Setup string list and list view
	unmarkedID->setStringList(IDList);
	ui.imagesRemList->setModel(unmarkedID);
	
	ui.imageLabel->setAlignment(Qt::AlignCenter);

	// Setup checkbox
	ui.addremToggle->setChecked(false);
	ui.methodBox->setCurrentIndex(0);

}

void PlaniWindow::savePlani()
{
	VAMLogger::log("Meas save");

	QDir dir;
	dir.setPath(currentProject->getAbsProjLib() + "/Planimetrics/");
	if (!dir.exists())
		dir.mkpath(".");

	QString fname = dir.absolutePath() + "/data.vol";
	QFile file(fname);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Planimetrics save error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return;
	}

	QTextStream out(&file);

	computeAreas();

	writeVector(weights, out);
	writeDoubleVector(compAreas, out);

	// Save mask image
	cv::imwrite(dir.absolutePath().toStdString() + "/" + std::to_string(imgIdxMap[currentImgIndex]) + "_" + std::to_string(getImageIdx(imgIdxMap[currentImgIndex])) + ".png", maskImage);

	// Save measurement
	planiModified = false;
}

void PlaniWindow::exportPlani()
{
	savePlani();

	QString fName = QFileDialog::getSaveFileName(this, tr("Export Planimetrics Data"), currentProject->getAbsProjLib() + "/Planimetrics/export.xlsx", tr("Excel spreadsheet (*.xlsx);;CSV (*.csv)"));

	if (fName == "")
		return;

	if (fName.endsWith(".xlsx"))
	{
		/* Create a new workbook and add a worksheet. */
		lxw_workbook  *workbook = workbook_new(fName.toUtf8().constData());
		lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

		/* Add a format. */
		lxw_format *format = workbook_add_format(workbook);

		/* Set the bold property for the format */
		format_set_bold(format);

		// Write header
		worksheet_write_string(worksheet, 0, 0, "ENAR", format);
		worksheet_write_string(worksheet, 0, 1, "Weight", format);

		for (int i = 0; i < currentDB.getVideoCnt(); i++)
		{
			std::string str = "Area #" + std::to_string(i);
			worksheet_write_string(worksheet, 0, 2+i, str.c_str(), format);
		}

		int rowCnt = 1;

		for (int i = 0; i < imgCnt; i++)
		{
			worksheet_write_string(worksheet, rowCnt, 0, IDList[i].toUtf8().constData(), format);
			worksheet_write_string(worksheet, rowCnt, 1, std::to_string(weights[i]).c_str(), format);
			for (int j = 0; j < compAreas[i].size(); j++)
			{
				worksheet_write_string(worksheet, rowCnt, 2+j, std::to_string(compAreas[i][j]).c_str(), format);
			}
			rowCnt++;
		}
		workbook_close(workbook);
	}
	else if (fName.endsWith("csv"))
	{
		QFile file(fName);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());

			VAMLogger::log("Export planimetrics error");
			return;
		}

		QTextStream out(&file);

		out << "ENAR,Weight";

		for (int i = 0; i < currentDB.getVideoCnt(); i++)
		{
			out << ",Area #" << i;
		}
		out << "\n";

		for (int i = 0; i < imgCnt; i++)
		{
			out << IDList[i] << "," << weights[i];
			for (int j = 0; j < compAreas[i].size(); j++)
			{
				out << "," << compAreas[i][j];
			}
			out << "\n";
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Unsupported extension"), tr("Please select a supported extension!"));
	}

}

void PlaniWindow::computeAreas()
{
	int IDIdx = getIDIndex();
	VAMImageIndex imgIdx = getImageIdx(imgIdxMap[currentImgIndex]);

	double val = cv::countNonZero(maskImage);

	compAreas[IDIdx][imgIdx] = val * etalonVals[imgIdx] / double(maskImage.cols * maskImage.rows);
}

void PlaniWindow::getSegmentation()
{
	VAMLogger::log("Segmentation");

	// Load mask image
	std::string fname = currentProject->getAbsProjLib().toStdString() + "/Planimetrics/" + std::to_string(imgIdxMap[currentImgIndex]) + "_" + std::to_string(getImageIdx(imgIdxMap[currentImgIndex])) + ".png";
	maskImage = cv::imread(fname);

	if (!maskImage.data)
	{
		maskImage = cv::Mat::zeros(currentImg.size(), CV_8UC1);
	}
	else
	{
		cv::cvtColor(maskImage, maskImage, cv::COLOR_BGR2GRAY);
	}

	drawImage();
}

void PlaniWindow::weightChanged(double val)
{
	// Modify weight
	planiModified = true;

	// Set weight
	weights[getIDIndex()] = val;

	VAMLogger::log("Weight set");
}

void PlaniWindow::brushSizeChanged(int val)
{
	VAMLogger::log("Brush size");

	brushSize = val;
}

void PlaniWindow::threshChanged(int val)
{
	thresh = val;
	if( fillCenter.x >= 0 && roiSet )
		floodFillImpl(fillCenter, false);
}

void PlaniWindow::methodChanged(int val)
{
	VAMLogger::log("Method");

	method = val;
}

void PlaniWindow::applyPolygon()
{
	VAMLogger::log("Apply polygon");

	if (polygon[0].size() < 3)
	{
		QMessageBox::warning(this, tr("Too few points"), tr("You need at least 3 points to draw a polygon"));
		return;
	}
	
	cv::fillPoly(maskImage, polygon, cv::Scalar(eraseMode ? 0 : 255));

	polygon[0].clear();
	drawImage();
}

void PlaniWindow::segment()
{
	VAMLogger::log("Run segmentation");

	if (!roiSet)
	{
		QMessageBox::warning(this, tr("No ROI"), tr("Please set the ROI first!"));
		return;
	}

	ui.msgLabel->setText(tr("Computation in progress... This might take a few seconds"));

	this->setEnabled(false);

	QtConcurrent::run(this, &PlaniWindow::segmentationImpl);
}

void PlaniWindow::segmentationImpl()
{
	double fact = 640.0 / maskImage.cols;
	
	cv::Mat tmpMask, tmpImage;
	cv::resize(maskImage, tmpMask, cv::Size(0, 0), fact, fact);
	cv::resize(currentImg, tmpImage, cv::Size(0, 0), fact, fact);
	tmpMask = tmpMask / 255;

	int initMode = cv::countNonZero(tmpMask) ? cv::GC_INIT_WITH_MASK : cv::GC_INIT_WITH_RECT;

	cv::Rect scaledRoi(roi.x * fact, roi.y * fact, roi.width * fact, roi.height * fact);

	cv::Mat bgModel, fgModel;

	cv::grabCut(tmpImage, tmpMask, scaledRoi, bgModel, fgModel, 1, initMode); // | cv::GC_INIT_WITH_MASK

	cv::resize(tmpMask, tmpMask, maskImage.size(), 0, 0, cv::INTER_NEAREST);
	cv::bitwise_and(cv::Mat::ones(maskImage.size(), maskImage.type()), tmpMask, maskImage);

	maskImage *= 255;

	emit segmDone();
}

void PlaniWindow::segmentationFinished()
{
	this->setEnabled(true);
	ui.msgLabel->setText(tr("Done"));

	//polygon[0].clear();
	drawImage();
}

void PlaniWindow::floodFill()
{
	if (!roiSet)
	{
		QMessageBox::warning(this, tr("No ROI"), tr("Please set the ROI first!"));
		return;
	}

	ui.msgLabel->setText(tr("Please select a seed point on the image!"));

	// disable ui
	ui.methodBox->setEnabled(false);
	ui.brushBox->setEnabled(false);
	ui.weightBox->setEnabled(false);
	ui.segBtn->setEnabled(false);
	ui.clearBtn->setEnabled(false);
	ui.helpBtn->setEnabled(false);
	ui.floodBtn->setEnabled(false);
	ui.rectBtn->setEnabled(false);
	ui.threshSlider->setEnabled(false);
	ui.actionClear_image->setEnabled(false);
	ui.actionDone->setEnabled(false);
	ui.actionExport->setEnabled(false);
	ui.actionNext_image->setEnabled(false);
	ui.actionPrevious_Image->setEnabled(false);
	ui.actionSave->setEnabled(false);
	ui.imagesRemList->setEnabled(false);
	ui.addremToggle->setEnabled(false);

	floodFilling = true;
}


void PlaniWindow::floodFillImpl(const cv::Point & pt, bool backUp)
{
	if (backUp || !maskBU.data)
	{
		maskBU = maskImage.clone();
	}

	cv::Mat tmpMask = cv::Mat::zeros(roi.height + 2, roi.width + 2, maskImage.type());

	int flags = 4 | 255 << 8 | cv::FLOODFILL_FIXED_RANGE | cv::FLOODFILL_MASK_ONLY;
	cv::floodFill(currentImg(roi), tmpMask, pt - roi.tl(), cv::Scalar(255), 0, cv::Scalar(thresh, thresh, thresh), cv::Scalar(thresh, thresh, thresh), flags);

	if (eraseMode)
	{
		maskImage(roi) = maskBU(roi) - tmpMask(cv::Rect(1, 1, roi.width, roi.height));
	}
	else
	{
		cv::bitwise_or(maskBU(roi), tmpMask(cv::Rect(1, 1, roi.width, roi.height)), maskImage(roi));
	}
	
	// enable ui
	ui.methodBox->setEnabled(true);
	ui.brushBox->setEnabled(true);
	ui.weightBox->setEnabled(true);
	ui.segBtn->setEnabled(true);
	ui.clearBtn->setEnabled(true);
	ui.helpBtn->setEnabled(true);
	ui.floodBtn->setEnabled(true);
	ui.rectBtn->setEnabled(true);
	ui.threshSlider->setEnabled(true);
	ui.actionClear_image->setEnabled(true);
	ui.actionDone->setEnabled(true);
	ui.actionExport->setEnabled(true);
	ui.actionNext_image->setEnabled(true);
	ui.actionPrevious_Image->setEnabled(true);
	ui.actionSave->setEnabled(true);
	ui.imagesRemList->setEnabled(true);
	ui.addremToggle->setEnabled(true);

	ui.msgLabel->setText(tr("Done"));

	floodFilling = false;

	drawImage();
}

void PlaniWindow::setROI()
{
	if (polygon[0].size() < 2)
	{
		QMessageBox::warning(this, tr("Too few points"), tr("You need at least 2 points to select region of interest"));
		return;
	}

	roi = cv::boundingRect(polygon[0]);
	roiSet = true;

	drawImage();
}

void PlaniWindow::help()
{
	// Display about information
	QMainWindow *window = new QMainWindow(this);
	window->setWindowModality(Qt::ApplicationModal);
	window->setWindowTitle(tr("How to segment"));

	QLabel *label = new QLabel(window);

	label->setText("This is a powerful tool for segmenting animals from the background \n\n"
		"Steps:\n"
		"	1. Put down 2 points that define a rectangle that is entirely OUTSIDE the animal and press S\n"
		"	2. Use the polygon and brush tools to correct any errors in the segmentation\n"
		"		2.1. To use the polygon tool put down 3 or more points and press A\n"
		"\n");

	label->setTextInteractionFlags(Qt::TextSelectableByMouse);

	QVBoxLayout *layout = new QVBoxLayout(window);

	layout->addWidget(label);

	QFrame *frame = new QFrame(window);
	frame->setLayout(layout);

	window->setCentralWidget(frame);
	window->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	window->show();
}

void PlaniWindow::clearPoints()
{
	VAMLogger::log("Points cleared");

	polygon[0].clear();
	drawImage();
}

void PlaniWindow::eraseModeChanged()
{
	VAMLogger::log("Erase mode");

	eraseMode = ui.addremToggle->isChecked();
}

void PlaniWindow::setCurrentProject(Project *value)
{
	currentProject = value;

	VAMLogger::log("Set current project");

	// Get current schema and DB
	currentDB = currentProject->getDB(0);

	// Read camera files
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
	{
		cv::FileStorage fs((currentProject->getAbsProjLib() + "/Database/cam" + QString::number(i) + ".yaml").toStdString(), cv::FileStorage::READ);
		fs["cam"] >> A[i];
		fs["dist"] >> d[i];
	}

	// Read Image lists
	IDList = QStringList(currentDB.getIDs());
	ImgPathList = QStringList(currentDB.getImages());

	if (IDList.size() != ImgPathList.size())
	{
		VAMLogger::log("Corrupt DB");
		QMessageBox::critical(this, tr("Error: Corrupt Database"), tr("The Database file has been corrupted. Please fix the still database!"));
		return;
	}

	// Check if image files exist
	for (QString imgPath : ImgPathList)
	{
		if (!VAMFileAgent::openFile(imgPath))
		{
			VAMLogger::log("Missing images");
			QMessageBox::critical(this, tr("Error: Image files missing"), tr("One or more image files are missing from the hard drive. Please fix the still database!"));
			return;
		}
	}

	// Get image counts
	for (int i = 1; i < VAMMaxVideos; i++)
	{
		imgCntThresholds[i] = imgCntThresholds[i - 1] + currentDB.getCnt(toIdx(i - 1));
	}

	auto etalonInd = currentDB.getGlobalEtalonIndex();
	std::vector<int> etalons;
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
	{
		for (auto ind : etalonInd)
		{
			etalons.push_back(imgCntThresholds[i] + ind);
		}
	}

	std::sort(etalons.begin(), etalons.end(), std::greater<int>());
	for (auto ind : etalons)
	{
		IDList.erase(IDList.begin() + ind);
		ImgPathList.erase(ImgPathList.begin() + ind);
	}
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
	{
		imgCntThresholds[i] -= i*etalonInd.size();
	}

	imgCnt = IDList.size() / currentDB.getVideoCnt();
	weights.resize(imgCnt, 1);
	compAreas.resize(imgCnt, std::vector<double>(currentDB.getVideoCnt(), 1.0));

	if (currentProject->getMeasCnt() <= 0)
	{
		VAMLogger::log("Missing measurement");
		QMessageBox::critical(this, tr("Error: Measuremet file missing"), tr("The measurement file is missing from the project. This shouldn't happen!"));
		return;
	}

	Measurement &currMeas = currentProject->getMeasurement(0);
	currMeas.setA(A);
	currMeas.setD(d);
	for (int i = 0; i < currentDB.getVideoCnt(); i++)
	{
		etalonVals[i] = currMeas.getPixelSize(imgCntThresholds[i], currentDB.getGlobalEtalonIndex(), toIdx(i));
	}

	// Setup remaining variables
	currentImgIndex = 0;
	
	// Setup image index map
	imgIdxMap.resize(0);
	if (VAMOptions::VAMImageOrderingType == OrderByAnimal)
	{
		std::vector< std::vector< int >> v(VAMMaxVideos);

		int maxSize = 0;
		for (int i = 0; i < VAMMaxVideos; i++)
		{
			int currSize = imgCnt;
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
	}
	else
	{
		imgIdxMap.resize(IDList.size());
		std::iota(imgIdxMap.begin(), imgIdxMap.end(), 0);
	}

	QDir dir;
	dir.setPath(currentProject->getAbsProjLib() + "/Planimetrics/");
	if (!dir.exists())
		dir.mkpath(".");

	// Read from file
	QString fname = dir.absolutePath() + "/data.vol";
	QFile file(fname);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		weights = readVector<double>(in);
		compAreas = readDoubleVector<double>(in);
	}

	// Setup UI
	setupUI();
}

Project *PlaniWindow::getCurrentProject() const
{
	return currentProject;
}

void PlaniWindow::adjustScrollBar(QScrollBar *scrollBar, double factor, double pos)
{
	// If the zoom scale changed by factor, we multiply the current position by it
	scrollBar->setValue(int(factor * scrollBar->value()
		// And offset it according to the center of the zooming
		+ ((factor - 1) * scrollBar->pageStep() * pos)));
}

void PlaniWindow::resizeImage(double factor, QPointF pos)
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
	drawImage(factor);
}

void PlaniWindow::closeEvent(QCloseEvent *event)
{
	// Prompt for save if the measurement was modified
	if (planiModified)
	{
		VAMLogger::log("Prompt for Planimetrics save");
		QMessageBox msgBox;
		msgBox.setText(tr("The current Planimetrics have been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Save");
			savePlani();
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

void PlaniWindow::resizeEvent(QResizeEvent * event)
{
	// Update marker drawings
	drawImage();
}


void PlaniWindow::prevImage()
{
	VAMLogger::log("Prev img: " + QString::number(currentImgIndex));

	// Save mask image
	std::string fname = currentProject->getAbsProjLib().toStdString() + "/Planimetrics/" + std::to_string(imgIdxMap[currentImgIndex]) + "_" + std::to_string(getImageIdx(imgIdxMap[currentImgIndex])) + ".png";
	cv::imwrite(fname, maskImage);
	computeAreas();

	// Decrease image cntr
	currentImgIndex--;
	polygon[0].clear();
	// Display image
	showImage();
}

void PlaniWindow::skipImage()
{
	VAMLogger::log("Next img: " + QString::number(currentImgIndex));

	// Save mask image
	std::string fname = currentProject->getAbsProjLib().toStdString() + "/Planimetrics/" + std::to_string(imgIdxMap[currentImgIndex]) + "_" + std::to_string(getImageIdx(imgIdxMap[currentImgIndex])) + ".png";
	cv::imwrite(fname, maskImage);
	computeAreas();

	// Increase image cntr
	currentImgIndex++;
	polygon[0].clear();
	// Display image
	showImage();
}

void PlaniWindow::listDoubleClicked(QModelIndex curr)
{
	VAMLogger::log("Next img: " + QString::number(currentImgIndex));

	// Save mask image
	std::string fname = currentProject->getAbsProjLib().toStdString() + "/Planimetrics/" + std::to_string(imgIdxMap[currentImgIndex]) + "_" + std::to_string(getImageIdx(imgIdxMap[currentImgIndex])) + ".png";
	cv::imwrite(fname, maskImage);
	computeAreas();

	// Increase image cntr
	currentImgIndex = curr.row();
	polygon[0].clear();
	// Display image
	showImage();
}

void PlaniWindow::redoImage()
{
	VAMLogger::log("Reset img: " + QString::number(currentImgIndex));
	
	// Reset image
	polygon[0].clear();
	getSegmentation();

	// Modified
	planiModified = true;

	// Display image
	showImage();
}

void PlaniWindow::imageClicked(const QPoint &p)
{
	VAMLogger::log("Image click");

	double fact = double(maskImage.cols) / double(currentDrawing.cols);

	cv::Point pt(p.x()*fact, p.y()*fact);

	if (floodFilling)
	{
		fillCenter = pt;
		floodFillImpl(pt, true);
		return;
	}
	
	// If in selection mode
	if (method == 0)
	{
		// Add to polygon
		polygon[0].push_back(pt);
	}
	else
	{
		// Use Brush
		cv::Scalar newVal( eraseMode ? 0 : 255 );

		if (method == 1)
		{
			cv::circle(maskImage, pt, brushSize, newVal, -1);
		}
		else
		{
			cv::Point p1(pt.x - brushSize, pt.y - brushSize), p2(pt.x + brushSize, pt.y + brushSize);
			if (p1.x < 0)
				p1.x = 0;
			if (p1.y < 0)
				p1.y = 0;
			if (p2.x >= maskImage.cols)
				p2.x = maskImage.cols - 1;
			if (p2.y >= maskImage.rows)
				p2.y = maskImage.rows - 1;

			maskImage(cv::Rect(p1, p2)) = newVal;
		}
	}

	
	// Display new images
	drawImage();

}

void PlaniWindow::drawImage(double factor)
{
	// Get the size of the image view
	// NOTE: factor is used when called after zooming: in this case the function is called BEFORE the label is resized, therefore markers will be in the wrong position

	// Determine resize factor
	float imgRatio = (float)currentImg.cols / (float)currentImg.rows;

	float labelRatio = (float)ui.imageScrollArea->viewport()->size().width() / (float)ui.imageScrollArea->viewport()->size().height();
	float resFact = imgRatio < labelRatio ? (float)ui.imageScrollArea->viewport()->size().height() * scale / (float)currentImg.rows :
		(float)ui.imageScrollArea->viewport()->size().width() *scale / (float)currentImg.cols;

	currentDrawing = currentImg*0.4;
	if (maskImage.data)
	{
		cv::Mat other;
		cv::bitwise_and(currentImg, cv::Scalar(255,0,255), other, maskImage);

		currentDrawing += other*0.6;

		std::vector< std::vector< cv::Point > > contours;
		cv::findContours(maskImage.clone(), contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
		cv::drawContours(currentDrawing, contours, -1, cv::Scalar(0, 255, 0), 2);

	}

	for (auto pt : polygon[0])
	{
		cv::circle(currentDrawing, pt, 5, cv::Scalar(0, 0, 255), 2);
	}

	if (roiSet)
	{
		cv::rectangle(currentDrawing, roi, cv::Scalar(255, 0, 0), 2);
	}

	cv::resize(currentDrawing, currentDrawing, cv::Size(0, 0), resFact, resFact);
	
	// Resize image to fit the scroll area * the zoom factor
	ui.imageLabel->resize(currentDrawing.cols, currentDrawing.rows);
	double xScale = ui.imageLabel->size().width();
	double yScale = ui.imageLabel->size().height();
	//cv::resize( currentImg, currentDrawing, cv::Size( ui.imageScrollArea->viewport()->size().width() * scale, ui.imageScrollArea->viewport()->size().height() *scale ) );

	// Put image on the label and update it
	ui.imageLabel->setPixmap(QPixmap::fromImage(cvMatToQImage(currentDrawing)));
	ui.imageLabel->update();
}

bool PlaniWindow::isGlobalEtalon()
{
	// Get image index
	int imgIdx = imgIdxMap[currentImgIndex];

	// Decide image index (side or upper)
	VAMImageIndex DBPart = getImageIdx(imgIdx);

	int IDIdx = imgIdx - imgCntThresholds[DBPart];

	// Get etalon vector from the database
	auto indices = currentProject->getDB(0).getGlobalEtalonIndex();
	return std::find(indices.begin(), indices.end(), IDIdx) != indices.end();

}

void PlaniWindow::showImage()
{
	// Set back and forward buttons enabled/disabled based on the image counter
	ui.actionPrevious_Image->setEnabled(currentImgIndex != 0);
	ui.actionNext_image->setEnabled(currentImgIndex < ImgPathList.size() - 1);
	
	// Display confidence of current image
	ui.weightBox->setValue(weights[getIDIndex()]);
	
	// Read image
	VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
	currentImg = imgRead(ImgPathList[imgIdxMap[currentImgIndex]], A[imageIdx], d[imageIdx]);
	maskBU = cv::Mat();

	// Fill image with black if faild to load
	if (!currentImg.data)
		currentImg = cv::Mat(cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()), CV_8UC1, cv::Scalar(0, 0, 0));

	// Set variables
	roi = cv::Rect(0, 0, currentImg.cols, currentImg.rows);
	floodFilling = false;
	roiSet = false;
	fillCenter = cv::Point(-1, -1);

	// Compute aspect ratios
	float imgRatio = (float)currentImg.cols / (float)currentImg.rows;
	float labelRatio = (float)ui.imageScrollArea->viewport()->size().width() / (float)ui.imageScrollArea->viewport()->size().height();

	// Resize Label
	int wi = (imgRatio > labelRatio) ? ui.imageScrollArea->viewport()->size().width() : ui.imageScrollArea->viewport()->size().height() * imgRatio;
	int hi = imgRatio > labelRatio ? ui.imageScrollArea->viewport()->size().height() : ui.imageScrollArea->viewport()->size().width() / imgRatio;
	ui.imageLabel->resize(wi, hi);

	// Resize it to fit the image label
	cv::resize(currentImg, currentDrawing, cv::Size(ui.imageLabel->size().width(), ui.imageLabel->size().height()));

	// Get Initial segmentation and draw image	
	getSegmentation();
}