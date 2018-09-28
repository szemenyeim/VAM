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

#include "Utility.h"

// Class to represent a point used by measurements
// It has a name, and x,y coordinates
class Point
{
public:
	// Default constructor
	Point( void ) {}

	// Contructors
	Point( QString _name ) :name( _name ) {}

	Point( double _x, double _y ) :x( _x ), y( _y ) {}

	Point( QString _name, double _x, double _y ) :name( _name ), x( _x ), y( _y ) {}

	// Contructor from cv::Point
	Point( cv::Point p ) :x( p.x ), y( p.y ) {}

	// Conversion to cv::Point
	operator cv::Point() { return cv::Point( x, y ); };
	operator QPointF() { return QPointF( x, y ); };

	// Construction from QString
	inline static Point fromString( QString s )
	{
		QStringList list = s.split( "," );
		Point p( list[ 0 ] );
		p.x = list[ 1 ].toDouble();
		p.y = list[ 2 ].toDouble();
		return p;
	}

	// Conversion to QString
	inline operator QString() const { QString res = name; return res.append( "," ).append( QString::number( x ) ).append( "," ).append( QString::number( y ) ); }

	// Destructor
	~Point( void ) {}

	// Getter and setter for the name variable
	inline QString getName() { return name; }

	inline void setName( QString _name ) { name = _name; }

	// Multiplication with a scalar
	inline Point operator *( double factor ) { return Point( name, x * factor, y * factor ); }

	// Element-wise multiplication
	inline Point operator *( Point other ) { return Point( name, x * other.x, y * other.y ); }

	// Coordinates
	double x;
	double y;

private:
	// Name
	QString name;
};

// Pure virtual class for Measurements (Angles and Distances)
class Meas
{
public:

	enum MeasType { MeasDistance = 0, MeasAngle };

	// Get type
	virtual MeasType getType() = 0;

	// Returns if the measurement uses the point pName
	virtual bool hasPoint( QString pName ) = 0;

	// Returns the name of the measurement
	virtual QString getName() = 0;

	// Converts the measurement into a QString
	virtual QString getStringFrom() const = 0;

	// Constructs measurement from QString
	virtual Meas* create( QString s ) = 0;

	// Sets the name of the measurement
	virtual void setName( QString _name ) = 0;

	// Signals the measurement that the point named "old" has been renamed "newN"
	// Does nothing if the measurement didn't use "old"
	virtual void pointRenamed( QString old, QString newN ) = 0;
};

