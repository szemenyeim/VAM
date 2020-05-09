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

#include <qstring.h>
#include "Schema.h"
#include "Measurement.h"
#include "StillDB.h"

// Class representing a project
class Project
{
private:

	// Type of the output format
	FormatType formatIndex;

	// State
	ProjectState state;

	// Size of the etalon in the video
	double etalonSize;

	// Current Project library
	QString projLib;

	// Generic Project library
	QString genProjLib;

	// Project name
	QString projName;

	// Models for the databases, schemas, and measurements in the project
	QStringListModel *schemaModel;
	QStringListModel *measModel;
	QStringListModel *dbModel;

	// Containers for the databases, schemas, and measurements in the project
	std::vector< Schema > schemas;
	std::vector< Measurement > measurements;
	std::vector< StillDB > DBs;

	// Calculate the measurement values
	void calculate(Measurement &currMeas, int imgIdx = -1);

	// Compute the value of a single measurement
	double compute(std::vector< Point > &currMeas, Meas *meas, double etalonPix);

	// Check if the image has non-zero element, and return a direction away from them
	cv::Point2f checkIfFilled(const cv::Mat &img);

	// Move point in a specified direction
	void moveOrigin(cv::Point2f &in, const cv::Point2f &magnet);

	QString fName;

public:
	// Contructor and desctuctor
	Project(void) : schemaModel(new QStringListModel()), measModel(new QStringListModel()), dbModel(new QStringListModel()) {}
	~Project(void) {}

	// Getter setter for format index
	inline FormatType getFormatIndex() { return formatIndex; }
	inline void setFormatIndex(FormatType val) { formatIndex = val; }

	// Getter setter for project state
	inline ProjectState getState() { return state; }
	inline void setState(ProjectState _state) { state = _state; }

	// Getter setter for  project lib
	inline QString getProjLib() { return projLib; }
	inline QString getAbsProjLib() { return genProjLib + projLib; }
	inline void setProjLib(QString val) { projLib = val; }
	inline QString getGenProjLib() { return genProjLib; }
	inline void setGenProjLib(QString val) { genProjLib = val; }

	// Getter and setter for project name
	inline void setProjName(QString _name) { projName = _name; }
	inline QString getName() { return projName; }

	// Counts of schemas, databases and measurements
	inline int getSchemaCnt() { return schemas.size(); }
	inline int getMeasCnt() { return measurements.size(); }
	inline int DBCnt() { return DBs.size(); }

	// Getter for databases measurements and schemas
	inline StillDB getDB(int index) { return DBs[index]; }
	StillDB getDB(QString name);
	inline Schema getSchema(int index) { return schemas[index]; }
	Schema getSchema(QString name);
	inline Measurement& getMeasurement(int index) { return measurements[index]; }
	inline std::vector<Measurement> &getMeasurements() { return measurements; }
	inline Measurement *getMeasPtr(int index) { return &measurements[index]; }
	Measurement getMeasurement(QString name);

	inline void setOutputName(QString name) { fName = name; }
	inline QString getOutputName() { return fName; }

	// Add DBs schemas and measurements
	void addDB(StillDB DB);
	void addSchema(Schema schema);
	void addMeasurement(Measurement measurement);

	// Return true if the schema/measurement/database with this name doesn't exist yet
	bool isSchemaNew(const QString &name);
	bool isMeasNew(const QString &name);
	bool isDBNew(const QString &name);

	// Remove DBs schemas and measurements
	inline void removeMeasurement(int index)
	{
		measurements.erase(measurements.begin() + index);
		measModel->removeRow(index);
	}
	inline void removeSchema(int index)
	{
		schemas.erase(schemas.begin() + index);
		schemaModel->removeRow(index);
	}
	inline void removeDB(int index)
	{
		DBs.erase(DBs.begin() + index);
		dbModel->removeRow(index);
	}

	// Rename DBs schemas and measurements
	inline void renameMeasurement(int index, QString _name)
	{
		measurements[index].setName(_name);
		measurements[index].save(measurements[index].getFileName());
		measModel->setData(measModel->index(index), _name);
	}

	inline void renameSchema(int index, QString _name)
	{
		schemas[index].setName(_name);
		schemas[index].save(schemas[index].getFileName());
		schemaModel->setData(schemaModel->index(index), _name);
	}

	inline void renameDB(int index, QString _name)
	{
		DBs[index].setName(_name);
		DBs[index].save(DBs[index].getFileName());
		dbModel->setData(dbModel->index(index), _name);
	}

	// Get string list models for list views
	inline QStringListModel *getSchemaList() { return schemaModel; }
	inline QStringListModel *getMeasList() { return measModel; }
	inline QStringListModel *getDBList() { return dbModel; }

	// File IO operations
	static Project read(QString path);
	void save(QString name);

	// Generate output data file
	bool generateOutput();
};

