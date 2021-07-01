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

#include "SchemaWindow.h"
#include <qmenu.h>


SchemaWindow::SchemaWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// Default window state
	resetWindow();
}


SchemaWindow::~SchemaWindow(void)
{

}

void SchemaWindow::resetWindow()
{
	// Setup UI
	ui.setupUi(this);

	// Default variable values
	schemaModified = false;
	UIDisabled = false;
	angleSelection.resize(VAMMaxVideos, false);
	distSelection.resize(VAMMaxVideos, false);
	images.resize(VAMMaxVideos);
	dispImages.resize(VAMMaxVideos);
	pointSelection = false;
	selected = 0;
	schemaName = QString("");

	// Fill up UI element lists
	newMeasButtons = { ui.newMeasButton1, ui.newMeasButton2, ui.newMeasButton3, ui.newMeasButton4 };
	newPointButtons = { ui.newPointButton1, ui.newPointButton2, ui.newPointButton3, ui.newPointButton4 };
	removeMeasButtons = { ui.removeMeasButton1, ui.removeMeasButton2, ui.removeMeasButton3, ui.removeMeasButton4 };
	removePointButtons = { ui.removePointButton1, ui.removePointButton2, ui.removePointButton3, ui.removePointButton4 };
	renameMeasButtons = { ui.renameMeasButton1, ui.renameMeasButton2, ui.renameMeasButton3, ui.renameMeasButton4 };
	renamePointButtons = { ui.renamePointButton1, ui.renamePointButton2, ui.renamePointButton3, ui.renamePointButton4 };
	pointViews = { ui.pointView1, ui.pointView2, ui.pointView3, ui.pointView4 };
	measViews = { ui.measView1, ui.measView2, ui.measView3, ui.measView4 };
	imageLabels = { ui.imageLabel1, ui.imageLabel2, ui.imageLabel3, ui.imageLabel4 };
	ptLabels = { ui.pl1, ui.pl2, ui.pl3, ui.pl4 };
	measLabels = { ui.ml1, ui.ml2, ui.ml3, ui.ml4 };
	imnameLabels = { ui.il1, ui.il2, ui.il3, ui.il4 };

	// Connect action slots
	connect(ui.actionOpen_Images, &QAction::triggered, this, &SchemaWindow::openImages);
	connect(ui.actionSet_Correction_Measurement, &QAction::triggered, this, &SchemaWindow::setCorrection);
	connect(ui.actionSave, &QAction::triggered, this, &SchemaWindow::saveSchema);
	connect(ui.actionSave_as, &QAction::triggered, this, &SchemaWindow::saveAsSchema);
	connect(ui.actionDone, &QAction::triggered, this, &SchemaWindow::close);

	// Connect button slots
	for (int i = 0; i < VAMMaxVideos; i++)
	{

		// Popup menu for new mesurement (side)
		VAMImageIndex idx = toIdx(i);

		QMenu *menu = new QMenu();
		QAction *dist = new QAction(tr("New Distance"), this);
		QAction *angle = new QAction(tr("New Angle"), this);
		menu->addAction(dist);
		menu->addAction(angle);
		newMeasButtons[i]->setMenu(menu);
		newMeasButtons[i]->setPopupMode(QToolButton::InstantPopup);

		connect(angle, &QAction::triggered, std::bind(&SchemaWindow::newAngleC, this, toIdx(i)));
		connect(dist, &QAction::triggered, std::bind(&SchemaWindow::newDistC, this, toIdx(i)));
		connect(newPointButtons[i], &QPushButton::clicked, std::bind(&SchemaWindow::newPoint, this, toIdx(i)));

		connect(removePointButtons[i], &QPushButton::clicked, std::bind(&SchemaWindow::delPoint, this, toIdx(i)));
		connect(removeMeasButtons[i], &QPushButton::clicked, std::bind(&SchemaWindow::delMeas, this, toIdx(i)));

		connect(renamePointButtons[i], &QPushButton::clicked, std::bind(&SchemaWindow::renPoint, this, toIdx(i)));
		connect(renameMeasButtons[i], &QPushButton::clicked, std::bind(&SchemaWindow::renMeas, this, toIdx(i)));

		// Connect clicked slots
		connect(pointViews[i], &QListView::clicked, std::bind(&SchemaWindow::listClicked, this, toIdx(i)));

		connect(imageLabels[i], &CustomLabel::mousePressed, std::bind(&SchemaWindow::imageClicked, this, std::placeholders::_1, toIdx(i)));

	}

	// Setup font
	QFont font("Times", 12, QFont::Bold);
	ui.infoLabel->setFont(font);

	// Setup window buttons
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

}

void SchemaWindow::setupWindow()
{

	vidCnt = currentProject->getDB(0).getVideoCnt();

	// setup list views
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if (i < vidCnt)
		{
			pointViews[i]->setModel(currentSchema.pointModels[i]);
			measViews[i]->setModel(currentSchema.measModels[i]);
		}
		else
		{
			pointViews[i]->setVisible(false);
			measViews[i]->setVisible(false);
			imageLabels[i]->setVisible(false);
			newPointButtons[i]->setVisible(false);
			removePointButtons[i]->setVisible(false);
			removeMeasButtons[i]->setVisible(false);
			renamePointButtons[i]->setVisible(false);
			renameMeasButtons[i]->setVisible(false);
			newMeasButtons[i]->setVisible(false);
			imageLabels[i]->setVisible(false);
			measLabels[i]->setVisible(false);
			ptLabels[i]->setVisible(false);
			imnameLabels[i]->setVisible(false);
		}
	}

	// Not modified
	schemaModified = false;
}

void SchemaWindow::openImages()
{
	// Open dialog for side and top images

	images.resize(VAMMaxVideos);
	dispImages.resize(VAMMaxVideos);

	int vidCnt = currentProject->getDB(0).getVideoCnt();

	for (int i = 0; i < vidCnt; i++)
	{
		QString imName = QFileDialog::getOpenFileName(this, tr("Open Image File") + " #" + QString::number(i), currentProject->getAbsProjLib(), tr("Image Files (*.bmp *.dds *.gif *.ico *.jpg *.jpeg *.tga *.tif *.tiff *.pbm *.pgm *.png *.ppm *.xbm *.xpm)"));

		if (imName.isEmpty())
			continue;

		VAMLogger::log("Opening images");

		// Load Images
		images[i] = imgRead(imName, cv::Mat(), cv::Mat());

		if (!images[i].data)
		{
			VAMLogger::log("Non existing images...");
			QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
				tr("Cannot load").append(" %1.").arg(QDir::toNativeSeparators(imName)));

			continue;
		}

		float imgRatio = (float)images[i].cols / (float)images[i].rows;
		float labelRatio = (float)imageLabels[i]->size().width() / (float)imageLabels[i]->size().height();
		float sideFact = imgRatio < labelRatio ? (float)imageLabels[i]->size().height() / (float)images[i].rows : (float)imageLabels[i]->size().width() / (float)images[i].cols;
		cv::resize(images[i], dispImages[i], cv::Size(0, 0), sideFact, sideFact);
		imageLabels[i]->setPixmap(QPixmap::fromImage(cvMatToQImage(dispImages[i])));

	}

}

void SchemaWindow::newAngleC(VAMImageIndex idx)
{
	// Prompt for name
	QString name;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Schema::isMeasNew, &currentSchema, _1, idx);
	if (!getName(tr("Enter Name"), tr("Please enter a name for the new angle!"), tr("Please specify a name!"), tr("An angle with this name already exists!"), name, func))
		return;

	VAMLogger::log("New angle " + idx);

	// Set name
	newAngle.setName(name);

	// Display message to select the three points
	ui.infoLabel->setText(tr("Please select the three points to define the angle!"));

	// Start side angle selection
	clearSelections();
	angleSelection[idx] = true;

	// Disable everything but the relevant parts of the UI
	disableUI(idx);
}

void SchemaWindow::newDistC(VAMImageIndex idx)
{
	// Prompt for name
	QString name;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Schema::isMeasNew, &currentSchema, _1, idx);
	if (!getName(tr("Enter Name"), tr("Please enter a name for the new distance!"), tr("Please specify a name!"), tr("A distance with this name already exists!"), name, func))
		return;

	VAMLogger::log("New distance " + idx);

	// Set name
	newDistance.setName(name);

	// Display message to select the two points
	ui.infoLabel->setText(tr("Please select the two points to define the distance!"));

	// Set side distance selection
	clearSelections();
	distSelection[idx] = true;

	// Disable everything but the relevant parts of the UI
	disableUI(idx);
}

void SchemaWindow::newPoint(VAMImageIndex idx)
{
	// Prompt for name
	currPName.clear();
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Schema::isPointNew, &currentSchema, _1, idx);
	if (!getName(tr("Enter Name"), tr("Please enter a name for the new point!"), tr("Please specify a name!"), tr("A point with this name already exists!"), currPName, func))
		return;

	VAMLogger::log("New point " + idx);

	// Prompt for selection
	ui.infoLabel->setText(tr("Please select the location of the point on the image!"));

	pointSelection = true;

	// Disable everything but the relevant parts of the UI
	disableUI(idx);
}

bool SchemaWindow::saveSchema()
{
	// Prompt for name
	if (schemaName.isEmpty())
	{
		// Prompt for project file
		schemaName =/* QFileDialog::getSaveFileName( this, tr( "Save Schema" ),*/ currentProject->getGenProjLib() + "/Schemas/" + currentSchema.getName() + ".schem"/*, tr( "VAM Schema (*.schem)" ) )*/;

		if (schemaName.isEmpty())
			return false;

		VAMLogger::log("New schema save");

		// Notify main window of new schema
		emit newData();
	}

	bool haveMeas = true;
	for (int i = 0; i < vidCnt; i++)
	{
		if (currentSchema.measCnt(toIdx(i)) == 0)
		{
			haveMeas = false;
			break;
		}
	}
	if (!haveMeas)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("There are no measurements for some of your videos!"));
		msgBox.setInformativeText(tr("Do you want to save the schema anyway?"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		int ret = msgBox.exec();

		if (ret == QMessageBox::No)
		{
			return false;
		}
	}

	VAMLogger::log("Schema save");

	// Save schema
	currentSchema.save(schemaName);

	// Add to project 
	currentProject->addSchema(currentSchema);

	emit dataUpdate();

	// No longer modified
	schemaModified = false;

	return true;
}

void SchemaWindow::saveAsSchema()
{
	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isSchemaNew, currentProject, _1);
	if (!getName(tr("New Schema"), tr("Enter Name:"), tr("Please specify a name!"), tr("A schema with this name already exists!"), text, func))
		return;

	// Set new name
	currentSchema.setName(text);

	// Prompt for project file
	schemaName = /*QFileDialog::getSaveFileName( this, tr( "Save Schema" ),*/ currentProject->getGenProjLib() + "/Schemas/" + currentSchema.getName() + ".schem"/*, tr( "VAM Schema (*.schem)" ) )*/;

	if (schemaName.isEmpty())
		return;

	VAMLogger::log("Schema save as");

	// Notify main window of new schema
	emit newData();

	// Save schema
	currentSchema.save(schemaName);

	// Add to project 
	currentProject->addSchema(currentSchema);
	emit dataUpdate();

	// No longer modified
	schemaModified = false;
}

void SchemaWindow::delPoint(VAMImageIndex idx)
{
	// Check if there is a point selected
	QModelIndexList indexes = pointViews[idx]->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to delete!"));
		return;
	}

	int index = indexes.at(0).row();
	VAMLogger::log("Delete point: " + QString::number(index) + " " + QString::number(idx));

	// Check if point is involved in measurement
	if (currentSchema.isPointUsed(index, idx))
	{
		QMessageBox::warning(this, tr("The point is used for some of the measurements."),
			tr("Please delete these angles/distances first!") + " " + currentSchema.getUsedPoints(index, idx));
		return;
	}
	schemaModified = true;

	// Otherwise detete
	currentSchema.removePoint(index, idx);
}

void SchemaWindow::delMeas(VAMImageIndex idx)
{
	// Check if there is a measurement selected
	QModelIndexList indexes = measViews[idx]->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a measurement to delete!"));
		return;
	}

	int index = indexes.at(0).row();
	VAMLogger::log("Delete measurement: " + QString::number(index) + " " + QString::number(idx));

	schemaModified = true;

	// Delete
	currentSchema.removeMeas(index, idx);
}

void SchemaWindow::renPoint(VAMImageIndex idx)
{
	// Check if there is a point selected
	QModelIndexList indexes = pointViews[idx]->selectionModel()->selectedIndexes();
	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to rename!"));
		return;
	}

	int index = indexes.at(0).row();
	VAMLogger::log("Rename point: " + QString::number(index) + " " + QString::number(idx));

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Schema::isPointNew, &currentSchema, _1, idx);
	if (!getName(tr("Enter Name"), tr("Please enter the new name for the point!"), tr("Please specify a name!"), tr("A point with this name already exists!"), text, func))
		return;

	// Rename point
	schemaModified = true;
	currentSchema.renamePoint(index, text, idx);

}

void SchemaWindow::renMeas(VAMImageIndex idx)
{
	// Check if there is a measurement selected
	QModelIndexList indexes = measViews[idx]->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a measurement to rename!"));
		return;
	}

	int index = indexes.at(0).row();
	VAMLogger::log("Rename measurement: " + QString::number(index) + " " + QString::number(idx));

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Schema::isMeasNew, &currentSchema, _1, idx);
	if (!getName(tr("Enter Name"), tr("Please enter the new name for the measurement!"), tr("Please specify a name!"), tr("A measurement with this name already exists!"), text, func))
		return;

	// Rename measurement
	schemaModified = true;
	currentSchema.renameMeas(index, text, idx);

}

void SchemaWindow::listClicked(VAMImageIndex idx)
{
	// We only care if we are int he process of defining a side angle or distance
	bool angleSel = std::find(angleSelection.begin(), angleSelection.end(), true) != angleSelection.end();
	bool distSel = std::find(distSelection.begin(), distSelection.end(), true) != distSelection.end();

	if (angleSel || distSel)
	{
		// We select 3 points for an angle and 2 for a distance
		int maxSelection = angleSel ? 3 : 2;

		// Get selection index
		QModelIndexList indexes = pointViews[idx]->selectionModel()->selectedIndexes();
		int index = indexes.at(0).row();

		VAMLogger::log("Point selected: " + QString::number(idx));

		// If index was already in the selection, we ignore the click
		for (int i = 0; i < selectedIdx.size(); i++)
		{
			if (index == selectedIdx[i])
			{
				return;
			}
		}

		// Otherwise we add the new point's index
		selectedIdx.push_back(index);

		// Get the point
		Point currPoint = currentSchema.getPoint(index, idx);

		// Add point and increment selection
		if (angleSel)
		{
			newAngle.addPoint(currPoint, selected++);
		}
		else
		{
			newDistance.addPoint(currPoint, selected++);
		}

		// Get pointer variables according to image index
		cv::Mat *img = &images[idx];
		cv::Mat *disp = &dispImages[idx];
		CustomLabel *label = imageLabels[idx];

		// Draw on image
		if (img->data)
		{
			// Determine Resize factors
			float imgRatio = (float)(img->cols) / (float)(img->rows);
			float labelRatio = (float)ui.imageLabel1->size().width() / (float)ui.imageLabel1->size().height();
			float factor = imgRatio < labelRatio ? (float)(label->size().height()) / (float)(img->rows) : (float)(label->size().width()) / (float)(img->cols);

			// Create image copy to draw on
			cv::resize(*img, *disp, cv::Size(0, 0), factor, factor);

			// Get size of the point
			Point p(disp->cols, disp->rows);

			if (angleSel)
			{
				// Draw circles at point coordinates and lines between them
				cv::line(*disp, newAngle.getPoint(selected - 1) * p, newAngle.getPoint(selected - 2) * p, cv::Scalar(0, 0, 255));
				cv::line(*disp, newAngle.getPoint(selected - 2) * p, newAngle.getPoint(selected - 3) * p, cv::Scalar(0, 0, 255));
				cv::circle(*disp, newAngle.getPoint(selected - 1) * p, 3, cv::Scalar(0, 0, 255));
				cv::circle(*disp, newAngle.getPoint(selected - 2) * p, 3, cv::Scalar(0, 0, 255));
				cv::circle(*disp, newAngle.getPoint(selected - 3) * p, 3, cv::Scalar(0, 0, 255));
			}
			else
			{
				// Draw circles at point coordinates and lines between them
				cv::line(*disp, newDistance.getPoint(selected - 1) * p, newDistance.getPoint(selected - 2) * p, cv::Scalar(0, 0, 255));
				cv::circle(*disp, newDistance.getPoint(selected - 1) * p, 3, cv::Scalar(0, 0, 255));
				cv::circle(*disp, newDistance.getPoint(selected - 2) * p, 3, cv::Scalar(0, 0, 255));
			}

			// Update label
			label->setPixmap(QPixmap::fromImage(cvMatToQImage(*disp)));
			label->update();
		}

		// If selected number reaches max selection, then done
		if (selected == maxSelection)
		{

			VAMLogger::log("Selection done");

			// Add new angle or distance
			if (angleSel)
			{
				currentSchema.addMeasurement(newAngle, idx);
			}
			else
			{
				currentSchema.addMeasurement(newDistance, idx);
			}

			// Clear selection variables
			clearSelections();

			// Schema modified
			schemaModified = true;

			// Enable UI
			enableUI();

			ui.infoLabel->setText(tr("Done!"));
		}
	}
}

void SchemaWindow::closeEvent(QCloseEvent *event)
{
	// Prompt for save if modified
	if (schemaModified)
	{
		VAMLogger::log("Prompt schema changed");

		QMessageBox msgBox;
		msgBox.setText(tr("The current schema has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Save");
			bool ret = saveSchema();
			if (!ret)
			{
				event->ignore();
				return;
			}
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
	delete this;
}

void SchemaWindow::keyPressEvent(QKeyEvent * event)
{
	// On escape kex we stop selection processes
	if (event->key() == Qt::Key_Escape)
	{
		VAMLogger::log("Escaped selection");

		// Clear selection variables
		clearSelections();

		// Enable UI
		enableUI();
	}
}

void SchemaWindow::resizeEvent(QResizeEvent * event)
{
	// Check for image data

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if (!images[i].data)
			continue;

		// Determine Resize factors
		float imgRatio = (float)images[i].cols / (float)images[i].rows;
		float labelRatio = (float)imageLabels[i]->size().width() / (float)imageLabels[i]->size().height();
		float sideFact = imgRatio < labelRatio ? (float)imageLabels[i]->size().height() / (float)images[i].rows : (float)imageLabels[i]->size().width() / (float)images[i].cols;

		// Resize them
		cv::resize(images[i], dispImages[i], cv::Size(0, 0), sideFact, sideFact);

		// Display images
		imageLabels[i]->setPixmap(QPixmap::fromImage(cvMatToQImage(dispImages[i])));

		// Update labels
		imageLabels[i]->update();
	}
}

Schema SchemaWindow::getCurrentSchema() const
{
	return currentSchema;
}

bool SchemaWindow::setCurrentSchema(const Schema &value)
{
	VAMLogger::log("Schema set");

	// Set schema
	currentSchema = value;
	schemaName = currentSchema.getFileName();

	// Setup UI
	setupWindow();

	return true;
}

void SchemaWindow::setCurrentProject(Project *value)
{
	currentProject = value;
}

void SchemaWindow::show()
{
	// Call parent
	QMainWindow::show();

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		// Fill images with black
		images[i] = cv::Mat(cv::Size(imageLabels[i]->size().width(), imageLabels[i]->size().height()), CV_8UC3, cv::Scalar(0, 0, 0));

		// Copy them
		images[i].copyTo(dispImages[i]);

		// Display
		imageLabels[i]->setPixmap(QPixmap::fromImage(cvMatToQImage(dispImages[i])));
	}
}

void SchemaWindow::clearSelections()
{
	// Clear selection processes
	angleSelection.assign(VAMMaxVideos, false);
	distSelection.assign(VAMMaxVideos, false);
	selectedIdx.clear();
	selected = 0;
}

void SchemaWindow::disableUI(int index)
{
	// Set varianble
	UIDisabled = true;

	// Disable UI elements
	ui.actionOpen_Images->setEnabled(false);
	ui.actionSet_Correction_Measurement->setEnabled(false);
	ui.actionSave->setEnabled(false);
	ui.actionSave_as->setEnabled(false);
	ui.statusbar->setSizeGripEnabled(false);

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		newMeasButtons[i]->setEnabled(false);
		newPointButtons[i]->setEnabled(false);
		removeMeasButtons[i]->setEnabled(false);
		removePointButtons[i]->setEnabled(false);
		renameMeasButtons[i]->setEnabled(false);
		renamePointButtons[i]->setEnabled(false);
		measViews[i]->setEnabled(false);
		if (index != i)
		{
			pointViews[i]->setEnabled(false);
			imageLabels[i]->setEnabled(false);
		}
	}
}

void SchemaWindow::enableUI()
{
	// Set variable
	UIDisabled = false;

	// Enable elements
	ui.actionOpen_Images->setEnabled(true);
	ui.actionSet_Correction_Measurement->setEnabled(true);
	ui.actionSave->setEnabled(true);
	ui.actionSave_as->setEnabled(true);
	ui.statusbar->setSizeGripEnabled(true);

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		newMeasButtons[i]->setEnabled(true);
		newPointButtons[i]->setEnabled(true);
		removeMeasButtons[i]->setEnabled(true);
		removePointButtons[i]->setEnabled(true);
		renameMeasButtons[i]->setEnabled(true);
		renamePointButtons[i]->setEnabled(true);
		measViews[i]->setEnabled(true);
		pointViews[i]->setEnabled(true);
		imageLabels[i]->setEnabled(true);
	}
}

void SchemaWindow::imageClicked(const QPoint &p, VAMImageIndex idx)
{
	// We only care for clicks if the UI is disabled
	if (UIDisabled && (!angleSelection[idx] && !distSelection[idx]))
	{
		VAMLogger::log("image click #" + QString::number(idx));

		// Get click location scaled between [0,1] (to make it scale invariant)
		Point location((double)p.x() / (double)imageLabels[idx]->size().width(), (double)p.y() / (double)imageLabels[idx]->size().height());

		// Get pointer variables according to image index
		cv::Mat *img = &images[idx];
		cv::Mat *disp = &dispImages[idx];
		CustomLabel *label = imageLabels[idx];

		// Draw on image
		if (img->data)
		{
			// Determine Resize factors
			float imgRatio = (float)(img->cols) / (float)(img->rows);
			float labelRatio = (float)ui.imageLabel1->size().width() / (float)ui.imageLabel1->size().height();
			float factor = imgRatio < labelRatio ? (float)(label->size().height()) / (float)(img->rows) : (float)(label->size().width()) / (float)(img->cols);

			// Create image copy to draw on
			cv::resize(*img, *disp, cv::Size(0, 0), factor, factor);

			// Get size of the point
			Point p(disp->cols, disp->rows);
			cv::circle(*disp, location * p, 3, cv::Scalar(0, 0, 255));

			// Update label
			label->setPixmap(QPixmap::fromImage(cvMatToQImage(*disp)));
			label->update();
		}

		// Add point
		currentSchema.addPoint(currPName, location, idx);

		// Point selection is done
		pointSelection = false;

		// Modified
		schemaModified = true;

		ui.infoLabel->setText(tr("Done!"));

		// Enable UI		
		enableUI();
	}
}

void SchemaWindow::setCorrection()
{
	bool ok;
	int imgIdx = QInputDialog::getInt(this, tr("Video Selection"), tr("Please select the index of the video to correct!"), 2, 2, vidCnt, 1, &ok);
	if (!ok)
		return;

	// Check if a side measurement is selected
	QModelIndexList indexes = ui.measView1->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a side measurement to use!"));
		return;
	}

	int index = indexes.at(0).row();

	if (currentSchema.getMeas(index, VAMImageIndex::_1)->getType() == Meas::MeasAngle)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("The selected measurement is an angle. Please select a distance!"));
		return;
	}

	schemaModified = true;

	VAMLogger::log("Use measurement for animal height: " + QString::number(index));

	// Update schema
	currentSchema.setHeightMeas(index, toIdx(imgIdx - 1));

	ui.infoLabel->setText(tr("Height measurement set."));
}
