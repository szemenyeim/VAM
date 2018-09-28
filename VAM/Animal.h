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

// Class containing measurement data for an animal
class Animal
{
public:

	// Constructor and destructor
	Animal( void ) {}
	~Animal( void ) {}

	// Measurement image URLs
	std::vector< QString > measImages;

	// Image size
	int width;
	int height;

	// Video data
	int videoCnt;
	int confidences[ VAMMaxVideos ];

	// Getter and setter for the ID ID variable
	inline void setID( const QString &val ) { ID = val; }

	inline QString getID() { return ID; }

	inline int getCnt() { return measurements.size(); }

	// Insert measurement data
	inline void addMeasurement( const QString &name, double value )
	{
		measurements.push_back( std::pair< QString, double >( name, value ) );
	}

	// Read measurement value by name
	inline double getMeasurement( const QString &name )
	{
		for( auto it : measurements )
		{
			if( !it.first.compare( name ) )
				return it.second;
		}
		// Default value
		return -1;
	}

	// Outputs data in csv format
	inline QString getCSVData()
	{
		// Empty strings
		QString strData( "" ), str2( "" );

		// Append all names and all values to separate strings, separated by commas
		for( auto currIt : measurements )
		{
			strData.append( currIt.first ).append( "," );
			str2.append( QString::number( currIt.second, 'f', 2 ) ).append( "," );
		}

		// Append confidence values
		for( int i = 0; i < videoCnt; i++ )
		{
			strData.append( VAMTranslatedStrings::confidence() ).append( " #" ).append( QString::number( i + 1 ) ).append( "," );
			str2.append( QString::number( confidences[ i ] ) ).append( "," );
		}

		// Append the two full strings, into two lines
		strData.append( "\n" ).append( str2 ).append( "\n" );

		// Create final output string
		QString str( VAMTranslatedStrings::csvID() + "," );
		str.append( strData.split( "\n" )[ 0 ] ).append( "\n" ).append( ID ).append( "," ).append( strData.split( "\n" )[ 1 ] );

		return str;
	}

	// Outputs data in html format
	inline QString getHTMLData()
	{
		// Initialize html table
		QString strData( "<table style=\"width:100%%\">\n" );
		strData.append( "<tr>\n<td>" + VAMTranslatedStrings::measName() + "</td>\n<td>" + VAMTranslatedStrings::value() + "</td>\n</tr>\n" );

		for( auto currIt : measurements )
		{
			// Append measurement names and values in the cells
			strData.append( "<tr>\n" );
			strData.append( "<td>" ).append( currIt.first ).append( "</td>\n" );
			strData.append( "<td>" ).append( QString::number( currIt.second, 'f', 2 ) ).append( "</td>\n" );
			strData.append( "</tr>\n" );
		}

		// Insert confindece values
		for( int i = 0; i < videoCnt; i++ )
		{
			strData.append( "<tr>\n<td>" + VAMTranslatedStrings::confidence() + " #" + QString::number( i + 1 ) + "</td>\n<td>" + QString::number( confidences[ i ] ) + "</td>\n</tr>\n" );
		}

		// Finish table
		strData.append( "</table>\n" );

		// Images
		for( int i = 0; i < videoCnt; i++ )
		{
			strData.append( "<figure>\n" );
			strData.append( "<img src=\"" ).append( measImages[ i ] ).append( "\" alt=\"Image\" style=\"width:" ).append( QString::number( width ) ).append( "px; height:" ).append( QString::number( height ) ).append( "px; \">\n" );
			strData.append( "<figcaption>" ).append( VAMTranslatedStrings::measImage() + " #" + QString::number( i + 1 ) ).append( "</figcaption>\n</figure>\n" );
		}

		// Finish headers
		QString str( "<h3>" + VAMTranslatedStrings::htmlID() + ": " );
		str.append( ID ).append( "</h3>\n" ).append( strData );

		return str;
	}

private:

	// ID ID of the animal
	QString ID;

	// Measurement data container
	std::vector< std::pair< QString, double > > measurements;

};

