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
#include "ui_plani.h"

class StillDB;
class Project;

// Class for marking measurements
class PlaniWindow :
	public QMainWindow
{
	Q_OBJECT
public:

	// Constructor and descturcotr
	PlaniWindow(QWidget *parent = 0);
	~PlaniWindow(void);

	// Override of QMainWindow::show()
	void show();

	// Getter setter for the current project
	Project *getCurrentProject() const;
	void setCurrentProject(Project *value);

private:

	// Camera files
	std::vector<cv::Mat> A, d;

	// Selected Roi
	cv::Rect roi;
	bool roiSet;

	// variables
	int method;
	int brushSize;
	int thresh;
	bool eraseMode;
	bool floodFilling;

	// User interface
	Ui::PlaniWindow ui;
	
	// Map for changing the order of images
	std::vector< int > imgIdxMap;

	// Current project and database
	Project *currentProject;
	StillDB currentDB;
	
	// Index if the currently displayed image
	int currentImgIndex;

	// Count of images and side images
	int imgCnt;
	std::vector< int > imgCntThresholds;

	// Currently displayed image - backup
	cv::Mat currentImg;

	// Currently displayed image - used for drawing on it
	cv::Mat currentDrawing, maskImage, maskBU;

	cv::Point fillCenter;

	// Animal data
	std::vector<double> weights;
	std::vector<std::vector<double>> compAreas;

	// Etalon values
	std::vector<double> etalonVals;

	// Zoom state of the image view
	double scale;

	// Indicates if the measurement has been modified since opening it
	bool planiModified;

	// List of image IDs and file names
	QStringList IDList;
	QStringList ImgPathList;

	// String list model for the list view
	QStringListModel *unmarkedID;

	// Polygon points
	std::vector< std::vector< cv::Point > > polygon;

	// Checks if the current image in the database is etalon
	bool isGlobalEtalon();

	// Display image and set related labels on the view
	void showImage();
	void drawImage(double factor = 1.0);

	// Resizes image by factor around center pos
	void resizeImage(double factor, QPointF pos);

	// Adjust the position of the scrollbars if the size of the image changed
	void adjustScrollBar(QScrollBar *scrollBar, double factor, double pos);

	// Sets default state of the window
	void resetWindow();

	// Sets the window up according to the current measurement
	void setupUI();

	// Convert an index to image index
	inline VAMImageIndex getImageIdx(int idx)
	{
		for (int i = VAMMaxVideos - 1; i >= 0; i--)
		{
			if (idx >= imgCntThresholds[i])
				return toIdx(i);
		}
		return toIdx(0);
	}

	inline int getIDIndex()
	{
		VAMImageIndex imageIdx = getImageIdx(imgIdxMap[currentImgIndex]);
		return imgIdxMap[currentImgIndex] - imgCntThresholds[imageIdx];
	}

	private slots:

	// Slot for save buttons
	void savePlani();

	// Slot for export buttons
	void exportPlani();

	// Compute the areas and store it;
	void computeAreas();

	// Get segmentation
	void getSegmentation();

	// Slot for weight changed
	void weightChanged(double val);

	// Slot for brush size changed
	void brushSizeChanged(int val);

	// Slot for threshold changed
	void threshChanged(int val);

	// Slot for method changed
	void methodChanged(int val);
	
	// Apply polygon
	void applyPolygon();

	// Segmentation
	void segment();
	void segmentationImpl();
	void segmentationFinished();

	// Flood Fill
	void floodFill();
	void floodFillImpl(const cv::Point& pt, bool backUp);

	// ROI
	void setROI();

	// Display help
	void help();

	// Clear points
	void clearPoints();

	// Change erase mode variable
	void eraseModeChanged();

	// Change current images
	void prevImage();
	void skipImage();

	// Jump to image
	void listDoubleClicked(QModelIndex curr);

	// Erase image segmentation
	void redoImage();

	// Slot for handling image clicks
	void imageClicked(const QPoint &p);

protected:

	// Called on close
	void closeEvent(QCloseEvent *event);

	// Handler for resize
	void resizeEvent(QResizeEvent *event);

signals:
	void segmDone();
	void closed();
};
