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

#include "Distance.h"


Point Distance::getPoint( int i )
{
	// Return the correct point
	switch( i )
	{
	case 0:
		return p1;
		break;
	case 1:
		return p2;
		break;
	default:
		return p1;
		break;
	}
}

void Distance::addPoint( Point p, int i )
{
	// Set ith point
	switch( i )
	{
	case 0:
		p1 = p;
		break;
	case 1:
		p2 = p;
		break;
	default:
		break;
	}
}

void Distance::pointRenamed( QString old, QString newN )
{
	// If one of the points is a match for "old", rename it
	if( !old.compare( p1.getName() ) )
		p1.setName( newN );
	if( !old.compare( p2.getName() ) )
		p2.setName( newN );
}

bool Distance::hasPoint( QString pName )
{
	// True, if one of the points matches pName
	return !( pName.compare( p1.getName() ) && pName.compare( p2.getName() ) );
}

QString Distance::getStringFrom() const
{
	// Contents of the string: Measurement type, name, and the points
	QString res = "Distance,";
	return res.append( name ).append( "," ).append( p1 ).append( "," ).append( p2 );
}

Distance* Distance::create( QString s )
{
	// Split string along commas
	QStringList list = s.split( "," );

	// Check if the string really contains a comma
	if( list.size() < 8 || list[ 0 ].compare( "Distance" ) )
		return new Distance( "Default" );

	// Set name
	Distance *d = new Distance( list[ 1 ] );

	// Set points
	d->p1 = Point( list[ 2 ], list[ 3 ].toInt(), list[ 4 ].toInt() );
	d->p2 = Point( list[ 5 ], list[ 6 ].toInt(), list[ 7 ].toInt() );


	return d;
}
