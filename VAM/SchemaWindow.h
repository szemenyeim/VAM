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
#include <opencv2/opencv.hpp>
#include "Utility.h"
#include "Schema.h"
#include "Project.h"
#include "ui_schema.h"

// Class for defining and managing schemas
class SchemaWindow :
	public QMainWindow
{
	Q_OBJECT
public:

	// Constructor and desctructor
	SchemaWindow( QWidget *parent = 0 );
	~SchemaWindow( void );

	// Getter and setter for the current schema
	Schema getCurrentSchema() const;
	bool setCurrentSchema( const Schema &value );

	// Setter for current project
	void setCurrentProject( Project *value );

	// Overwrite of QMainwindow::show
	void show();

private:

	// UI
	Ui::SchemaWindow ui;

	// Containers for enabling/disabling the ui elements
	std::vector< QPushButton* > newPointButtons, removeMeasButtons, removePointButtons, renameMeasButtons, renamePointButtons;
	std::vector< QToolButton* > newMeasButtons;
	std::vector< QListView* > pointViews, measViews;
	std::vector< CustomLabel* > imageLabels;
	std::vector< QLabel* > ptLabels, measLabels, imnameLabels;

	// Store point indices that were selected during the creation of a measurement
	std::vector< int > selectedIdx;

	// Number of points selected during the creation of a measurement
	int selected;

	// Current schema
	Schema currentSchema;

	// Current project
	Project *currentProject;

        // Video Count
        int vidCnt;

	// Name of the schema
	QString schemaName;

	// Is schema modified
	bool schemaModified;

	// Name of the point currently under creation
	QString currPName;

	// Are parts of the UI disabled
	bool UIDisabled;

	// Is a measurement deifnition in process
	std::vector< bool > angleSelection;
	std::vector< bool > distSelection;

	// Is a point definition in process
	bool pointSelection;

	// Angle/Distance currently under definition
	Angle newAngle;
	Distance newDistance;

	// Images (currently displayed and backup original versions)
	std::vector< cv::Mat > images;
	std::vector< cv::Mat > dispImages;

	// Set default UI state
	void resetWindow();

	// Setup UI according to the current schema
	void setupWindow();

	// Clear point slections used for measurement definition
	void clearSelections();

	// Enable or disable parts of the UI to make sure the user clicks in the right places during a measurement or point definition
	void disableUI( int index );
	void enableUI();

	private slots:

	// Action slots
	void setCorrection();
	void openImages();
	bool saveSchema();
	void saveAsSchema();

	// Add, delete and rename points/measurements
	void newAngleC( VAMImageIndex idx );
	void newDistC( VAMImageIndex idx );
	void newPoint( VAMImageIndex idx );
	void delPoint( VAMImageIndex idx );
	void delMeas( VAMImageIndex idx );
	void renPoint( VAMImageIndex idx );
	void renMeas( VAMImageIndex idx );

	// Click handler for point lists
	void listClicked( VAMImageIndex idx );

	// Click handler for images
	void imageClicked( const QPoint &p, VAMImageIndex idx );

signals:

	// Signal main window if a new schema is created
	void newData();
	void dataUpdate();

protected:

	// Called on close
	void closeEvent( QCloseEvent *event );

	// Handle key press events
	void keyPressEvent( QKeyEvent *event );

	// Handle window resized events
	void resizeEvent( QResizeEvent *event );

};

