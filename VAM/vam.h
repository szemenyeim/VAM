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

#ifndef VAM_H
#define VAM_H

#include <QtWidgets/QMainWindow>
#include "Utility.h"
#include "ui_VAM.h"
#include <qspinbox.h>

class Project;

// Class for the main window of the application
class VAM : public QMainWindow
{
	Q_OBJECT

public:
	VAM(QWidget *parent = 0);
	~VAM();

private:

	// User interface
	Ui::VAMClass ui;

	// Current project
	Project *currentProject;

	// List of available languages and translation files
	QStringList languages;
	QStringList translationFiles;
	QString currentLang;

	// List of list views and labels
	std::vector< QLabel* > vidLabels,imgLabels;
	std::vector< QListView* > vidLists;
	std::vector< QPushButton* > buttons,calibButtons;
	std::vector< QStringListModel* > vidModels;
	QSpinBox *cameraNumSpin;
	QLabel *cameraNumLabel;

	// Indicates if the UI has been disabled
	bool UIDisabled;

	// Images
	std::vector< cv::Mat > images;

	// Indicates if the current project has been modified
	bool projectModified;

	// Indicates if the parts of the current project has been modified
	bool somethingModified;

	// Indicates if the utput generation is in progress
	bool generating;

	// Project library
	QString projectLib;

	// Project name
	QString projectName;

	// Reset ui into its default state
	void resetUI();

	// Setup UI based on the current project
	void loadCurrentProject2UI(bool def = false);

	// For open recent function
	QList<QAction*> recentFileActionList;
	QStringList recentFilePaths;
	int maxFileNr;

	// Adjust for recent file
	void adjustForCurrentFile(const QString &filePath);
	void updateRecentActionList();

	void updateBar();

	private slots:

	void toggleUI();

	// Slots for schema/db/measurement creation/deletion/opening/renaming/editing
	void createSchema();
	void createMeasurement();
	void manageVideos(int index);
	void calibBtn(int index);

	void doVolumetric();
	void doMorpho();

	void deleteSchema();
	void deleteMeas();
	void resetDB(bool keepVideos);

	void openSchema();
	void openMeas();
	//void openDB();

	/*void renameMeas();
	void renameSchema();
	void renameDB();*/

	void dbEdit();
	void schemaEdit();
	void measEdit();

	// Output file creation
	void createOutput();

	// Schange file format
	void formatChanged(int index);
	void cameraNumChanged(int newCameraNum);

	// Read translation files
	void readOptionsAndTranslations();

	// Enable/Disable UI elements
	void setProjectState(ProjectState state);

	bool isProjNew(QString projName);

	// Slots for the actions in the menu and toolbar
	void createProjLib();
	void showAbout();
	void selectLanguage();
	void loggingToggled();
	void orderingChanged();
	void exitPressed();
	void openProject();
	void newProject();
	void saveProject();
	void saveAs();    
    
    // Spinbox value change handler functions
    void videoBoxChanged(double val, VAMImageIndex idx);

	// draw images
	void drawImages(int i);

	// Called if one of the other windows return with a new element
	void newElementAdded();
	void compDataChanged();
	void videoListChanged(QStringList newList, VAMImageIndex idx);

	// Update Config File
	void updateConfig();

	// Update project state
	void updateProjectState();

protected:

	// Called if the window is closed
	void closeEvent(QCloseEvent *event);

	// Handle window resized events
	void resizeEvent(QResizeEvent *event);

};

#endif // VAM_H
