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

#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets\WidgetSeek.h>
#include <VLCQtWidgets\WidgetVideo.h>
#include "Utility.h"
#include "Project.h"
#include "StillDB.h"
#include "ui_video.h"
extern "C"
{
#include <libavformat/avformat.h>
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

// Class for creating still images from videos
class VideoWindow :
	public QMainWindow
{
	Q_OBJECT
public:

	// Constructor and destructor
	VideoWindow(QWidget *parent = 0);
	~VideoWindow(void);

	// Override of QMainWindow::show()
	void show();

	// Getter setter for current project
	Project *getCurrentProject() const;
	void setCurrentProject(Project *value);

	// Getter setter for current database
	StillDB getCurrentDB() const;
	bool setCurrentDB(const StillDB &value);

private:

	// The user interface
	Ui::VideoWindow ui;

	// Arrays containing ui elemets
    std::vector< QLabel* > /*currTimeLabels, maxTimeLabels,*/ titleLabels;
    std::vector< VlcWidgetSeek* > sliders;
	std::vector< QPushButton* > prevButtons, nextButtons, fbButtons, ffButtons, playButtons, pauseButtons, stopButtons;
	std::vector< VlcMedia* > media;

	// Spinboxes and checkboxes for the toolbar
	QDoubleSpinBox *etalonBox;
	QSpinBox *frameTimeBox;
	QCheckBox *etalonToggle, *videoLock, *deintToggle;

	// Video outputs and video players
    std::vector<VlcWidgetVideo*> videoOut;
    std::vector<QLayout*> videoLayouts;
    std::vector<VlcMediaPlayer*> players;

    VlcInstance *instance;

	// Current project
	Project *currentProject;

	// Current database
	StillDB currentDB;
	QString dbName;

	// Currently playing videos and frame times
	std::vector< QString > currentVideos;
	std::vector< double > frameTimes;

	// Videos
	std::vector<QStringList> videos;

	// File paths for the still images saved
	std::vector<QString> filePaths;

	// Indicates if the database has been modified
	bool DBModified;

	// Is the current still etalon
	bool etalon;

	// If true, the two videos are synchronized
	bool frameLock;

	// If true, the two videos are synchronized
	bool deinterlace;

	// Indicates if the user is dragging the video slider
	bool sliderDrag;

	// Indicates if the play should be stopped automatically
	bool autoStop;

	// Current video order
	bool videoOrderVertical;

	// Paused states of the videos
	std::vector<bool> paused;

	// Indicate if automatic playing of the next video in the list is enabled
	std::vector<bool> autoPlayEnabled;

	// Index of the current video
	std::vector<int> vidCntr;

	// Playing states of the videos
	std::vector<bool> playing;

	// Number of videos
	int videoCnt;

	// Indicates if there is a video file
	bool usingVideos;

	// Size of the etalon used
	double etalonSize;

	// Video player setup
	bool setCurrentVideo();

	// Set dafault window state
	void resetWindow();

	// Setup user interface according to the current database
	void setupUI( bool noConnect = false );

	// Stop all videos
	void stopVideos();

	private slots:

	// Change in the etalon size
	void etalonChanged(double val);

	// Checkbox clicks
	void etalonClicked(bool val);
	void frameLockClicked(bool val);
	void deintClicked(bool val);

	// Click on the still list
	void listClicked(QModelIndex curr);

	// Click on the still list
	void listDoubleClicked(QModelIndex curr);

	// Callback for change in the video sliders
	void sliderChanged(VAMImageIndex idx);

	// Functions to allow dragging the slider
	void sliderPressed(VAMImageIndex idx);

	// Save stills
	void stillSaveClicked();

	// Callback for saving side and upper image
	void imageSaved(const QString &filePath, VAMImageIndex idx);

	// Callback for video position change
    void updateSlider(float val, VAMImageIndex idx);

	// Slots for actions
	void remStill();
	void etalonStill();
	void openStill();
	void renameStill();
	void reorderVideos();
	bool doneC();
	void saveAsC();
	//void changeVidC();

	// Slots for video controls
	void pauseClicked(VAMImageIndex idx);
	void playClicked(VAMImageIndex idx);
	void playPauseClicked(VAMImageIndex idx);
	//void stopClicked(VAMImageIndex idx);
	void fbClicked(VAMImageIndex idx);
	void ffClicked(VAMImageIndex idx);
	void prevClicked(VAMImageIndex idx);
	void nextClicked(VAMImageIndex idx);
    
    // Audio
    void audioSliderChanged(int val);

	VAMImageIndex swapIndices(VAMImageIndex idx);

signals:

	// Signal to tell the main window that there is a new database
	void newData();
	void dataUpdate();


protected:

	// Called upon closing
	void closeEvent(QCloseEvent *event);
};

