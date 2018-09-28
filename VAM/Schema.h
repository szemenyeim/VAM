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

#include "Point.h"
#include "Angle.h"
#include "Distance.h"

// Class for representing a schema: a set of measurements to compute and the points used to compute them
// Like everything in VAM this class uses two different sets of measurements: one for the side image the other for the upper image
class Schema
{
public:

	// Contructor
	Schema( void );

	// Custom copy contructor (necessary because measurements are stored by Meas* pointers
	Schema( const Schema &other );

	// Destructor
	~Schema( void );

	// Custom operator =
	Schema& operator= ( const Schema &other );

	// Functions for inserting points and measurements
	void addPoint( QString name, Point location, VAMImageIndex imageIdx );

	void addMeasurement( Angle meas, VAMImageIndex imageIdx );

	void addMeasurement( Distance meas, VAMImageIndex imageIdx );

	// Functions for removing points and measurements
	void removePoint( int index, VAMImageIndex imageIdx );

	void removeMeas( int index, VAMImageIndex imageIdx );

	// Functions for renaming points and measurements
	void renamePoint( int index, QString _name, VAMImageIndex imageIdx );

	void renameMeas( int index, QString _name, VAMImageIndex imageIdx );

	// Getter for points and measurements
	Point getPoint( int index, VAMImageIndex imageIdx );

	Meas *getMeas( int index, VAMImageIndex imageIdx );

	// Get point or measurement counts
	inline int pointCnt( VAMImageIndex imageIdx ) { return points[ imageIdx ].size(); }
	inline int pointCnt() { int cnt = 0;  for( int i = 0; i < VAMMaxVideos; cnt += points[ i ].size(), i++ ) {} return cnt; }
	inline std::vector< int > pointCounts()
	{
		std::vector< int > counts;
		for( int imageIdx = 0; imageIdx < VAMMaxVideos; imageIdx++ )
		{
			counts.push_back( points[ imageIdx ].size() );
		}
		return counts;
	}

	inline int measCnt( VAMImageIndex imageIdx ) { return measurements[ imageIdx ].size(); }

	// Get used points
	QString getUsedPoints( int index, VAMImageIndex imageIdx );

	bool isPointUsed( int index, VAMImageIndex imageIdx );

	// Getter setter for name
	inline QString getName() { return name; }

	inline void setName( QString _name ) { name = _name; }

	// Resturn true if the measurement or the point do not exist
	bool isPointNew( QString name, VAMImageIndex idx );

	bool isMeasNew( QString name, VAMImageIndex idx );

	bool matches(int videoCnt)
	{
		for (int i = 0; i < videoCnt; i++)
		{
			if (pointCnt(toIdx(i)) == 0)
			{
				return false;
			}
		}
		return true;
	}

	// Getter setter for the height measurement name
	inline QString getHeightMeas( VAMImageIndex imageIdx ) { return measurements[ imageIdx ][ heightMeasIdx[ imageIdx ] ]->getName(); }
	inline int getHeightMeasIdx( VAMImageIndex imageIdx ) { return heightMeasIdx[ imageIdx ]; }
	inline Meas* getHeightMeasVal(VAMImageIndex imageIdx) { return measurements[imageIdx][heightMeasIdx[imageIdx]]; }

	inline void setHeightMeas( int index, VAMImageIndex imageIdx )
	{
		// reset old text
		if( heightMeasIdx[ imageIdx - 1 ] != -1 )
		{
			measModels[ 0 ]->setData( measModels[ 0 ]->index( heightMeasIdx[ imageIdx - 1 ] ), measurements[ 0 ][ heightMeasIdx[ imageIdx - 1 ] ]->getName() );
		}

		// Set new value and add a star to the distance name
		heightMeasIdx[ imageIdx - 1 ] = index;
		measModels[ 0 ]->setData( measModels[ 0 ]->index( heightMeasIdx[ imageIdx - 1 ] ), measurements[ 0 ][ heightMeasIdx[ imageIdx - 1 ] ]->getName() + VAMTranslatedStrings::schemaSign() );
	}

	// IO operations on Schemas
	void save( QString fName );

	bool read( QString fName );
	bool readLegacy( QString fName );

	inline QString getFileName() { return fileName; }

	// Models for the list views
	std::vector<QStringListModel*> pointModels;
	std::vector<QStringListModel*> measModels;

private:

	// Name
	QString name;

	// Name of the file containing the schema
	QString fileName;

	// Containers for points and measurements
	std::vector<std::vector< Point >> points;
	std::vector<std::vector< Meas* >> measurements;

	// Indicate the number of measurements using a certain point
	std::vector<std::vector< int >> used;

	// Helper function for operator = and the copy contructor
	void swap( Schema &other );

	// Index of the heigth measurement
	std::vector<int> heightMeasIdx;

};

