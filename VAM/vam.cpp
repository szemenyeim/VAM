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


#include "VAM.h"
#include "Project.h"
#include "SchemaWindow.h"
#include "MarkerWindow.h"
#include "VideoWindow.h"
#include "PlaniWindow.h"
#include "MorphoWindow.h"
#include "CalibrationWizard.h"
#include <VideoDialog.h>
#include <QTranslator>
#include <qtextedit.h>
#include <QStandardPaths>
#include <QResource>
#include <QSettings>
#include <QtConcurrent/QtConcurrent>

VAM::VAM(QWidget *parent)
	: QMainWindow(parent), currentProject()
{
	currentProject = NULL;
	maxFileNr = 5;
	generating = false;

	// Read translation file and options
	readOptionsAndTranslations();

	// If default project, create lib
	projectLib = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).append(QString("/VATEM2"));

	QDir dir(projectLib);
	if (!dir.exists())
		dir.mkpath(".");

	VAMFileAgent::setProjPath(projectLib);
	QDir subDir(dir.absolutePath() + "/Schemas");
	subDir.mkpath(".");
	subDir.setPath(dir.absolutePath() + "/Measurements");
	subDir.mkpath(".");
	subDir.setPath(dir.absolutePath() + "/Projects");
	subDir.mkpath(".");

	// Create list models
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		vidModels.push_back(new QStringListModel());
	}

	images.resize(VAMMaxVideos, cv::Mat::zeros(480, 640, CV_8UC3));

	// Set ui into default state
	resetUI();

	// Create default project and load it
	loadCurrentProject2UI(true);

	// Default state
	projectModified = false;
	somethingModified = false;
}

VAM::~VAM()
{
	// Delete project
	if (currentProject)
		delete currentProject;

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		delete vidModels[i];
	}
}

void VAM::resetUI()
{
	// Setup UI
	ui.setupUi(this);

	// Setup toolbar
	QWidget* toolWidget = new QWidget;
	QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
	cameraNumLabel = new QLabel(this);
	cameraNumLabel->setText(tr("Number of Cameras:"));
	toolLayout->addWidget(cameraNumLabel);
	cameraNumSpin = new QSpinBox(this);
	cameraNumSpin->setValue(2);
	cameraNumSpin->setMaximum(VAMMaxVideos);
	cameraNumSpin->setMinimum(1);
	toolLayout->addWidget(cameraNumSpin);
	ui.mainToolBar->addWidget(toolWidget);

	// Connect button and action signals to slots
	connect(ui.schemaAdd, &QPushButton::clicked, this, &VAM::createSchema);
	connect(ui.measAdd, &QPushButton::clicked, this, &VAM::createMeasurement);
	connect(ui.schemaOpen, &QPushButton::clicked, this, &VAM::openSchema);
	connect(ui.measOpen, &QPushButton::clicked, this, &VAM::openMeas);
	//connect(ui.importStill, &QPushButton::clicked, this, &VAM::openDB);
	connect(ui.schemaRemove, &QPushButton::clicked, this, &VAM::deleteSchema);
	connect(ui.measRemove, &QPushButton::clicked, this, &VAM::deleteMeas);
	connect(ui.schemaEdit, &QPushButton::clicked, this, &VAM::schemaEdit);
	connect(ui.measEdit, &QPushButton::clicked, this, &VAM::measEdit);
	connect(ui.stillCreate, &QPushButton::clicked, this, &VAM::dbEdit);
	connect(ui.resetDB, &QPushButton::clicked, [this]() { resetDB(false); });
	connect(ui.stillDelete, &QPushButton::clicked, [this]() { resetDB(true); });

	connect(ui.generateOutput, &QPushButton::clicked, this, &VAM::createOutput);

	connect(ui.formatCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &VAM::formatChanged);
	connect(cameraNumSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &VAM::cameraNumChanged);

	connect(ui.actionAbout, &QAction::triggered, this, &VAM::showAbout);
	connect(ui.actionSelect_Language, &QAction::triggered, this, &VAM::selectLanguage);
	connect(ui.actionEnable_Logging, &QAction::triggered, this, &VAM::loggingToggled);
	connect(ui.actionSet_Project_Directory, &QAction::triggered, this, &VAM::createProjLib);
	connect(ui.actionOrder_Images_by_Animal_ID, &QAction::triggered, this, &VAM::orderingChanged);
	connect(ui.actionExit, &QAction::triggered, this, &VAM::exitPressed);
	connect(ui.actionNew_Project, &QAction::triggered, this, &VAM::newProject);
	connect(ui.actionOpen_Project, &QAction::triggered, this, &VAM::openProject);
	connect(ui.actionSave_As, &QAction::triggered, this, &VAM::saveAs);
	connect(ui.actionSave_Project, &QAction::triggered, this, &VAM::saveProject);
	connect(ui.actionPlanimetrics_export, &QAction::triggered, this, &VAM::doVolumetric);
	connect(ui.actionMorphometrics_export, &QAction::triggered, this, &VAM::doMorpho);

	ui.actionEnable_Logging->setText(VAMLogger::enabled ? tr("Disable Logging") : tr("Enable Logging"));
	ui.actionEnable_Logging->setChecked(VAMLogger::enabled);
	ui.actionOrder_Images_by_Animal_ID->setChecked(VAMOptions::VAMImageOrderingType == OrderByAnimal);

	vidLists = { ui.vidList1,ui.vidList2,ui.vidList3,ui.vidList4 };
	vidLabels = { ui.vidLabel1,ui.vidLabel2,ui.vidLabel3,ui.vidLabel4 };
	imgLabels = { ui.img1,ui.img2,ui.img3,ui.img4 };
	buttons = { ui.vidEdit1,ui.vidEdit2,ui.vidEdit3,ui.vidEdit4 };
	calibButtons = { ui.calibBtn1,ui.calibBtn2,ui.calibBtn3,ui.calibBtn4 };

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		connect(buttons[i], &QPushButton::clicked, std::bind(&VAM::manageVideos, this, i));
		connect(calibButtons[i], &QPushButton::clicked, std::bind(&VAM::calibBtn, this, i));
		drawImages(i);
	}

	// Setup font
	QFont font("Times", 12, QFont::Bold);
	ui.projNameLabel->setFont(font);
	QFont font1("Times", 10, QFont::Normal);
	ui.outNameLabel->setFont(font1);
	ui.stillCntLabel->setFont(font1);
	ui.outNameLabel->setText("");

	// Setup recent file menu
	QAction* recentFileAction = 0;
	for (int i = 0; i < maxFileNr; ++i) {
		recentFileAction = new QAction(this);
		recentFileAction->setVisible(false);
		connect(recentFileAction, &QAction::triggered, this, &VAM::openProject);
		recentFileActionList.append(recentFileAction);
		ui.menuOpen_Recent->addAction(recentFileActionList.at(i));
	}
	recentFileAction = new QAction(this);
	recentFileAction->setVisible(false);
	recentFileAction->setEnabled(false);
	recentFileAction->setText(tr("<Empty>"));
	recentFileActionList.append(recentFileAction);
	ui.menuOpen_Recent->addAction(recentFileAction);
	updateRecentActionList();
	generating = false;

	// Setup window buttons (to allow maximize button)
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
}

void VAM::loadCurrentProject2UI(bool def)
{
	if (def)
	{
		setProjectState(UNCREATED);
		return;
	}

	// Setup project name
	ui.projNameLabel->setText(currentProject->getName());

	// Setup combo box
	ui.formatCombo->setCurrentIndex(currentProject->getFormatIndex());

	// Setup list views
	ui.schemaCombo->setModel(currentProject->getSchemaList());
	ui.measCombo->setModel(currentProject->getMeasList());
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		QStringList orig = currentProject->getDB(0).getVideos(toIdx(i)), shortened;
		for (QString curr : orig)
		{
			shortened.push_back(curr.split("/").back());
		}
		vidModels[i]->setStringList(shortened);
		vidLists[i]->setModel(vidModels[i]);
	}

	cameraNumSpin->setValue(currentProject->getDB(0).getVideoCnt());
	cameraNumChanged(cameraNumSpin->value());

	// Default state
	projectModified = false;
	somethingModified = false;
	generating = false;

	// Disable UI conditionally
	setProjectState(currentProject->getState());

	std::vector< int > cnt = currentProject->getDB(0).getCounts();

	int fullCnt = 0;

	for (int i = 0; i < cameraNumSpin->value(); i++)
	{
		int k = cameraNumSpin->value();
		fullCnt += cnt[i];
		if (cnt[i] > 0)
		{
			images[i] = imgRead(currentProject->getDB(0).getStill(cnt[i] - 1, toIdx(i)), cv::Mat(), cv::Mat());
		}
		drawImages(i);
	}
	ui.stillCntLabel->setText(tr("Taken %1 stills from %2 cameras").arg(fullCnt).arg(cameraNumSpin->value()));

	this->resize(ui.centralWidget->size() + QSize(1, 1));

	VAMLogger::log("Project loaded to UI");
}

void VAM::createSchema()
{
	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isSchemaNew, currentProject, _1);
	if (!getName(tr("New Schema"), tr("Enter Name:"), tr("Please specify a name!"), tr("A schema with this name already exists!"), text, func))
		return;

	VAMLogger::log("Schema created");

	// Create schema
	Schema newSchem;
	newSchem.setName(text);

	// Create schema window
	SchemaWindow *schemaWindow = new SchemaWindow();
	schemaWindow->setWindowModality(Qt::ApplicationModal);
	connect(schemaWindow, &SchemaWindow::newData, this, &VAM::newElementAdded);
	connect(schemaWindow, &SchemaWindow::dataUpdate, this, &VAM::compDataChanged);

	// Setup variables and show
	schemaWindow->setCurrentProject(currentProject);
	schemaWindow->setCurrentSchema(newSchem);
	schemaWindow->show();

}

void VAM::createMeasurement()
{
	// Check for schemas and measurements
	if (!currentProject->getSchemaCnt() || !currentProject->DBCnt())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please create a schema and a database first"));
		return;
	}

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isMeasNew, currentProject, _1);
	if (!getName(tr("New Measurement"), tr("Enter Name:"), tr("Please specify a name!"), tr("A measurement with this name already exists!"), text, func))
		return;

	VAMLogger::log("Measurement created");

	// Create measurement
	Measurement newMeas;
	newMeas.setName(text);

	// Auxiliary variables
	bool ok;
	int dbIdx, schemaIdx;

	// Prompt for database
	/*QString message = tr("Select Still Database");
	while (1)
	{
		text = QInputDialog::getItem(this, tr("New Measurement"),
			message, currentProject->getDBList()->stringList(), 0, false, &ok);

		if (!ok)
			return;*/

	dbIdx = 0;// currentProject->getDBList()->stringList().indexOf(text);

		// Check if the DB is empty
		/*if (currentProject->getDB(dbIdx).getCnt() == 0)
		{
			message = tr("The selected database is empty. Please select another one!");
			continue;
		}*/

		// Add database
	newMeas.setDB(currentProject->getDB(dbIdx));

	newMeas.setIDs(currentProject->getDB(dbIdx).getModel()->stringList());

	/*break;
}*/

// Prompt for schema
	QString message = tr("Select Schema");
	while (1)
	{
		text = QInputDialog::getItem(this, tr("New Measurement"),
			message, currentProject->getSchemaList()->stringList(), 0, false, &ok);

		if (!ok)
			return;

		schemaIdx = currentProject->getSchemaList()->stringList().indexOf(text);

		int pCnt = currentProject->getSchema(schemaIdx).pointCnt();
		int vCnt = currentProject->getDB(dbIdx).getCnt();

		if (!currentProject->getSchema(schemaIdx).matches(currentProject->getDB(dbIdx).getVideoCnt()))
		{
			int btn = QMessageBox::warning(this, tr("Schema mismatch"), tr("The selected schema does not contain measurements for all cameras. Are you sure you want to use this schema?"),
				QMessageBox::Ok, QMessageBox::Cancel);
			if (btn != QMessageBox::Ok)
				continue;
		}

		// Check if schema is empty
		if (pCnt == 0)
		{
			message = tr("The selected schema is empty. Please select another one!");
			continue;
		}

		// Add schema
		newMeas.setSchema(currentProject->getSchema(schemaIdx));
		for (int i = 0; i < VAMMaxVideos; i++)
		{
			newMeas.setPoints(currentProject->getSchema(schemaIdx).pointModels[i]->stringList(), toIdx(i));
		}

		break;
	}

	// Create marker window
	MarkerWindow *markerWindow = new MarkerWindow();
	markerWindow->setWindowModality(Qt::ApplicationModal);
	connect(markerWindow, &MarkerWindow::newData, this, &VAM::newElementAdded);
	connect(markerWindow, &MarkerWindow::dataUpdate, this, &VAM::compDataChanged);

	VAMLogger::log("DB: " + QString::number(dbIdx) + " Schema: " + QString::number(schemaIdx));

	// setup window and show
	markerWindow->setCurrentProject(currentProject);
	if (markerWindow->setCurrentMeasurement(newMeas))
		markerWindow->show();
}

void VAM::manageVideos(int index)
{
	// Initiate dialog variables and callbacks
	VideoDialog *dialog = new VideoDialog(this);

    connect(dialog, &VideoDialog::newData, std::bind(&VAM::videoListChanged, this, std::placeholders::_1, toIdx(index)));
    connect(dialog, &VideoDialog::distChanged, std::bind(&VAM::videoBoxChanged, this, std::placeholders::_1, toIdx(index)));

	// Launch dialog
	dialog->showDialog(currentProject->getDB(0).getVideos(toIdx(index)));

	if (index != 0)
		dialog->setBoxVal(currentProject->getDB(0).getEtalonDistance(toIdx(index - 1)));
    else{
        dialog->hideDistBox();
    }
}


void VAM::calibBtn(int index)
{
	CalibrationWizard wizard(toIdx(index), currentProject->getAbsProjLib(), this);
	wizard.exec();
}

void VAM::doVolumetric()
{
	if (!currentProject || currentProject->getState() < OUTPUT)
	{
		QMessageBox::warning(this, tr("No measurement"), tr("You need to create a measurement before creating planimetrics measurements!"));
		return;
	}

	PlaniWindow *win = new PlaniWindow();
	win->setWindowModality(Qt::ApplicationModal);

	win->setCurrentProject(currentProject);
	win->show();
}

void VAM::doMorpho()
{
	if (!currentProject || currentProject->getState() < OUTPUT)
	{
		QMessageBox::warning(this, tr("No measurement"), tr("You need to create a measurement before creating morphometrics measurements!"));
		return;
	}

	MorphoWindow *win = new MorphoWindow();
	win->setWindowModality(Qt::ApplicationModal);

	win->setCurrentProject(currentProject);
	win->show();
}

void VAM::videoBoxChanged(double val, VAMImageIndex idx)
{
    if( idx == 0 )
        return;
    
    projectModified = true;
    
    // Get new etalon distance
	StillDB DB = currentProject->getDB(0);
    DB.setEtalonDistance(val, toIdx(idx - 1));
	currentProject->removeDB(0);
	currentProject->addDB(DB);
    currentProject->save(currentProject->getName());
    
    VAMLogger::log("Etalon distance #" + QString::number(idx) + ":  " + QString::number(val));
}

void VAM::deleteSchema()
{
	// Check selection
	int index = ui.schemaCombo->currentIndex();
	if (index < 0)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a schema to delete!"));
		return;
	}

	VAMLogger::log("Schema deleted: " + QString::number(index));

	// Delete schema
	projectModified = true;
	currentProject->removeSchema(index);

	somethingModified = true;
	updateProjectState();
}

void VAM::deleteMeas()
{
	// Check selection
	int index = ui.measCombo->currentIndex();
	if (index < 0)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a measurement to delete!"));
		return;
	}

	VAMLogger::log("Measurement deleted: " + QString::number(index));

	// Delete measurement
	projectModified = true;
	currentProject->removeMeasurement(index);

	somethingModified = true;
	updateProjectState();
}

void VAM::resetDB(bool keepVideos)
{
	VAMLogger::log("Database reset: " + QString::number(keepVideos));

	StillDB DB;
	StillDB old = currentProject->getDB(0);
	DB.setName(old.getName());
	DB.setFileName(old.getFileName());
	DB.setVideoCnt(old.getVideoCnt());
	if (keepVideos)
	{
		for (int i = 0; i < DB.getVideoCnt(); i++)
		{
			DB.setVideos(toIdx(i), old.getVideos(toIdx(i)));
			if (i > 0)
			{
				DB.setEtalonDistance(old.getEtalonDistance(toIdx(i)), toIdx(i));
			}
		}
	}
    else
    {
        for (int i = 0; i < DB.getVideoCnt(); i++)
        {
            vidModels[i]->setStringList(QStringList());
            vidLists[i]->setModel(vidModels[i]);
        }
    }
	currentProject->removeDB(0);
	currentProject->addDB(DB);

	// UpdateProject
	projectModified = true;
	somethingModified = true;
	updateProjectState();
}

void VAM::openSchema()
{
	// Prompt for file
	QString schemaName = QFileDialog::getOpenFileName(this, tr("Open Schema File"), projectLib + "/Schemas", tr("Schema Files (*.schem)"));
	if (schemaName.isEmpty())
		return;

	// Read file
	Schema schem;
	if (!schem.read(schemaName))
	{
		VAMLogger::log("Schema open failed");
		QMessageBox::critical(this, tr("Error opening schema file"),
			tr("Please try another location"));
		return;
	}

	VAMLogger::log("Schema opened");

	// Add it to the project
	currentProject->addSchema(schem);
	projectModified = true;

	somethingModified = true;
	updateProjectState();
}

void VAM::openMeas()
{
	// Prompt for file
	QString measurementName = QFileDialog::getOpenFileName(this, tr("Open Measurement File"), projectLib + "/Measurements", tr("Measurement Files (*.meas)"));
	if (measurementName.isEmpty())
		return;

	// Read file
	Measurement meas;
	if (!meas.read(measurementName))
	{
		VAMLogger::log("Measurement open failed");
		QMessageBox::critical(this, tr("Error opening measurement file"),
			tr("Please try another location"));

		return;

	}

	VAMLogger::log("Measurement opened");

	// Add it to the project
	currentProject->addMeasurement(meas);
	projectModified = true;

	somethingModified = true;
	updateProjectState();
}

/*void VAM::openDB()
{
	// Prompt for file
	QString dbName = QFileDialog::getOpenFileName(this, tr("Open Video Database File"), projectLib, tr("Still Database Files (*.stillDB)"));
	if (dbName.isEmpty())
		return;

	// Read file
	StillDB db;
	if (!db.read(dbName))
	{
		VAMLogger::log("Database open failed");
		QMessageBox::critical(this, tr("Error opening database file"),
			tr("Please try another location"));

		return;

	}

	VAMLogger::log("Database opened");

	// Add it to the project
	currentProject->removeDB(0);
	currentProject->addDB(db);
	cameraNumSpin->setValue(db.getVideoCnt());
	cameraNumChanged(db.getVideoCnt());
	projectModified = true;

	somethingModified = true;
	updateProjectState();
}*/

void VAM::dbEdit()
{
	VAMLogger::log("Database edit " + QString::number(0 /*index.row()*/));

	// Create window
	VideoWindow *videoWindow = new VideoWindow();
	videoWindow->setWindowModality(Qt::ApplicationModal);
	connect(videoWindow, &VideoWindow::newData, this, &VAM::newElementAdded);
	connect(videoWindow, &VideoWindow::dataUpdate, this, &VAM::compDataChanged);

	// Setup window
	videoWindow->setCurrentProject(currentProject);
	if (videoWindow->setCurrentDB(currentProject->getDB(0 /*index.row()*/)))
		videoWindow->show();
}

void VAM::schemaEdit()
{
	int index = ui.schemaCombo->currentIndex();

	if (index < 0) {
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a schema to edit!"));
		return;
	}

	VAMLogger::log("Schema edit " + QString::number(index));

	// Create window
	SchemaWindow *schemaWindow = new SchemaWindow();
	schemaWindow->setWindowModality(Qt::ApplicationModal);
	connect(schemaWindow, &SchemaWindow::newData, this, &VAM::newElementAdded);
	connect(schemaWindow, &SchemaWindow::dataUpdate, this, &VAM::compDataChanged);

	// Setup window
	schemaWindow->setCurrentProject(currentProject);
	if (schemaWindow->setCurrentSchema(currentProject->getSchema(index)))
		schemaWindow->show();
}

void VAM::measEdit()
{
	int index = ui.measCombo->currentIndex();

	if (index < 0) {
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a measurement to edit!"));
		return;
	}

	VAMLogger::log("Measurement edit " + QString::number(index));

	// Auxiliary variables
	QString text, message = tr("Select Still Database");
	int dbIdx = currentProject->getDBList()->stringList().indexOf(currentProject->getMeasurement(index).getDB().getName());
	int schemaIdx = currentProject->getSchemaList()->stringList().indexOf(currentProject->getMeasurement(index).getSchema().getName());
	bool ok;

	// Check for the existence of the database and schema used for the measurement
	bool noDB = dbIdx == -1;
	bool noSchema = schemaIdx == -1;

	// If there is no database, prompt for a new one
	while (noDB)
	{
		text = QInputDialog::getItem(this, tr("The database for the measurement is not loaded."),
			message, currentProject->getDBList()->stringList(), 0, false, &ok);

		if (!ok)
			return;

		dbIdx = currentProject->getDBList()->stringList().indexOf(text);

		if (currentProject->getDB(dbIdx).getCnt() == 0)
		{
			message = tr("The selected database is empty. Please select another one!");
			continue;
		}

		// Set it
		Measurement meas = currentProject->getMeasurement(index);
		meas.setDB(currentProject->getDB(dbIdx));
		currentProject->addMeasurement(meas);

		VAMLogger::log("Database used had to change: " + QString::number(dbIdx));

		break;
	}

	// If there is no schema, prompt for a new one
	message = tr("Select Schema");
	while (noSchema)
	{
		text = QInputDialog::getItem(this, tr("The schema for the measurement is not loaded."),
			message, currentProject->getSchemaList()->stringList(), 0, false, &ok);

		if (!ok)
			return;

		schemaIdx = currentProject->getSchemaList()->stringList().indexOf(text);

		int pCnt = currentProject->getSchema(schemaIdx).pointCnt();
		int vCnt = currentProject->getDB(dbIdx).getCnt();

		// Check if schema is empty
		if (pCnt == 0)
		{
			message = tr("The selected schema is empty. Please select another one!");
			continue;
		}

		VAMLogger::log("Schema used had to change: " + QString::number(schemaIdx));

		// Set it
		Measurement meas = currentProject->getMeasurement(index);
		meas.setSchema(currentProject->getSchema(schemaIdx));
		currentProject->addMeasurement(meas);

		break;
	}

	// Create window
	MarkerWindow *markerWindow = new MarkerWindow();
	markerWindow->setWindowModality(Qt::ApplicationModal);
	connect(markerWindow, &MarkerWindow::newData, this, &VAM::newElementAdded);
	connect(markerWindow, &MarkerWindow::dataUpdate, this, &VAM::compDataChanged);

	// Setup window
	markerWindow->setCurrentProject(currentProject);
	if (markerWindow->setCurrentMeasurement(currentProject->getMeasurement(index), (noDB || noSchema)))
		markerWindow->show();
}

/*void VAM::renameMeas()
{
	// Check selection
	QModelIndexList indexes = ui.measListView->selectionModel()->selectedIndexes();
	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a measurement to rename!"));
		return;
	}

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isMeasNew, currentProject, _1);
	if (!getName(tr("Rename Measurement"), tr("Enter Name:"), tr("Please specify a name!"), tr("A measurement with this name already exists!"), text, func))
		return;

	int index = indexes.at(0).row();
	VAMLogger::log("Measurement rename" + QString::number(index));

	// Rename
	projectModified = true;
	currentProject->renameMeasurement(index, text);
}

void VAM::renameSchema()
{
	// Check selection
	QModelIndexList indexes = ui.shemaListView->selectionModel()->selectedIndexes();
	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a schema to rename!"));
		return;
	}

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isSchemaNew, currentProject, _1);
	if (!getName(tr("Rename Schema"), tr("Enter Name:"), tr("Please specify a name!"), tr("A schema with this name already exists!"), text, func))
		return;

	int index = indexes.at(0).row();
	VAMLogger::log("Schema rename" + QString::number(index));

	// Rename
	projectModified = true;
	currentProject->renameSchema(index, text);
}

void VAM::renameDB()
{
	// Check selection
	QModelIndexList indexes = ui.dbListView->selectionModel()->selectedIndexes();
	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a database to rename!"));
		return;
	}

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isDBNew, currentProject, _1);
	if (!getName(tr("Rename Database"), tr("Enter Name:"), tr("Please specify a name!"), tr("A database with this name already exists!"), text, func))
		return;

	int index = indexes.at(0).row();
	VAMLogger::log("Database rename" + QString::number(index));

	// Rename
	projectModified = true;
	currentProject->renameDB(index, text);
}*/

void VAM::createOutput()
{
	// Save project
	saveProject();
	generating = true;

	VAMLogger::log("Output generation");

	QDir dir(currentProject->getAbsProjLib());
	dir.setPath(dir.absolutePath() + "/Output");
	if (!dir.exists())
		dir.mkpath(".");

	QString ext;
	switch (currentProject->getFormatIndex()) {
	case XLSX:
		ext = tr("XLSX files (*.xlsx)");
		break;
	case HTML:
		ext = tr("HTML files (*.html)");
		break;
	case CSV:
		ext = tr("CSV files (*.csv)");
		break;
	default:
		break;
	}

	QString fName = QFileDialog::getSaveFileName(this, tr("Select output file"), dir.absolutePath() + "/result", ext);

	if (fName.isEmpty())
		return;

	int imgCnt = 0;
	for (int i = 0; i < currentProject->getMeasCnt(); i++)
	{
		Measurement *curr = currentProject->getMeasPtr(i);
		if( !curr->isConnected() )
			connect(curr->signal, &Messenger::computed, this, &VAM::updateBar);
		curr->setConnected(true);
		imgCnt++;
	}
	int DBCnt = currentProject->getDB(0).getCnt() - currentProject->getDB(0).getVideoCnt()*(currentProject->getDB(0).getGlobalEtalonIndex().size());
	imgCnt *= DBCnt;
	ui.progressBar->setMaximum(imgCnt); 
	ui.progressBar->setValue(0);


	currentProject->setOutputName(fName);
	QtConcurrent::run(currentProject, &Project::generateOutput);

}

void VAM::createProjLib()
{
	// Get project lib
	QString text = QFileDialog::getExistingDirectory(this, tr("Select Project Directory"), projectLib, QFileDialog::DontUseNativeDialog);

	if (text.isEmpty())
		return;

	VAMLogger::log("Projlib created");

	// Set new project lib
	projectLib = text;
}

void VAM::formatChanged(int index)
{
	if (!currentProject)
		return;

	// Change output format
	projectModified = true;
	FormatType type = static_cast<FormatType>(index);
	currentProject->setFormatIndex(type);

	VAMLogger::log("Format changed" + QString::number(index));

	somethingModified = true;
	updateProjectState();

}

void VAM::cameraNumChanged(int newCameraNum)
{
	// Update database
	StillDB DB = currentProject->getDB(0);
	DB.setVideoCnt(newCameraNum);
	DB.save(DB.getFileName());
	currentProject->removeDB(0);
	currentProject->addDB(DB);

	// Update visibility
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		bool isVid = i < newCameraNum;
		vidLists[i]->setVisible(isVid);
		vidLabels[i]->setVisible(isVid);
		imgLabels[i]->setVisible(isVid);
		buttons[i]->setVisible(isVid);
		calibButtons[i]->setVisible(isVid);
	}

	somethingModified = true;
	updateProjectState();
}

void VAM::setProjectState(ProjectState state)
{
	// Enable or disable UI elements
	ui.schemaAdd->setEnabled(state >= SCHEMA);
	ui.resetDB->setEnabled(state >= VIDEO);
	ui.measAdd->setEnabled(state >= MEASUREMENT);
	ui.schemaOpen->setEnabled(state >= SCHEMA);
        ui.stillCreate->setEnabled(state >= VIDEO);
	ui.stillDelete->setEnabled(state >= STILL);
	ui.measOpen->setEnabled(state >= MEASUREMENT);
	ui.schemaRemove->setEnabled(state >= SCHEMA);
	ui.measRemove->setEnabled(state >= MEASUREMENT);
	ui.schemaEdit->setEnabled(state >= SCHEMA);
	//ui.importStill->setEnabled(state >= STILL);
	ui.measEdit->setEnabled(state >= MEASUREMENT);

	ui.formatCombo->setEnabled(state >= OUTPUT);
	ui.measCombo->setEnabled(state >= MEASUREMENT);
	ui.schemaCombo->setEnabled(state >= SCHEMA);

	cameraNumSpin->setEnabled(state >= VIDEO);
	cameraNumLabel->setEnabled(state >= VIDEO);

	ui.generateOutput->setEnabled(state >= OUTPUT);
	ui.actionSave_As->setEnabled(state >= VIDEO);
	ui.actionSave_Project->setEnabled(state >= VIDEO);

	ui.progressBar->setEnabled(state >= OUTPUT);

	QPixmap noSign, yesSign;
	noSign.load(":/VAM/Icons/1466084143_delete.png");
	yesSign.load(":/VAM/Icons/1466084211_Accept.png");

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		vidLabels[i]->setEnabled(state >= VIDEO);
		imgLabels[i]->setEnabled(state >= STILL);
		vidLists[i]->setEnabled(state >= VIDEO);
		buttons[i]->setEnabled(state >= VIDEO);
		calibButtons[i]->setEnabled(state >= VIDEO);
	}

	if (state < OUTPUT)
		ui.outNameLabel->setText("");

	// Set state indicator pixmaps
	ui.videoLabel->setPixmap(state > VIDEO ? yesSign : noSign);
	ui.stillLabel->setPixmap(state > STILL ? yesSign : noSign);
	ui.schemaLabel->setPixmap(state > SCHEMA ? yesSign : noSign);
	ui.measLabel->setPixmap(state > MEASUREMENT ? yesSign : noSign);
	ui.outLabel->setPixmap(state > OUTPUT ? yesSign : noSign);
}

bool VAM::isProjNew(QString projName)
{
	// Project is new if there is no directory for it yet
	QDir dir(projectLib + "/" + projName);
	return !dir.exists();
}

void VAM::showAbout()
{
	// Display about information
	QMainWindow *window = new QMainWindow(this);
	window->setWindowModality(Qt::ApplicationModal);
	window->setWindowTitle(tr("About VAM"));

	QLabel *label = new QLabel(window);

	label->setText("VATEM2 --- Video Assisted Measurement of Animals http://github.com/szemenyeim/VATEM2 \n"
		"Copyright( C ) 2017  Marton Szemenyei\n"
		"Produced by the University of Veterinary Sciences, Budapest (www.univet.hu/en)\n\n"
		"This program is free software : you can redistribute it and / or modify\n"
		"it under the terms of the GNU General Public License as published by\n"
		"the Free Software Foundation, either version 3 of the License, or\n"
		"( at your option ) any later version.\n"
		"\n"
		"This program is distributed in the hope that it will be useful,\n"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the\n"
		"GNU General Public License for more details.\n"
		"\n"
		"You should have received a copy of the GNU General Public License\n"
		"along with this program. If not, see http://www.gnu.org/licenses/ \n\n"
		"Credits:\n\n"
                "FFmpeg library - LGPLv2.1 http://www.ffmpeg.org/ \n"
                "Qt library - LGPLv3.0 http://www.qt.io/ \n"
                "VLC library - LGPLv2.1 http://www.videolan.org/vlc/libvlc.html \n"
                "VLC-Qt library - LGPLv3.0 http://vlc-qt.tano.si/ \n"
                "OpenCV library - BSD license http://opencv.org/ \n"
		"ZBar library - Zero license http://zbar.sourceforge.net/ \n"
		"Libiconv library - LGPL https://www.gnu.org/software/libiconv/ \n"
		"XLSX Writer Lib - Free BSD https://github.com/jmcnamara/libxlsxwriter \n"
		"The Mesa 3D Graphics library - MIT license http://www.mesa3d.org/egl.html \n"
		"ICU - International Components for Unicode http://www.unicode.org/copyright.html \n"
		"Microsoft Visual Studio 2015 Enterprise Edition - https://www.visualstudio.com/ \n"
		"Flexera InstallShield Limited Edition - http://learn.flexerasoftware.com/content/IS-EVAL-InstallShield-Limited-Edition-Visual-Studio \n"
		"Icons designed by Momentum Design Lab - Creative Commons (Attribution 3.0 Unported) http://momentumdesignlab.com/ \n"
                "Additional icons by ASP.NET icons http://aspneticons.com/ \n"
                "Volume icon designed by Yummygum https://yummygum.com/ \n"
		"Main application icon designed by icons8 - Creative Commons (Attribution-NoDerivs 3.0 Unported) http://icons8.com/ \n"
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

void VAM::selectLanguage()
{
	// Get current language index
	int index = languages.indexOf(currentLang);
	if (index == -1)
		index = 0;

	// Get new language from dialog
	bool ok;
	QString newLang = QInputDialog::getItem(this, tr("Select Language"), tr("Choose a language from the list"), languages, index, false, &ok);
	if (!ok)
		return;

	VAMLogger::log("Language: " + newLang);

	// Get new language index
	index = languages.indexOf(newLang);
	currentLang = newLang;

	// Setup translator for new language
	QTranslator* translator = new QTranslator();
	translator->load(":/VAM/Translations/" + translationFiles.at(index));
	QApplication::installTranslator(translator);

	// Retranslate UI (make sure to keep project modified flag as it might reset)
	bool temp = projectModified;
	ui.retranslateUi(this);
	projectModified = temp;

	// Open translation file
	updateConfig();

}

void VAM::loggingToggled()
{

	VAMLogger::log("Logging disabled");

	VAMLogger::enabled = !VAMLogger::enabled;

	VAMLogger::log("Logging enabled");

	ui.actionEnable_Logging->setText(VAMLogger::enabled ? tr("Disable Logging") : tr("Enable Logging"));

	// Open config file
	updateConfig();
}

void VAM::orderingChanged()
{
	VAMOptions::VAMImageOrderingType = VAMOptions::VAMImageOrderingType == OrderByAnimal ? OrderByImageType : OrderByAnimal;

	VAMLogger::log("Ordering changed to" + QString(VAMOptions::VAMImageOrderingType != OrderByAnimal ? "OrderByImageType" : "OrderByAnimal"));

	updateConfig();
}

void VAM::exitPressed()
{

	VAMLogger::log("Bye! (Menu)");

	this->close();
}

void VAM::openProject()
{
	// Check if project is modified and warn
	if (projectModified)
	{

		VAMLogger::log("Project modified prompt");

		QMessageBox msgBox;
		msgBox.setText(tr("The current project has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{

			VAMLogger::log("Saved");
			saveProject();
		}
		else if (ret == QMessageBox::Cancel)
		{

			VAMLogger::log("Cancel");
			return;
		}
		else
		{
			VAMLogger::log("Discard");
		}
	}

	QString fileName;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!(action->data().toString().isEmpty()))
		fileName = action->data().toString();
	else
		// Prompt for project file
		fileName = QFileDialog::getOpenFileName(this, tr("Open Project File"), projectLib + "/Projects", tr("VAM Projects (*.VAMproj)"));

	if (fileName.isEmpty())
		return;


	VAMLogger::log("Open proj");

	// Read up projectfile
	currentProject = new Project(Project::read(fileName));
	adjustForCurrentFile(fileName);
	currentProject->setGenProjLib(projectLib);

	// Setup UI
	projectName = currentProject->getName();
	loadCurrentProject2UI();
}

void VAM::newProject()
{
	// Check if project is modified and warn
	if (projectModified)
	{

		VAMLogger::log("Project modified prompt");
		QMessageBox msgBox;
		msgBox.setText(tr("The current project has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Saved");
			saveProject();
		}
		else if (ret == QMessageBox::Cancel)
		{
			VAMLogger::log("Cancel");
			return;
		}
		else
		{
			VAMLogger::log("Discard");
		}
	}

	VAMLogger::log("New project");

	if (currentProject)
		delete currentProject;

	currentProject = new Project();

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&VAM::isProjNew, this, _1);
	if (!getName(tr("New Project"), tr("Enter Name:"), tr("Please specify a name!"), tr("A project with this name already exists!"), text, func))
		return;

	currentProject->setProjName(text);
	currentProject->setProjLib("/Projects/" + text);
	currentProject->setFormatIndex(CSV);
	currentProject->setState(VIDEO);

	VAMFileAgent::setProjPath(projectLib);
	currentProject->setGenProjLib(projectLib);

	QDir dir(currentProject->getAbsProjLib());
	if (!dir.exists())
		dir.mkpath(".");

	// Check if writing was succesful
	if (!dir.exists())
	{
		QMessageBox::critical(this, tr("Error writing directory"), tr("The selected project library could not be written. Please choose another one!"));
		delete currentProject;
		return;
	}

	QDir subDir(dir.absolutePath() + "/Database");
	subDir.mkpath(".");
	subDir.setPath(subDir.absolutePath() + "/images");
	subDir.mkpath(".");

	StillDB DB;
	DB.setName(text);
	DB.setVideoCnt(2);
	QString dbName = currentProject->getAbsProjLib() + "/Database/" + DB.getName() + ".stillDB";
	DB.save(dbName);
	currentProject->addDB(DB);

	currentProject->save(currentProject->getAbsProjLib() + "/" + currentProject->getName() + ".vamproj");
	adjustForCurrentFile(currentProject->getAbsProjLib() + "/" + currentProject->getName() + ".vamproj");

	// Reset UI
	loadCurrentProject2UI(false);

}

void VAM::saveProject()
{
	// Open Dialog for name selection
	if (projectName.isEmpty())
	{
		// Prompt for project file
		projectName = /*QFileDialog::getSaveFileName( this, tr( "Save Project File" ), */currentProject->getName()/*, tr( "VAM Projects (*.VAMproj)" ) )*/;

		if (projectName.isEmpty())
			return;

		VAMLogger::log("First save project");
	}

	VAMLogger::log("Save project");

	// Save project
	currentProject->save(projectName);
	projectModified = false;

}

void VAM::saveAs()
{

	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&VAM::isProjNew, this, _1);
	if (!getName(tr("New Project"), tr("Enter Name:"), tr("Please specify a name!"), tr("A project with this name already exists!"), text, func))
		return;

	currentProject->setProjName(text);
	currentProject->setProjLib(projectLib + "/" + text);
	currentProject->setFormatIndex(CSV);

	QDir dir(projectLib + "/" + text);
	if (!dir.exists())
		dir.mkpath(".");

	// Check if writing was succesful
	if (!dir.exists())
	{
		QMessageBox::critical(this, tr("Error writing directory"), tr("The selected project library could not be written. Please choose another one!"));
		delete currentProject;
		return;
	}

	QDir subDir(dir.absolutePath() + "/Database");
	subDir.mkpath(".");
	subDir.setPath(subDir.absolutePath() + "/images");
	subDir.mkpath(".");

	// Open Dialog for name selection
	projectName = /*QFileDialog::getSaveFileName( this, tr( "Save Project File" ),*/ currentProject->getAbsProjLib() + "/" + currentProject->getName() + ".VAMproj"/*, tr( "VAM Projects (*.VAMproj)" ) )*/;

	if (projectName.isEmpty())
		return;

	VAMLogger::log("Save As project");

	// Save project
	currentProject->save(projectName);
	adjustForCurrentFile(currentProject->getAbsProjLib() + "/" + currentProject->getName() + ".vamproj");

	projectModified = false;
}

void VAM::drawImages(int i)
{
	cv::Mat tmp;
	// Determinae resize factor
	float imgRatio = (float)images[i].cols / (float)images[i].rows;

	float labelRatio = (float)imgLabels[i]->size().width() / (float)imgLabels[i]->size().height();
	float resFact = imgRatio < labelRatio ? (float)imgLabels[i]->size().height() / (float)images[i].rows :
		(float)imgLabels[i]->size().width() / (float)images[i].cols;

	// Resize them
	cv::resize(images[i], tmp, cv::Size(0, 0), resFact, resFact);
	imgLabels[i]->setPixmap(QPixmap::fromImage(cvMatToQImage(tmp)));

	// Update labels
	imgLabels[i]->update();
}

void VAM::readOptionsAndTranslations()
{
	// Open options file
	QString appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(QString(""));

	QDir dir(appDir);

	// If there is no options file, create one
	if (!dir.exists())
	{
		dir.mkpath(".");
		QFile file(appDir + "/config.ini");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			return;
		}

		QTextStream out(&file);


		out << "English\n";
		out << "false\n";
		out << "0\nend\n";

	}

	// Read options file
	QFile optFile(appDir + "/config.ini");
	if (!optFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream optIn(&optFile);

	// Read up current language string
	currentLang = optIn.readLine();

	// Setup logger
	VAMLogger::enabled = optIn.readLine().compare("false");

	// SetupOrderingType
	VAMOptions::VAMImageOrderingType = optIn.readLine().compare("0") ? OrderByAnimal : OrderByImageType;

	// Get recent file list
	recentFilePaths = readQStringList(optIn);

	// Close
	optFile.close();

	// Open translation file
	QFile file(":/VAM/Translations/translations.tr");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream in(&file);

	// Read available languages and matching translation files
	languages = readQStringList(in);
	translationFiles = readQStringList(in);
	// Close
	file.close();

	// Look up current language
	int index = languages.indexOf(currentLang);

	if (index == -1)
		return;

	// Load current language
	QTranslator* translator = new QTranslator();
	translator->load(":/VAM/Translations/" + translationFiles.at(index));
	QApplication::installTranslator(translator);

	VAMLogger::log("Translations read successful");
}

void VAM::newElementAdded()
{
	projectModified = true;

	VAMLogger::log("New element signaled");
}

void VAM::compDataChanged()
{
	somethingModified = true;

	std::vector< int > cnt = currentProject->getDB(0).getCounts();

	int fullCnt = 0;

	for (int i = 0; i < cameraNumSpin->value(); i++)
	{
		fullCnt += cnt[i];
		if (cnt[i] > 0)
			images[i] = imgRead(currentProject->getDB(0).getStill(cnt[i] - 1, toIdx(i)), cv::Mat(), cv::Mat());
		drawImages(i);
	}

	ui.stillCntLabel->setText(tr("Taken %1 stills from %2 cameras").arg(fullCnt).arg(cameraNumSpin->value()));

	updateProjectState();
}

void VAM::videoListChanged(QStringList newList, VAMImageIndex idx)
{
	StillDB DB = currentProject->getDB(0);
	DB.setVideos(idx, newList);
	if( DB.getCnt() )
	{
		DB.setUsingVideos(!newList.isEmpty());
	}
	DB.save(DB.getFileName());
	currentProject->removeDB(0);
	currentProject->addDB(DB);
	QStringList orig = currentProject->getDB(0).getVideos(idx), shortened;
	for (QString curr : orig)
	{
		shortened.push_back(curr.split("/").back());
	}
	vidModels[idx]->setStringList(shortened);

	somethingModified = true;
	updateProjectState();
}

void VAM::updateConfig()
{
	// Open config file
	QString appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(QString(""));

	QFile file(appDir + "/config.ini");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream out(&file);

	// Update current language
	out << currentLang << "\n";

	out << (VAMLogger::enabled ? "true" : "false") << "\n";
	out << (VAMOptions::VAMImageOrderingType == OrderByAnimal ? "1" : "0") << "\n";

	writeQStringList(recentFilePaths, out);

	// Close
	file.close();
}

void VAM::updateProjectState()
{
	StillDB DB = currentProject->getDB(0);
	bool videoDone = true;
	for (int i = 0; i < DB.getVideoCnt(); i++)
	{
		if (DB.getVideos(toIdx(i)).isEmpty() && DB.getUsingVideos())
		{
			videoDone = false;
			break;
		}
	}

	if (!videoDone) {
		setProjectState(VIDEO);
		currentProject->setState(VIDEO);
		return;
	}
	if (DB.getCnt() == 0) {
		setProjectState(STILL);
		currentProject->setState(STILL);
		return;
	}
	if (currentProject->getSchemaCnt() == 0) {
		setProjectState(SCHEMA);
		currentProject->setState(SCHEMA);
		return;
	}
	if (currentProject->getMeasCnt() == 0) {
		setProjectState(MEASUREMENT);
		currentProject->setState(MEASUREMENT);
		return;
	}
	if (somethingModified)
	{
		setProjectState(OUTPUT);
		currentProject->setState(OUTPUT);
		return;
	}
	setProjectState(FINISHED);
	currentProject->setState(FINISHED);
}

void VAM::closeEvent(QCloseEvent *event)
{
	// Prompt for save if modified
	if (projectModified)
	{

		VAMLogger::log("Project modified prompt");
		QMessageBox msgBox;
		msgBox.setText(tr("The current project has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{

			VAMLogger::log("Save project");
			saveProject();
			event->accept();
		}
		else if (ret == QMessageBox::Cancel)
		{

			VAMLogger::log("Cancel");
			event->ignore();
		}
		else
		{

			VAMLogger::log("Discard");
			event->accept();
		}
	}
	else
	{
		event->accept();
	}

	VAMLogger::log("Bye!");
}

void VAM::resizeEvent(QResizeEvent * event)
{
	for (int i = 0; i < cameraNumSpin->value(); i++)
		drawImages(i);
}

void VAM::adjustForCurrentFile(const QString &filePath)
{

	recentFilePaths.removeAll(filePath);
	recentFilePaths.prepend(filePath);
	while (recentFilePaths.size() > maxFileNr)
		recentFilePaths.removeLast();

	updateConfig();
	// see note
	updateRecentActionList();
}

void VAM::updateRecentActionList()
{

	int itEnd = 0;
	if (recentFilePaths.size() <= maxFileNr)
		itEnd = recentFilePaths.size();
	else
		itEnd = maxFileNr;

	for (int i = 0; i < itEnd; ++i) {
		QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
		recentFileActionList.at(i)->setText(strippedName);
		recentFileActionList.at(i)->setData(recentFilePaths.at(i));
		recentFileActionList.at(i)->setVisible(true);
	}

	for (int i = itEnd; i < maxFileNr; ++i)
		recentFileActionList.at(i)->setVisible(false);

	recentFileActionList.back()->setVisible(recentFilePaths.isEmpty());
}

void VAM::updateBar()
{
	if (generating)
	{
		int curr = ui.progressBar->value() + 1;
		int max = ui.progressBar->maximum();
		ui.progressBar->setValue(curr);
		ui.outNameLabel->setText(tr("Saving image %1 of %2").arg(curr).arg(max));

		// Write Output file
		if (curr >= max)
		{
			int animCnt = 0, measCnt = 0;
			for (int i = 0; i < currentProject->getMeasCnt(); i++)
			{
				Measurement *curr = currentProject->getMeasPtr(i);
				auto anims = curr->getAnimals();
				animCnt += anims.size();
				for (int j = 0; j < anims.size(); j++)
				{
					measCnt += anims[j].getCnt();
				}
			}

			ui.outNameLabel->setText(tr("Saved %1 animals with %2 measurements to").arg(animCnt).arg(measCnt) + " " + currentProject->getOutputName());

			somethingModified = false;
			updateProjectState();
			generating = false;

			QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr("Output Generation Successful!"));
		}
	}
}
