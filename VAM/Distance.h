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

// Class representing a point used in measurements
class Distance : public Meas
{
public:

	// Constructors
	Distance( void ) {}
	Distance( QString _name ) :name( _name ) {}

	// Destructor
	~Distance( void ) {}

	// Add point to the ith place
	void addPoint( Point p, int i );

	// Get point in the indexth position
	Point getPoint( int index );

	// Getter and setter for name
	inline QString getName() { return name; }

	inline void setName( QString _name ) { name = _name; }

	// Implementation of the pointRenamed message
	void pointRenamed( QString old, QString newN );

	// Implementation of getType
	inline MeasType getType() { return Meas::MeasDistance; }

	// Returns true if the Distance uses the point pName
	bool hasPoint( QString pName );

	// Conversions from and to QString
	QString getStringFrom() const;

	Distance* create( QString s );

private:

	// Two points defining the distance
	Point p1;
	Point p2;

	// Name
	QString name;
};

