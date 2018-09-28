//  VAM --- Video Assisted Measurement of Animals
//	Copyright( C ) 2016  M·rton Szemenyei  

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

#define LIBVLC_PLUGINS_DIR "plugins"
#include "VideoWindow.h"
#include <QString>
#include <QMultiMap>
#include <QTime>
#include <QApplication>
#include <qprogressdialog.h>
extern "C"
{
#include <vlc\vlc.h>
#include <vlc\libvlc_media_player.h>
}
#include <VLCQtCore\Audio.h>
#include <VLCQtCore\Video.h>
#include <stdio.h>

VAMImageIndex VideoWindow::swapIndices(VAMImageIndex idx)
{
	if (videoOrderVertical)
	{
		if (idx == _2)
			idx = _3;
		else if (idx == _3)
			idx = _2;
	}
	return idx;
}


VideoWindow::VideoWindow(QWidget *parent)
	: QMainWindow(parent)
{
	qunsetenv("VLC_PLUGIN_PATH");

	VlcCommon::setPluginPath(QString(LIBVLC_PLUGINS_DIR));

	instance = new VlcInstance(VlcCommon::args(), this);
	playing.resize(VAMMaxVideos);
	paused.resize(VAMMaxVideos);
	vidCntr.resize(VAMMaxVideos);
	autoPlayEnabled.resize(VAMMaxVideos);
	players.resize(VAMMaxVideos);
	videoOut.resize(VAMMaxVideos);
	sliders.resize(VAMMaxVideos);
	media.resize(VAMMaxVideos);
	//videos.resize(VAMMaxVideos);

	// Default values
	resetWindow();
}


VideoWindow::~VideoWindow(void)
{
	// Delete players
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		delete players[i];
		delete videoOut[i];
	}
}

void VideoWindow::show()
{
	// Call parent function
	QMainWindow::show();

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));

		// Setup model
		if (idx < videoCnt)
		{
			paused[idx] = true;

			// Set plaing status
			playing[idx] = false;

			players[i]->stop();
			// Setup media
			currentVideos[idx] = videos[idx].at(0);
			QString vidName = currentVideos[idx];
			VAMFileAgent::openFile(vidName);
			media[i] = new VlcMedia(vidName, true, instance);
			//players[i]->open(media[i]);
		}
	}
}

void VideoWindow::resetWindow()
{
	// Setup UI
	ui.setupUi(this);

	// Set default values
	DBModified = false;
	etalon = false;
	sliderDrag = true;
	frameLock = false;
	videoOrderVertical = false;
	paused.resize(VAMMaxVideos, false);
	autoPlayEnabled.resize(VAMMaxVideos, true);
	dbName = "";

	// Create Tool widget
	QWidget* toolWidget = new QWidget;
	QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
	QLabel *label = new QLabel(this);


	// Create box for frameRate
	/*QString TT(tr("This value is used for skipping back to the next keyframe. If skipping back does not work, set this to a higher value."));
	label = new QLabel(this);
	label->setText(tr("Frame Time (ms):"));
	label->setToolTip(TT);
	toolLayout->addWidget(label);
	frameTimeBox = new QSpinBox(this);
	frameTimeBox->setMinimum(50);
	frameTimeBox->setMaximum(1000);
	frameTimeBox->setValue(100);
	frameTimeBox->setSingleStep(25);
	frameTimeBox->setToolTip(TT);
	toolLayout->addWidget(frameTimeBox);*/

	// Checkboxes for video lock and etalon
	QString TT3 = tr("Use this to lock the videos together. (Pausing, resuming, etc. one of the videos will affect all of them)");
	videoLock = new QCheckBox(this);
	videoLock->setText(tr("Lock Videos"));
	videoLock->setToolTip(TT3);
	toolLayout->addWidget(videoLock);
	QString TT5 = tr("Toggle deinterlace mode.");
	deintToggle = new QCheckBox(this);
	deintToggle->setText(tr("Deinterlace"));
	deintToggle->setToolTip(TT5);
	toolLayout->addWidget(deintToggle);
	QString TT4 = tr("Toggle Etalon.");
	etalonToggle = new QCheckBox(this);
	etalonToggle->setText(tr("Etalon"));
	etalonToggle->setToolTip(TT4);
	toolLayout->addWidget(etalonToggle);
	// Create box for etalon size
	label->setText(tr("Etalon Size (meters):"));
	toolLayout->addWidget(label);
	etalonBox = new QDoubleSpinBox(this);
	toolLayout->addWidget(etalonBox);

	// Set the spacing
	toolLayout->setContentsMargins(0, 0, 15, 0);
	ui.toolBar->addWidget(toolWidget);

	// Setup UI element vectors
	//currTimeLabels = { ui.actTime1,		ui.actTime2,		ui.actTime3,		ui.actTime4 };
	//maxTimeLabels = { ui.duration1,		ui.duration2,		ui.duration3,		ui.duration4 };
	titleLabels = { ui.videoName1,		ui.videoName2,		ui.videoName3,		ui.videoName4 };
	prevButtons = { ui.prevVid1,		ui.prevVid2,		ui.prevVid3,		ui.prevVid4 };
	nextButtons = { ui.nextVid1,		ui.nextVid2,		ui.nextVid3,		ui.nextVid4 };
	fbButtons = { ui.frameBack1,		ui.frameBack2,		ui.frameBack3,		ui.frameBack4 };
	ffButtons = { ui.frameForward1,	ui.frameForward2,	ui.frameForward3,	ui.frameForward4 };
	playButtons = { ui.play1,			ui.play2,			ui.play3,			ui.play4 };
	videoLayouts = { ui.videoL1,	ui.videoL2,	ui.videoL3,	ui.videoL4 };
	//pauseButtons = { ui.pause1,ui.pause2, ui.pause3, ui.pause4 };
	//stopButtons = { ui.stop1,ui.stop2, ui.stop3, ui.stop4 };


	//Connect ui signlas to handler slots
	connect(etalonBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &VideoWindow::etalonChanged);
	connect(etalonToggle, &QCheckBox::stateChanged, this, &VideoWindow::etalonClicked);
	connect(videoLock, &QCheckBox::stateChanged, this, &VideoWindow::frameLockClicked);
	connect(deintToggle, &QCheckBox::stateChanged, this, &VideoWindow::deintClicked);
	connect(ui.stillImageList, &QListView::clicked, this, &VideoWindow::listClicked);
	connect(ui.stillImageList, &QListView::doubleClicked, this, &VideoWindow::listDoubleClicked);
	connect(ui.volumeSlider, &QSlider::valueChanged, this, &VideoWindow::audioSliderChanged);

	connect(ui.actionDelete_still, &QAction::triggered, this, &VideoWindow::remStill);
	connect(ui.actionSave_stills, &QAction::triggered, this, &VideoWindow::stillSaveClicked);
	connect(ui.actionOpen_still, &QAction::triggered, this, &VideoWindow::openStill);
	connect(ui.actionRename_still, &QAction::triggered, this, &VideoWindow::renameStill);
	connect(ui.actionVideo_Order, &QAction::triggered, this, &VideoWindow::reorderVideos);
	connect(ui.actionEtalon, &QAction::triggered, this, &VideoWindow::etalonStill);
	connect(ui.actionSave, &QAction::triggered, this, &VideoWindow::doneC);
	connect(ui.actionSave_as, &QAction::triggered, this, &VideoWindow::saveAsC);
	connect(ui.actionDone, &QAction::triggered, this, &VideoWindow::close);

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		// Create player nad renderer
		videoOut[i] = new VlcWidgetVideo(this);
		sliders[i] = new VlcWidgetSeek(this);
		sliders[i]->setMaximumHeight(100);
		sliders[i]->setMinimumHeight(50);
		videoLayouts[i]->addWidget(videoOut[i]);
		videoLayouts[i]->addWidget(sliders[i]);
		players[i] = new VlcMediaPlayer(instance);
		players[i]->setVideoWidget(videoOut[i]);
		videoOut[i]->setMediaPlayer(players[i]);
		sliders[i]->setMediaPlayer(players[i]);

	}

	// Setup window buttons
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

}

void VideoWindow::setupUI(bool noConnect)
{
	// Setup etalon size
	connect(players[0], &VlcMediaPlayer::snapshotTaken, std::bind(&VideoWindow::imageSaved, this, std::placeholders::_1, toIdx(0)));

	// Set vector sizes
	currentVideos.resize(VAMMaxVideos);
	frameTimes.resize(VAMMaxVideos, 500);

	// Setup model
	ui.stillImageList->setModel(currentDB.getModel());

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		// Setup model
		float totalWidth = 0, totalHeight = 0;
		if (idx < videoCnt)
		{
			// Enable/disable previous/next video buttons
			prevButtons[i]->setEnabled(false);
			nextButtons[i]->setEnabled(1 < videos[idx].size());

			// Set video titles
			titleLabels[i]->setText("(1/" + QString::number(videos[idx].size()) + "): " + currentVideos[idx]);

			// Unhide UI elements for the side video
			sliders[i]->setVisible(true);
			titleLabels[i]->setVisible(true);
			//maxTimeLabels[i]->setVisible(true);
			//currTimeLabels[i]->setVisible(true);
			prevButtons[i]->setVisible(true);
			nextButtons[i]->setVisible(true);
			fbButtons[i]->setVisible(true);
			ffButtons[i]->setVisible(true);
			playButtons[i]->setVisible(true);
			videoOut[i]->setVisible(true);
		}
		else
		{
			// Hide UI elements for the side video
			sliders[i]->setVisible(false);
			titleLabels[i]->setVisible(false);
			videoOut[i]->setVisible(false);
			//maxTimeLabels[i]->setVisible(false);
			//currTimeLabels[i]->setVisible(false);
			prevButtons[i]->setVisible(false);
			nextButtons[i]->setVisible(false);
			fbButtons[i]->setVisible(false);
			ffButtons[i]->setVisible(false);
			playButtons[i]->setVisible(false);
			//stopButtons[ i ]->setVisible( false );
			//pauseButtons[ i ]->setVisible( false );
		}

		if (!noConnect)
		{
			// Connections
			//connect(sliders[i], &QSlider::sliderReleased, std::bind(&VideoWindow::sliderChanged, this, toIdx(i)));
			//connect(sliders[i], &QSlider::sliderPressed, std::bind(&VideoWindow::sliderPressed, this, toIdx(i)));
			//connect( pauseButtons[ i ], &QPushButton::clicked, std::bind( &VideoWindow::pauseClicked, this, toIdx( i ) ) );
			connect(playButtons[i], &QPushButton::clicked, std::bind(&VideoWindow::playPauseClicked, this, toIdx(i)));
			//connect( stopButtons[ i ], &QPushButton::clicked, std::bind( &VideoWindow::stopClicked, this, toIdx( i ) ) );
			connect(fbButtons[i], &QPushButton::clicked, std::bind(&VideoWindow::fbClicked, this, toIdx(i)));
			connect(ffButtons[i], &QPushButton::clicked, std::bind(&VideoWindow::ffClicked, this, toIdx(i)));
			connect(prevButtons[i], &QPushButton::clicked, std::bind(&VideoWindow::prevClicked, this, toIdx(i)));
			connect(nextButtons[i], &QPushButton::clicked, std::bind(&VideoWindow::nextClicked, this, toIdx(i)));

			// Video handlers
			connect(players[i], &VlcMediaPlayer::positionChanged, std::bind(&VideoWindow::updateSlider, this, std::placeholders::_1, toIdx(i)));
			etalonBox->setValue(currentDB.getGlobalEtalonSize());
			etalonBox->setEnabled(false);
		}
	}

	videoLock->setEnabled(videoCnt > 1);

	// Default state
	DBModified = false;

}

void VideoWindow::stopVideos()
{
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		players[idx]->stop();
	}
}

Project *VideoWindow::getCurrentProject() const
{
	return currentProject;
}

void VideoWindow::setCurrentProject(Project *value)
{
	currentProject = value;
}

StillDB VideoWindow::getCurrentDB() const
{
	return currentDB;
}

bool VideoWindow::setCurrentDB(const StillDB & value)
{
	currentDB = value;
	dbName = currentDB.getFileName();
	videoCnt = value.getVideoCnt();
	videos = value.getVideos();
	for (int i = 0; i < videoCnt; i++)
	{
		for (int j = videos[i].size() - 1; j >= 0; j--)
		{
			if (!VAMFileAgent::openFile(videos[i][j]))
			{
				videos[i].erase(videos[i].begin() + j);
			}
		}

		if (videos[i].isEmpty())
		{
			videos[i].push_back("");
		}
	}

	// Setup current video an UI
	return setCurrentVideo();
}

bool VideoWindow::setCurrentVideo()
{
	// Get video lists
	videos.resize(videoCnt);

	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		QStringList &values = currentDB.getVideos(toIdx(i));

		VAMLogger::log("Videos added to video view: " + QString::number(values.size()));

		// Play first video
		vidCntr[idx] = 0;
	}

	// Override the current database with the ordered videos
	//currentDB.addVideos( videos );

	// setup the user interface
	setupUI();

	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		paused[idx] = true;
	}

	return true;
}

void VideoWindow::etalonChanged(double val)
{
	// Modified
	DBModified = true;

	// Get new etalon size
	currentDB.setGlobalEtalonSize(etalonBox->value());

	VAMLogger::log("Etalon size:  " + QString::number(etalonBox->value()));
}

void VideoWindow::etalonClicked(bool val)
{
	// Get new etalon checked state
	etalon = etalonToggle->isChecked();
	QModelIndexList indexes = ui.stillImageList->selectionModel()->selectedIndexes();

	etalonBox->setEnabled(false);

	VAMLogger::log("Etalon changed:  " + QString::number(val));

	if (indexes.isEmpty())
	{
		return;
	}

	// Modified
	DBModified = true;

	// Get index
	int index = indexes.at(0).row();

	if( etalon)
		currentDB.addEtalon(index);
	else
		currentDB.removeEtalon(index);

	etalonBox->setEnabled(etalon);
}

void VideoWindow::frameLockClicked(bool val)
{
	// Get new frame lock checked state
	frameLock = videoLock->isChecked();

	VAMLogger::log("Frame lock:  " + QString::number(val));
}

void VideoWindow::deintClicked(bool val)
{
	// Get new frame lock checked state
	deinterlace = deintToggle->isChecked();

	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		libvlc_video_set_deinterlace(players[idx]->core(), deinterlace ? "bob" : NULL);
	}

	VAMLogger::log("Deinterlace:  " + QString::number(val));
}

void VideoWindow::listClicked(QModelIndex curr)
{
	VAMLogger::log("Still selected:  " + QString::number(curr.row()));

	// Get correct etalons vector
	bool isEtalon = currentDB.getEtalons()[curr.row()];

	// Set etalon button's checked state according to the etalon status of the clicked element
	etalonToggle->setChecked(isEtalon);

}

void VideoWindow::listDoubleClicked(QModelIndex curr)
{
	int idx = curr.row();

	VAMLogger::log("Still double clicked:  " + QString::number(idx));

	std::vector< float > positions = currentDB.getStillTimes(idx);

	for (int i = 0; i < videoCnt; i++)
	{

		VAMImageIndex idx = swapIndices(toIdx(i));
		players[idx]->pause();
		paused[idx] = true;
		players[idx]->setPosition(positions[idx]);
	}
}

void VideoWindow::stillSaveClicked()
{
	VAMLogger::log("Still save");

	QString filePath(currentProject->getAbsProjLib());

	filePaths.clear();
	filePaths.resize(videoCnt, "");

	for (int i = 0; i < videoCnt; i++)
	{

		VAMImageIndex idx = swapIndices(toIdx(i));
		// Set file path of the still
		filePaths[i] = currentProject->getAbsProjLib() + "/Database/images/temp_" + QString::number(idx) + ".jpg";
		players[idx]->video()->takeSnapshot(filePaths[i]);

	}
}

void VideoWindow::imageSaved(const QString &filePath, VAMImageIndex idx)
{
	idx = toIdx(filePath.split("_").back().split(".")[0].toInt());
	idx = swapIndices(idx);
	filePaths[idx] = filePath;

	// This check is needed because for some reason QtAV's videoCapture calls this function twice
	for (int i = 0; i < videoCnt; i++)
	{
		if (filePaths[i].isEmpty())
		{
			return;
		}
	}

	VAMLogger::log("Reading QR codes");

	// Display progress
	QProgressDialog progress("Reading QR codes...", "", 0, VAMMaxVideos, this);
	progress.setAutoClose(false);
	progress.setCancelButton(0);
	progress.setWindowModality(Qt::WindowModal);
	progress.setWindowFlags(Qt::Dialog | Qt::Desktop);
	//progress.exec();

	QString ID;

	for (int i = 0; i < videoCnt; i++)
	{
		progress.setValue(i);

		// Read QR
		ID = readQRBarCode(filePaths[i]);

		// If no QR on the side image, try the upper
		if (ID.isEmpty())
		{
			break;
		}
	}

	bool foundCode = ID.isEmpty();

	VAMLogger::log("QR: " + ID);
	progress.cancel();

	// Prompt for ID name (the read QR is the default)
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&StillDB::isIDNew, &currentDB, _1);
	if (!getName(tr("Specify ID"),
		foundCode ? tr("No QR/Barcode found") : tr("Found QR/Barcode:"),
		tr("Please specify a name!"),
		tr("An animal with this ID already exists!"),
		ID,
		func))
	{
		// Delete stills
		for (int i = 0; i < videoCnt; i++)
		{
			QString path = filePaths[i];
			VAMFileAgent::openFile(path);
			QFile::remove(filePaths[i]);

			// Reset paths
			filePaths.clear();
			filePaths.resize(videoCnt, "");

			return;
		}
	}

	// Modified
	DBModified = true;

	// Add still
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx = swapIndices(toIdx(i));
		// Set file path of the still
		QFile img(filePaths[i]);
		filePaths[i] = currentProject->getAbsProjLib() + "/Database/images/" + ID + "_" + QString::number(idx) + ".jpg";
		img.rename(filePaths[i]);
		VAMFileAgent::abs2rel(filePaths[i]);
		currentDB.addStill(filePaths[i], ID, players[i]->position(), toIdx(i));

		// Set etalons
		if (etalon)
			currentDB.addEtalon(currentDB.getCnt(toIdx(i)) - 1);
	}

	// Reset paths
	filePaths.clear();
	filePaths.resize(videoCnt, "");
}

void VideoWindow::updateSlider(float val, VAMImageIndex idx)
{

	idx = swapIndices(idx);
	// Set duration labels
		//maxTimeLabels[idx]->setText(QTime(0, 0).addMSecs(players[idx]->length()).toString("m:ss"));
		//int frameCnt = players[idx]->position() / frameTimes[idx];
		//currTimeLabels[idx]->setText(QTime(0, 0).addMSecs(players[idx]->position()).toString("m:ss") + ":" + QString::number(frameCnt));

	// If we are far from the video's end, we enable auto play
	if (players[idx]->length() - players[idx]->position()*players[idx]->length() > 500)
	{
		autoPlayEnabled[idx] = true;
	}

	// If we're in a paused state, we pause the video
	// This is needed to make sure that the next video stays paused if the previous was when it triggered autoplay
	// It is possible for a paused video to trigger autoplay if the user drags the slider
	if (paused[idx])
	{
		players[idx]->pause();
	}

	// If there is no slider drag (sliderDrag is false if the user drags the slider)
	if (sliderDrag)
	{
		// Then update the values of the slider
				//sliders[idx]->setMaximum(players[idx]->length());
		//sliders[idx]->setValue(players[idx]->position());
	}

	// If we are close to the video's end, and autoplay is enabled
	if (autoPlayEnabled[idx] && (players[idx]->length() - players[idx]->position()*players[idx]->length() <= 500))
	{
		VAMLogger::log("Side autoplay");

		// We disable auto play to prevent it from triggering more than once
		players[idx]->pause();
		paused[idx] = true;
		playing[idx] = false;
		playButtons[idx]->setIcon(QIcon(":/VAM/Icons/1462036191_Play.png"));
		//autoPlayEnabled[idx] = false;

		// Play next video
		//nextClicked(idx);
	}
}

void VideoWindow::remStill()
{

	// Check if there is a selected still
	QModelIndexList indexes = ui.stillImageList->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a still to delete!"));
		return;
	}

	// Modified
	DBModified = true;

	// Get index
	int index = indexes.at(0).row();

	VAMLogger::log("Still removed: " + QString::number(index));

	// Delete still
	currentDB.deleteStill(index);

}

void VideoWindow::etalonStill()
{
	// Check if there is a selected still
	QModelIndexList indexes = ui.stillImageList->selectionModel()->selectedIndexes();

	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a still!"));
		return;
	}

	// Modified
	DBModified = true;

	// Get index
	int index = indexes.at(0).row();

	// Get etalons vector
	bool isEtalon = currentDB.getEtalons()[index];

	VAMLogger::log("Etalon changed: nr " + QString::number(index) + " to " + QString::number(!isEtalon));

	// Change the action's checked state
	ui.actionEtalon->setChecked(!isEtalon);

	if (!isEtalon)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("The selected still does not contain an etalon!"));
		return;
	}

	// Otherwise add new etalon
	currentDB.toggleGlobalEtalonIndex(index);
}

void VideoWindow::openStill()
{
	QStringList ID;
	std::vector<QStringList> stillNames(VAMMaxVideos);

	for (int i = 0; i < videoCnt; i++)
	{
		// Open dialog for image
		stillNames[i] = QFileDialog::getOpenFileNames(this, tr("Open Image Files #") + QString::number(i), currentProject->getAbsProjLib() + "/Databases/images", tr("Image Files (*.bmp *.dds *.gif *.ico *.jpg *.jpeg *.tga *.tif *.tiff *.pbm *.pgm *.png *.ppm *.xbm *.xpm)"));

		if (stillNames[i].isEmpty())
			return;

	}

	// Check for equal still counts
	bool ok = true;
	for (int i = 1; i < videoCnt; i++)
	{
		if (stillNames[i].size() != stillNames[0].size())
		{
			ok = false;
			break;
		}
	}

	if (!ok)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select an equal number of side and upper stills to open!"));
		return;
	}

	int fileCnt = stillNames[0].size();

	// Read QR
	for (int i = 0; i < fileCnt; i++)
	{
		ID.push_back("");

		for (int j = 0; j < videoCnt; j++)
		{
			ID[i] = readQRBarCode(stillNames[j][i]);
		}
		bool foundCode = ID.isEmpty();

		// Prompt for ID
		using std::placeholders::_1;
		std::function<bool(QString)> func = std::bind(&StillDB::isIDNew, &currentDB, _1);
		if (!getName(tr("Specify ID"),
			foundCode ? tr("No QR/Barcode found") : tr("Found QR/Barcode:"),
			tr("Please specify a name!"),
			tr("An animal with this ID already exists!"),
			foundCode ? ID[i] = stillNames[0][i].split("/").back().split(".")[0] : ID[i],
			func))
			return;

		// Add still
		for (int j = 0; j < videoCnt; j++)
		{
			currentDB.addStill(stillNames[j][i], ID[i], 0, toIdx(j), true);
		}
	}

	VAMLogger::log("Stills opened");

	// Modified
	DBModified = true;

}

void VideoWindow::renameStill()
{
	// Check if there is a still selected
	QModelIndexList indexes = ui.stillImageList->selectionModel()->selectedIndexes();
	if (indexes.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a still to rename!"));
		return;
	}

	// Prompt for new ID
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&StillDB::isIDNew, &currentDB, _1);
	if (!getName(tr("Rename Still"), tr("Enter ID:"), tr("Please specify a name!"), tr("A still with this name already exists!"), text, func))
		return;

	int index = indexes.at(0).row();
	VAMLogger::log("Still renamed: " + QString::number(index));

	// Modified
	DBModified = true;

	// Rename still
	currentDB.renameStill(index, text);
}

void VideoWindow::reorderVideos()
{
	videoOrderVertical = !videoOrderVertical;

	setupUI(true);

	bool temp = frameLock;
	frameLock = true;
	pauseClicked(toIdx(0));
	frameLock = temp;
}

bool VideoWindow::doneC()
{
	// If no name yet
	if (dbName.isEmpty())
	{
		// Prompt for project file
		dbName = /*QFileDialog::getSaveFileName( this, tr( "Save Database" ),*/ currentProject->getAbsProjLib() + "/Databases/" + currentDB.getName() + ".stillDB"/*, tr( "VAM Still Database (*.stillDB)" ) )*/;

		if (dbName.isEmpty())
			return false;

		VAMLogger::log("Database new save");

		// Signal that there is a new database
		emit newData();
	}

	if (currentDB.getCnt() > 0 && currentDB.getGlobalEtalonIndex().empty())
	{
		auto etalons = currentDB.getEtalons();
		bool noEtalon = false;
		for (int i = 0; i < currentDB.getIDs().size(); i++)
		{
			if (!etalons[i])
			{
				noEtalon = true;
				break;
			}
		}
		if (noEtalon)
		{
			QMessageBox msgBox;
			msgBox.setText(tr("There is no global etalon"));
			msgBox.setInformativeText(tr("Do you want to save the database anyway?"));
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			msgBox.setDefaultButton(QMessageBox::No);
			int ret = msgBox.exec();

			if (ret == QMessageBox::No)
			{
				return false;
			}
		}
	}

	VAMLogger::log("Database save");

	// Save DB
	currentDB.save(dbName);

	// Add/update database
	currentProject->addDB(currentDB);
	emit dataUpdate();

	// No longer modified
	DBModified = false;
	return true;
}

void VideoWindow::saveAsC()
{
	// Prompt for name
	QString text;
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&Project::isDBNew, currentProject, _1);
	if (!getName(tr("New Video database"), tr("Enter Name:"), tr("Please specify a name!"), tr("A database with this name already exists!"), text, func))
		return;

	// Set name
	currentDB.setName(text);

	// Prompt for project file
	dbName = /*QFileDialog::getSaveFileName( this, tr( "Save Database" ),*/ currentProject->getAbsProjLib() + "/Database/" + currentDB.getName() + ".stillDB"/*, tr( "VAM Still Database (*.stillDB)" ) )*/;

	if (dbName.isEmpty())
		return;

	VAMLogger::log("Database save as");

	// Signal that there is a new database
	emit newData();
	emit dataUpdate();

	// Make sure new database doesn't delete removed stills, as they are still used by the old database
	currentDB.clearStillsToDelete();

	// Save DB
	currentDB.save(dbName);

	// Add/update database
	currentProject->addDB(currentDB);

	// No longer modified
	DBModified = false;
}

/*void VideoWindow::changeVidC()
{
	// Get new video strings
	QStringList fileNames;
	for( int i = 0; i < videoCnt; i++ )
	{
		fileNames = QFileDialog::getOpenFileNames( this, tr( "Change Video File(s)" ) + " #" + QString::number( i + 1 ), currentProject->getProjLib(), tr( "Video Files (*.avi *.mp4 *.mkv *.vid *.mv4 *.mts *.m4v)" ) );
		if( fileNames.isEmpty() )
			continue;
		DBModified = true;
		videos[ i ] = fileNames;
	}

	if( DBModified )
	{
		currentDB.addVideos( videos );
		setCurrentDB( currentDB );
		show();
		DBModified = true;
	}

}*/

void VideoWindow::pauseClicked(VAMImageIndex idx)
{

	VAMLogger::log("Pause #" + QString::number(idx));

	// Pause
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx2 = swapIndices(toIdx(i));
		// Pause other as well if frames are locked
		if (idx == i || frameLock)
		{
			players[idx2]->pause();
			playButtons[idx2]->setIcon(QIcon(":/VAM/Icons/1462036191_Play.png"));
			paused[idx2] = true;
		}
	}
}

void VideoWindow::playClicked(VAMImageIndex idx)
{

	VAMLogger::log("Play #" + QString::number(idx));

	// Resume
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx2 = swapIndices(toIdx(i));
		// Resume other as well if frames are locked
		if (idx == i || frameLock)
		{

			playButtons[idx2]->setIcon(QIcon(":/VAM/Icons/1462036201_Pause.png"));

			// Playing
			paused[idx2] = false;

			players[idx2]->resume();
			if (!playing[idx2])
			{
				players[idx2]->open(media[idx2]);
				playing[idx2] = true;
				qApp->processEvents();
			}
		}
	}
}

void VideoWindow::playPauseClicked(VAMImageIndex idx)
{
	VAMImageIndex idx2 = swapIndices(idx);
	if (idx2 >= videoCnt)
		return;
	if (!paused[idx])
	{
		pauseClicked(idx2);
	}
	else {
		playClicked(idx2);
	}
}

/*void VideoWindow::stopClicked( VAMImageIndex idx )
{
	if( idx >= videoCnt )
		return;

	VAMLogger::log( "Stop #" + QString::number( idx ) );

	// Stop
	for( int i = 0; i < videoCnt; i++ )
	{
		// Stop other as well if frames are locked
		if( idx == i || frameLock )
		{
			players[ i ]->stop();
			playing[ i ] = false;

			// Set slider values
			sliders[ i ]->setSliderPosition( 0 );
			currTimeLabels[ i ]->setText( QTime( 0, 0 ).toString( "m:ss" ) );
		}
	}
}*/

void VideoWindow::fbClicked(VAMImageIndex idx)
{

	if (swapIndices(idx) >= videoCnt)
		return;

	VAMLogger::log("FrameBack #" + QString::number(idx));

	// Jump back some time
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx2 = swapIndices(toIdx(i));
		if (idx == idx2 || frameLock)
		{
			float fps = libvlc_media_player_get_fps(players[idx2]->core());
			if (fps <= 0.f) fps = 20;
			float frameTime = 1000.f / fps;
			float offset = 1.f / media[i]->duration() * 2 * frameTime;
			players[idx2]->setPosition(players[idx2]->position() - offset);
		}
	}
}

void VideoWindow::ffClicked(VAMImageIndex idx)
{
	if (swapIndices(idx) >= videoCnt)
		return;

	VAMLogger::log("FrameForward #" + QString::number(idx));

	// Step formward
	for (int i = 0; i < videoCnt; i++)
	{
		VAMImageIndex idx2 = swapIndices(toIdx(i));
		if (idx == idx2 || frameLock)
		{
			/*float fps = libvlc_media_player_get_fps(players[idx2]->core());
			if (fps <= 0.f) fps = 20;
			float frameTime = 1000.f / fps;
			float offset = 1.f / media[i]->duration() * 2 * frameTime;
			players[idx2]->setPosition(players[idx2]->position() + offset);*/
			libvlc_media_player_next_frame(players[idx2]->core());
		}
	}
}

void VideoWindow::prevClicked(VAMImageIndex idx)
{
	VAMImageIndex idx2 = swapIndices(idx);
	VAMLogger::log("Prev #" + QString::number(idx) + " :" + QString::number(vidCntr[idx]));

	// Play previous video
	if (vidCntr[idx2] > 0)
	{
		// Set paused state
		paused[idx2] = players[idx]->state() == Vlc::State::Paused;

		// Stop and play
		players[idx]->stop();
		QString vidName = videos[idx2][--vidCntr[idx2]];
		VAMFileAgent::openFile(vidName);
		media[idx2] = new VlcMedia(vidName, true, instance);
		players[idx]->open(media[idx2]);

		// Update video name
		titleLabels[idx]->setText("(" + QString::number(vidCntr[idx2] + 1) + "/" + QString::number(videos[idx2].size()) + "): " + videos[idx2][vidCntr[idx2]]);

	}

	// Update previous and next buttons
	prevButtons[idx]->setEnabled(vidCntr[idx2] > 0);
	nextButtons[idx]->setEnabled(vidCntr[idx2] < videos[idx2].size() - 1);
}

void VideoWindow::nextClicked(VAMImageIndex idx)
{
	VAMImageIndex idx2 = swapIndices(idx);
	VAMLogger::log("Next #" + QString::number(idx) + " :" + QString::number(vidCntr[idx]));

	// Play next video
	if (vidCntr[idx2] < videos[idx2].size() - 1)
	{
		// Set paused state
		paused[idx2] = players[idx]->state() == Vlc::State::Paused;

		// Stop and play
		players[idx]->stop();
		QString vidName = videos[idx2][++vidCntr[idx2]];
		VAMFileAgent::openFile(vidName);
		media[idx2] = new VlcMedia(vidName, true, instance);
		players[idx]->open(media[idx2]);

		currentVideos[idx2] = videos[idx2].at(vidCntr[idx2]);

		// Update video name
		titleLabels[idx]->setText("(" + QString::number(vidCntr[idx2] + 1) + "/" + QString::number(videos[idx2].size()) + "): " + videos[idx2][vidCntr[idx2]]);

	}

	// Update previous and next buttons
	prevButtons[idx]->setEnabled(vidCntr[idx2] > 0);
	nextButtons[idx]->setEnabled(vidCntr[idx2] < videos[idx2].size() - 1);
}

void VideoWindow::sliderChanged(VAMImageIndex idx)
{
	if (!sliderDrag)
	{
		VAMLogger::log("Dragged #" + QString::number(idx));

		// Get slider value and set video to it
		//int val = sliders[idx]->sliderPosition();
		//players[idx]->setPosition(val);
		sliderDrag = true;

		for (int i = 0; i < videoCnt; i++)
		{
			VAMImageIndex idx2 = swapIndices(toIdx(i));
			if (frameLock && idx2 != idx)
			{
				// If the slider position is larger than the other video's length, then set it to the end
				//val = val > sliders[idx]->maximum() ? sliders[idx]->maximum() : val;
				//players[idx]->setPosition(val);
				sliderDrag = true;
			}
		}
	}
}

void VideoWindow::sliderPressed(VAMImageIndex idx)
{
	VAMLogger::log("Drag #" + QString::number(idx));

	// Set slider drag
	sliderDrag = false;
}

// Audio
void VideoWindow::audioSliderChanged(int val)
{
	VAMLogger::log("Volume #" + QString::number(val));
	for (int i = 0; i < videoCnt; i++)
	{
		players[i]->audio()->setVolume(val);
	}
}
void VideoWindow::closeEvent(QCloseEvent *event)
{
	// Prompt for saving database
	if (DBModified)
	{
		VAMLogger::log("Database change prompt");
		QMessageBox msgBox;
		msgBox.setText(tr("The current video database has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Save");
			bool ret = doneC();
			if (!ret)
			{
				event->ignore();
				return;
			}
			// Stop players
			stopVideos();
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
			// Stop players
			stopVideos();
			event->accept();
		}
	}
	else
	{
		VAMLogger::log("Bye");
		// Stop players
		stopVideos();
		event->accept();
	}
	delete this;
}
