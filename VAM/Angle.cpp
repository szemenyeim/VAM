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

#include "Angle.h"


Point Angle::getPoint( int i )
{
	// Return the ith point
	switch( i )
	{
	case 0:
		return p1;
		break;
	case 1:
		return p2;
		break;
	case 2:
		return p3;
		break;
	default:
		return p1;
		break;
	}
}

// Add point in the ith place
void Angle::addPoint( Point p, int i )
{
	switch( i )
	{
	case 0:
		p1 = p;
		break;
	case 1:
		p2 = p;
		break;
	case 2:
		p3 = p;
		break;
	default:
		break;
	}
}

void Angle::pointRenamed( QString old, QString newN )
{
	// If one of the points matches the old name, we rename it
	if( !old.compare( p1.getName() ) )
		p1.setName( newN );
	if( !old.compare( p2.getName() ) )
		p2.setName( newN );
	if( !old.compare( p3.getName() ) )
		p3.setName( newN );
}

bool Angle::hasPoint( QString pName )
{
	// Return true, if one of the points is a match
	return !( pName.compare( p1.getName() ) && pName.compare( p2.getName() ) && pName.compare( p3.getName() ) );
}

QString Angle::getStringFrom() const
{
	// The string contains the type of the measurement, the name and the points
	QString res = "Angle,";
	return res.append( name ).append( "," ).append( p1 ).append( "," ).append( p2 ).append( "," ).append( p3 );

}

Angle* Angle::create( QString s )
{
	// Split the list among commas
	QStringList list = s.split( "," );

	// Check if list contains an angle
	if( list.size() < 11 || list[ 0 ].compare( "Angle" ) )
		return new Angle( "Default" );

	// Set name
	Angle *d = new Angle( list[ 1 ] );

	// Set points
	d->p1 = Point( list[ 2 ], list[ 3 ].toInt(), list[ 4 ].toInt() );
	d->p2 = Point( list[ 5 ], list[ 6 ].toInt(), list[ 7 ].toInt() );
	d->p3 = Point( list[ 8 ], list[ 9 ].toInt(), list[ 10 ].toInt() );
	
	return d;

}