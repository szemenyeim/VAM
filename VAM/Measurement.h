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

#include "Schema.h"
#include "StillDB.h"
#include "Animal.h"


class Messenger : public QObject
{
	Q_OBJECT
public:

signals:
	   void computed();

};

// Class representing a measurement created with a still database and a schema
class Measurement
{
public:

	// Constructor and destructor
	Measurement(void) :autoCorrect(true)
	{
		points.resize(VAMMaxVideos);
		pixRatio.resize(VAMMaxVideos,1.0);
		signal = new Messenger();
		connected = false;
	}
	~Measurement(void) { /*delete signal*/; }

	// File IO operations for the measurement
	void save(QString fName);
	bool read(QString fName);
	bool readLegacy(QString fName);

	// Getter setter for name
	inline void setName(QString _name) { name = _name; }
	inline QString getName() { return name; }

	// Returns the file name
	inline QString getFileName() { return fileName; }

	// Getter setter for a marker position
	inline void setMark(Point pos, int imgIdx, int pIdx) { markPositions[imgIdx][pIdx] = pos; }
	inline Point getMark(int imgIdx, int pIdx) const { return markPositions[imgIdx][pIdx]; }

	// Gets all the marks for an image
	inline std::vector< Point > &getMarkRow(int imgIdx) { return markPositions[imgIdx]; }

	// Get number of finished images
	inline int getMarkedCnt() { return std::count(marked.begin(), marked.end(), true); }

	// Getter setter for camera matrices and distortions
	inline std::vector<cv::Mat> &getA() { return A; }
	inline std::vector<cv::Mat> &getD() { return d; }
	inline void setA(std::vector<cv::Mat> &_A) { A = _A; }
	inline void setD(std::vector<cv::Mat> &_d) { d = _d; }

	// Sets/gets finished flag for an image
	inline void setMarked(int idx, bool val) { marked[idx] = val; }
	inline std::vector< bool > &getMarked() { return marked; }

	// Number of points to mark for the images
	inline int getPointCnt(int index) { if (markPositions.size() > index) return markPositions[index].size(); return 0; }

	// Number of images
	inline int getCnt(VAMImageIndex idx) { return IDs.size(); }
	inline int getCnt() { return markPositions.size(); }

	// Getter setter for the names of the points
	inline QStringList getPoints(VAMImageIndex idx) { return points[idx]; }
	inline void setPoints(QStringList val, VAMImageIndex idx) { points[idx] = val; }

	// Getter setter for the names of the images
	inline QStringList getIDs() { return IDs; }
	inline void setIDs(QStringList val) { IDs = val; }

	// Getter setter for confidence
	inline int getConfidence(int index) { return confidences[index]; }
	inline void setConfidence(int index, int val) { confidences[index] = val; }

	// Get vector containing all marks that belong to the same animal (same ID)
	inline std::vector< Animal >& getAnimals() { return data; }

	// Resizes the measurement to fit the sizes of the database and schema
	void resize(int imgCnt, const std::vector< int > &imgCnts, const std::vector< int > &ptCnts, const std::vector< bool > &etalonIndices, const std::vector<int> &globalEtalonIdx);

	// Get index of first unmarked point for an image. Returns -1 if finished
	int getFirstUnset(int imageIdx);

	// Getter setter for the Schema
	inline Schema getSchema(){return schema;}
	inline void setSchema(Schema _schema) { schema = _schema; }

	// Getter setter for the Database
	inline StillDB getDB() { return DB; }
	inline void setDB(StillDB _DB) { DB = _DB; }

	// Getter setter for the autocorrect variable
	inline bool getAutoCorrect() { return autoCorrect; }
	inline void setAutoCorrect( bool val ) { autoCorrect = val; }

	// Calculate the measurement values
	void calculate(QString path, int index = -1, cv::Mat &image = cv::Mat());

	// Compute the value of a single measurement
	double compute(std::vector< Point > &currMeas, Meas *meas, double etalonPix, VAMImageIndex vidIdx);

	// Check if the image has non-zero element, and return a direction away from them
	cv::Point2f checkIfFilled(const cv::Mat &img);

	// Move point in a specified direction
	void moveOrigin(cv::Point2f &in, const cv::Point2f &magnet);

	//Getter setter for isConnected
	inline bool isConnected() { return connected; }
	inline void setConnected(bool val) { connected = val; }

	double getEtalonSize(int index, VAMImageIndex vidIdx); 
	double getEtalonSize(int index, std::vector<int> etalonIndices, VAMImageIndex vidIdx);
	double getPixelSize(int index, std::vector<int> etalonIndices, VAMImageIndex vidIdx);

	std::vector< std::vector< double > > getMetricPoints(const std::vector< std::vector< int > > &ptIndices);

private:

	// Name of the schema and the database use
	Schema schema;
	StillDB DB;

	// Check if it's connected
	bool connected;

	// List of images used (needed to detect database changes)
	QStringList IDs;

	// List of points used (needed to detect schema changes)
	std::vector<QStringList> points;

	// If true, the program will automatically adjust for the differences in distance of animals and the etalon from the camera
	bool autoCorrect;

	// Name of the measurement
	QString name;

	// Name of the file containing the measurement
	QString fileName;

	// Marking finished flags for the images
	std::vector< bool > marked;

	// The positions of the markers
	std::vector< std::vector< Point > > markPositions;

	// The uncertainty of the measurements
	std::vector< int > confidences;

	// Measurement data per animal
	std::vector< Animal > data;

	// Auxiliary vars for calculation
	double etalonSize;
	// Pointer for drawing the measurement image
	cv::Mat *drawImage, *reservedImage;
	cv::Rect rect;

	std::vector<cv::Mat> A, d;
	std::vector<float> pixRatio;

	double getDist(const Point &p1, const Point &p2, int dim, VAMImageIndex idx);

public:
	Messenger *signal;

};

