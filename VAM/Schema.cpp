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

#include "Schema.h"


Schema::Schema(void)
{
	// Reserve String list models
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		pointModels.push_back(new QStringListModel());
		measModels.push_back(new QStringListModel());
	}
	heightMeasIdx.resize( VAMMaxVideos-1, -1);
	points.resize( VAMMaxVideos );
	measurements.resize( VAMMaxVideos );
	used.resize( VAMMaxVideos );

}

Schema::Schema(const Schema &other)
{
	// Copy simple members
	name = other.name;
	fileName = other.fileName;
	points = other.points;
	used = other.used;
	heightMeasIdx = other.heightMeasIdx;

	points.resize( VAMMaxVideos );
	measurements.resize( VAMMaxVideos );
	pointModels.resize( VAMMaxVideos );
	measModels.resize( VAMMaxVideos );
	used.resize( VAMMaxVideos );

	for (int j = 0; j < VAMMaxVideos; j++)
	{
		// Copy string list models
		pointModels[j] = new QStringListModel(other.pointModels[j]->stringList());
		measModels[j] = new QStringListModel(other.measModels[j]->stringList());



		// Copy side measurements
		for (int i = 0; i < other.measurements[j].size(); i++)
		{
			if (other.measurements[j][i]->getType() == Meas::MeasDistance)
			{
				Distance *newDist = new Distance(*(Distance*)other.measurements[j][i]);
				measurements[j].push_back(newDist);
			}
			else
			{
				Angle *newAng = new Angle(*(Angle*)other.measurements[j][i]);
				measurements[j].push_back(newAng);
			}
		}
	}
}

Schema& Schema::operator= (const Schema &other)
{
	// Use copy constructor
	Schema tmp(other);

	// swap vectors
	swap(tmp);

	return *this;
}

void Schema::swap(Schema &other)
{
	// Copy simple variables
	name = other.name;
	fileName = other.fileName;
	heightMeasIdx = other.heightMeasIdx;

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		// Swap vectors
		std::swap(measurements[i], other.measurements[i]);
		std::swap(points[i], other.points[i]);
		std::swap(used[i], other.used[i]);

		// Swap models
		std::swap(pointModels[i], other.pointModels[i]);
		std::swap(measModels[i], other.measModels[i]);
	}
}

Schema::~Schema(void)
{
	// Delete measurements
	for (int j = 0; j < VAMMaxVideos; j++)
	{
		for (int i = 0; i < measurements[j].size(); i++)
		{
			delete measurements[j][i];
		}

		// Delete models
		delete pointModels[j];
		delete measModels[j];
	}
}

void Schema::addPoint(QString name, Point location, VAMImageIndex imageIdx)
{
	// Set name of the point
	location.setName(name);
	// Add point
	points[imageIdx].push_back(location);
	// Not used yet
	used[imageIdx].push_back(0);
	// Add to models
	pointModels[imageIdx]->insertRows(pointModels[imageIdx]->rowCount(), 1);
	pointModels[imageIdx]->setData(pointModels[imageIdx]->index(pointModels[imageIdx]->rowCount() - 1), name);
}

void Schema::addMeasurement(Angle meas, VAMImageIndex imageIdx)
{
	// Reserve angle
	Angle *retained = new Angle(meas);

	// Add angle
	measurements[imageIdx].push_back(retained);

	// Update used vector
	for (int i = 0; i < points[imageIdx].size(); i++)
	{
		if (retained->hasPoint(points[imageIdx][i].getName()))
		{
			used[imageIdx][i]++;
		}

	}
	// Update model
	measModels[imageIdx]->insertRows(measModels[imageIdx]->rowCount(), 1);
	measModels[imageIdx]->setData(measModels[imageIdx]->index(measModels[imageIdx]->rowCount() - 1), meas.getName());

}

void Schema::addMeasurement(Distance meas, VAMImageIndex imageIdx)
{
	// Reserve distance
	Distance *retained = new Distance(meas);

	// Add distance
	measurements[imageIdx].push_back(retained);

	// Update used vector
	for (int i = 0; i < points[imageIdx].size(); i++)
	{
		if (retained->hasPoint(points[imageIdx][i].getName()))
		{
			used[imageIdx][i]++;
		}

	}
	// Update model
	measModels[imageIdx]->insertRows(measModels[imageIdx]->rowCount(), 1);
	measModels[imageIdx]->setData(measModels[imageIdx]->index(measModels[imageIdx]->rowCount() - 1), meas.getName());

}

void Schema::removePoint(int index, VAMImageIndex imageIdx)
{
	// Remove point
	points[imageIdx].erase(points[imageIdx].begin() + index);
	// Remove it from used vector
	used[imageIdx].erase(used[imageIdx].begin() + index);
	// Update model
	pointModels[imageIdx]->removeRow(index);

}

void Schema::removeMeas(int index, VAMImageIndex imageIdx)
{
	// Decrease height measurement index if on the first image
	if (!imageIdx)
	{
		for (int i = 0; i < VAMMaxVideos - 1; i++)
		{
			if (index < heightMeasIdx[i] && heightMeasIdx[i] != -1)
			{
				heightMeasIdx[i]--;
			}
			else if (index == heightMeasIdx[i])
			{
				heightMeasIdx[i] = -1;
			}
		}
	}

	// Decrease uses in used vector
	for (int i = 0; i < points[imageIdx].size(); i++)
	{
		if (measurements[imageIdx][index]->hasPoint(points[imageIdx][i].getName()))
		{
			used[imageIdx][i]--;
		}

	}
	// Delete measurement
	delete measurements[imageIdx][index];
	// Update vector
	measurements[imageIdx].erase(measurements[imageIdx].begin() + index);
	// Update model
	measModels[imageIdx]->removeRow(index);

}

void Schema::renamePoint(int index, QString _name, VAMImageIndex imageIdx)
{
	// Notify all measurements that the point has been renamed
	for (int i = 0; i < measurements[imageIdx].size(); i++)
	{
		measurements[imageIdx][i]->pointRenamed(points[imageIdx][index].getName(), _name);
	}
	// Rename it
	points[imageIdx][index].setName(_name);
	// Update model
	pointModels[imageIdx]->setData(pointModels[imageIdx]->index(index), _name);
}

void Schema::renameMeas(int index, QString _name, VAMImageIndex imageIdx)
{
	measurements[imageIdx][index]->setName(_name);
	measModels[imageIdx]->setData(measModels[imageIdx]->index(index), _name);
}

Point Schema::getPoint(int index, VAMImageIndex imageIdx)
{
	return points[imageIdx][index];
}

Meas* Schema::getMeas(int index, VAMImageIndex imageIdx)
{
	return measurements[imageIdx][index];
}

QString Schema::getUsedPoints(int index, VAMImageIndex imageIdx)
{
	QString list;

	for (int i = 0; i < measurements[imageIdx].size(); i++)
	{
		// If the ith point is used by the measurement
		if (measurements[imageIdx][i]->hasPoint(points[imageIdx][index].getName()))
		{
			// Add the name of the point to the list
			list.append(measurements[imageIdx][i]->getName() + ", ");
		}

	}

	return list;
}

bool Schema::isPointUsed(int index, VAMImageIndex imageIdx)
{
	return used[imageIdx][index];
}

bool Schema::isPointNew(QString name, VAMImageIndex idx)
{
	for (int i = 0; i < pointCnt(idx); i++)
	{
		// If there is a match return false
		if (!(name.compare(getPoint(i, idx).getName())))
		{
			return false;
		}
	}
	// If there is no match return true
	return true;
}

bool Schema::isMeasNew(QString name, VAMImageIndex idx)
{
	for (int i = 0; i < measCnt(idx); i++)
	{
		// If there is a match return false
		if (!(name.compare(getMeas(i, idx)->getName())))
		{
			return false;
		}
	}
	// If there is no match return true
	return true;
}

void Schema::save(QString fName)
{
    // Set fileName
    VAMFileAgent::openFile(fName);
	QFile file(fName);
    if(VAMFileAgent::isInProjLib(fName))
        VAMFileAgent::abs2rel(fName);
	fileName = fName;

	// Try to open the file

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Schema save error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return;
	}

	QTextStream out(&file);

	// Put out header and basic data
	out << "VATEM3 schema file\n" << "v2.0\n" << fileName << "\n" << name << "\n";
	
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if( i > 0 )
			out << QString::number( heightMeasIdx[ i - 1 ] ) << "\n";

		// Write used vectors
		writeVector< int >(used[i], out);

		// Write points
		writePointList(points[i], out);

		// Write measurements
		writeMeasList(measurements[i], out);
	}
}

bool Schema::read(QString fName)
{
    // Set file name
    VAMFileAgent::openFile(fName);
	QFile file(fName);
    if(VAMFileAgent::isInProjLib(fName))
        VAMFileAgent::abs2rel(fName);
	
	fileName = fName;

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		VAMLogger::log("Schema read error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorSchemaOpen1().append(fName), VAMTranslatedStrings::errorSchemaOpen2());
		return false;
	}

	QTextStream in(&file);

	// Read up header line and the line of the filename
	in.readLine();
	if (in.readLine().compare("v2.0"))
	{
		file.close();
		return readLegacy(fName);
	}
	in.readLine();

	// Get name
	name = in.readLine();

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if( i > 0 )
			heightMeasIdx[ i - 1 ] = in.readLine().toInt();
		// Read used vectors
		used[i] = readVector< int >(in);

		// Read points
		points[i] = readPointList(in);

		// Read measurements
		measurements[i] = readMeasList(in);

		// Set up string lists containing the names of the points and measurements
		QStringList sP, sM;

		for (Point &p : points[i])
		{
			sP.push_back(p.getName());
		}

		for (Meas *p : measurements[i])
		{
			sM.push_back(p->getName());
		}

		if ( i > 0 && heightMeasIdx[i-1] != -1)
		{
			measModels[0]->setData(measModels[0]->index(heightMeasIdx[i - 1]), measurements[0][heightMeasIdx[i - 1]]->getName() + VAMTranslatedStrings::schemaSign());
		}

		pointModels[i]->setStringList(sP);
		measModels[i]->setStringList(sM);
	}

	return true;
}

bool Schema::readLegacy(QString fName)
{
	// Set file name
	fileName = fName;

	// Try to open the file
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		VAMLogger::log("Schema read error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorSchemaOpen1().append(fName), VAMTranslatedStrings::errorSchemaOpen2());
		return false;
	}

	QTextStream in(&file);

	// Read up header line and the line of the filename
	in.readLine();
	in.readLine();

	// Get name
	name = in.readLine();
	heightMeasIdx[0] = in.readLine().toInt();

	// Read used vectors
	used[0] = readVector< int >(in);
	used[1] = readVector< int >(in);

	// Read points
	points[0] = readPointList(in);
	points[1] = readPointList(in);

	// Read measurements
	measurements[0] = readMeasList(in);
	measurements[1] = readMeasList(in);

	// If the only video is the upper, swap the points and measurements
	if( !points[ 1 ].empty() && points[ 0 ].empty() )
	{
		points[ 0 ].swap( points[ 1 ] );
		used[ 0 ].swap( used[ 1 ] );
		measurements[ 0 ].swap( measurements[ 1 ] );
		heightMeasIdx[ 0 ] = -1;
	}

	// Set up string lists containing the names of the points and measurements
	QStringList sP, uP, sM, uM;

	for (Point &p : points[0])
	{
		sP.push_back(p.getName());
	}

	for (Point &p : points[1])
	{
		uP.push_back(p.getName());
	}

	for (Meas *p : measurements[0])
	{
		sM.push_back(p->getName());
	}

	if (heightMeasIdx[0] != -1)
	{
		sM.replace(heightMeasIdx[0], measurements[0][heightMeasIdx[0]]->getName() + VAMTranslatedStrings::schemaSign());
	}

	for (Meas *p : measurements[0])
	{
		uM.push_back(p->getName());
	}

	// Update models
	pointModels[0]->setStringList(sP);
	pointModels[1]->setStringList(uP);
	measModels[0]->setStringList(sM);
	measModels[1]->setStringList(uM);

	return true;
}
