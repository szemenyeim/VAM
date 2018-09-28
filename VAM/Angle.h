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

// Class representing an Angle in a measurement
class Angle : public Meas
{
public:

	// Contructors
	Angle( void ) {}

	Angle( QString _name ) :name( _name ) {}

	// Destructor
	~Angle( void ) {}

	// Add point for the ith place
	void addPoint( Point p, int i );

	// Get the point in the indexth position
	Point getPoint( int index );

	// Getter and setter for the name variable
	inline QString getName() { return name; }

	inline void setName( QString _name ) { name = _name; }

	// Implementation of the pointRenamed message
	void pointRenamed( QString old, QString newN );

	// Implementation og getType
	inline MeasType getType() { return Meas::MeasAngle; }

	// Returns true, if the measurement has a point named pName
	bool hasPoint( QString pName );

	// Conversion to and from QString
	QString getStringFrom() const;

	Angle* create( QString s );

private:

	// First point of the angle
	Point p1;

	// Middle point of the angle
	Point p2;

	// Last point of the angle
	Point p3;

	// Name
	QString name;

};

