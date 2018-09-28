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
#include "Utility.h"
#include "Project.h"
#include "ui_marker.h"

class Measurement;
class Schema;
class StillDB;
class Project;

// Class for marking measurements
class MarkerWindow :
	public QMainWindow
{
	Q_OBJECT
public:

	// Constructor and descturcotr
	MarkerWindow( QWidget *parent = 0 );
	~MarkerWindow( void );

	// Override of QMainWindow::show()
	void show();

	// Getter setter for the current measurement
	Measurement getCurrentMeasurement() const;
	bool setCurrentMeasurement( const Measurement &value, bool schemdbChange = false );

	// Getter setter for the current project
	Project *getCurrentProject() const;
	void setCurrentProject( Project *value );

private:

	// User interface
	Ui::MarkerWindow ui;

	// Auxiliary variables representing changes in the still database
	std::vector< std::vector< int >> imgIndices;

	// Helper variables representing changes in the stchema
	std::vector< std::vector< int >> pointIndices;

	// Map for changing the order of images
	std::vector< int > imgIdxMap;

	// Indicates if the current measurement contains marks set by the user
	bool measData;

	// Selecting or placing marks
	bool markerSelectionMode;

	// Current project, measurement, schema an database
	Project *currentProject;
	Measurement currentMeasurement;
	Schema currentSchema;
	StillDB currentDB;

	// Name of the measurement
	QString measurementName;

	// Index of the database and schema in the project
	int currentDBIdx;
	int currentSchemaIdx;

	// Index of the selected point -1 if no markers are selected
	int selectedIdx;

	// Index if the currently displayed image
	int currentImgIndex;

	// Index of the next unmarked point on the image
	int currentPointIndex;

	// Count of images and side images
	int imgCnt;
	std::vector< int > imgCntThresholds;

	// # of images unmarked
	int imgRem;

	// # of finished images
	int imgDone;

	// Currently displayed image - backup
	cv::Mat currentImg;

	// Currently displayed image - used for drawing on it
	cv::Mat currentDrawing;

	// Zoom state of the image view
	double scale;

	// Indicates if the measurement has been modified since opening it
	bool measurementModified;

	// List of image IDs and file names
	QStringList IDList;
	QStringList ImgPathList;

	// String list model for the list view
	QStringListModel *unmarkedID;

	// Checks if the current image in the database is etalon
	bool isGlobalEtalon( bool idxMap = false );

	// Checks if the indexth image in the measurement is etalon
	bool wasGlobalEtalon( int index );

	// Checks if the current image in the database is etalon
	bool hasEtalon(bool idxMap = false);

	// Checks if the indexth image in the measurement is etalon
	bool hadEtalon(const Measurement &oldMeas, int index);

	// Set the name of the current point
	QString getPointName();

	// Copy marker from old measurement or set the default value
	void copyMarkOrSetDefault(Measurement &oldMeas, int pIdx, int offSet, int offset2, int oldImgIdx, VAMImageIndex imageIdx);

	// Check if the database or the schema changed since the measurement was last saved 
	// And setup auxiliary variables accordingly
	bool dataBaseChanged();
	bool schemaChanged();

	// Setup markings in the measurement
	void setupMarkings();

	// Draw markers on current image
	void drawMarkings( double factor = 1.0 );

	// Display image and set related labels on the view
	void showImage();

	// Remove point from image
	void removePoint();

	// Resizes image by factor around center pos
	void resizeImage( double factor, QPointF pos );

	// Adjust the position of the scrollbars if the size of the image changed
	void adjustScrollBar( QScrollBar *scrollBar, double factor, double pos );

	// Sets default state of the window
	void resetWindow();

	// Sets the window up according to the current measurement
	void setupUI();

	// Convert an index to image index
	inline VAMImageIndex getImageIdx( int idx )
	{
		for( int i = VAMMaxVideos-1; i >= 0; i-- )
		{
			if( idx >= imgCntThresholds[ i ] )
				return toIdx( i );
		}
		return toIdx( 0 );
	}

signals:

	// Notifies main view, that a new measurement has been added
	void newData();
	void dataUpdate();

	private slots:

	// Slot for save buttons
	void saveMeasurement();
	void saveAsMeasurement();

	// Slot for confidence changed
	void confidenceChanged( int val );

	// Change marker selection mode
	void markerModeChanged();

	// Change auto corrent variable
	void autoCorrChanged( bool val );

	// Change current images
	void prevImage();
	void skipImage();

	// Jump to image
	void listDoubleClicked(QModelIndex curr);

	// Erase all markers on image
	void redoImage();

	// Slot for handling image clicks
	void imageClicked( const QPoint &p );

	// Slot for handling mouse movement over the image (for crosshair)
	void imageHovered( const QPoint &p );

protected:

	// Called on close
	void closeEvent( QCloseEvent *event );

	// Handler for keyboard events
	void keyPressEvent( QKeyEvent *event );

	// Handler for resize
	void resizeEvent( QResizeEvent *event );
};

