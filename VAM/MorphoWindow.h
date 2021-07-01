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
#include "ui_morpho.h"

// Class for exporting morphometrics
class MorphoWindow :
	public QMainWindow
{
	Q_OBJECT
public:

	// Constructor and desctructor
	MorphoWindow(QWidget *parent = 0);
	~MorphoWindow(void);

	// Setter for current project
	void setCurrentProject(Project *value);

private:

	// UI
	Ui::MorphoWindow ui;

	// Containers for enabling/disabling the ui elements
	std::vector< QPushButton* > addPtButtons;
	std::vector< QListView* > pointViews;
	std::vector< QLabel* > labels;

	QStringListModel *ptModel;
	QStringList ptNames;

	// Current selection
	std::vector< std::vector< int > > selectedPoints;
	
	// Current schema
	Schema currentSchema;
	Measurement currentMeasurement;

	// Current project
	Project *currentProject;

	// Video Count
	int vidCnt;
	
	// Is selection modified
	bool morphoModified;

	// Set default UI state
	void resetWindow();

	// Setup UI according to the current schema
	void setupWindow();

	private slots:

	// Action slots
	bool saveMorpho();
	void exportMorpho();

	// Add, delete and rename points/measurements
	void pointUp();
	void pointDown();
	void addPoint(VAMImageIndex idx);
	void delPoint();
	
protected:

	// Called on close
	void closeEvent(QCloseEvent *event);

signals:
	void closed();

};
