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
#pragma execution_character_set("utf-8")

#include <qevent.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qstringlistmodel.h>
#include <qtextstream.h>
#include <qinputdialog.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <functional>

class Point;
class Meas;

// Indicates whether the side or the upper image/video is used
enum VAMImageIndex { _1 = 0, _2, _3, _4 };
inline VAMImageIndex toIdx( int i ) { return static_cast<VAMImageIndex>( i ); }

const int VAMMaxVideos = 4;

// Type of the output data file
enum FormatType { XLSX = 0, HTML, CSV };

// Ordering type of images
enum OrderingType { OrderByImageType = 0, OrderByAnimal };

// Enum for the project states
enum ProjectState { UNCREATED = 0, VIDEO, STILL, SCHEMA, MEASUREMENT, OUTPUT, FINISHED};

// Functions to convert between QImage and cv::Mat
cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );

QImage cvMatToQImage( const cv::Mat &inMat );

// Function to draw text with special characters on image
void drawText( cv::Mat &image, const cv::Point &pt, const QString &text, const QColor &color );

// Read QR code from image specified by name
QString readQRBarCode( const QString &name );

// Shows QInputdialog to ask for a name
bool getName( const QString &title, const QString &msg, const QString &empty, const QString &already, QString &text, std::function<bool( QString )> func );
//bool getName( const QString & title, const QString & msg, const QString & empty, const QString & already, QString & text, std::function<bool( QString, VAMImageIndex )> func );

// Write std::vector to file
template < typename T >
void writeVector( const std::vector< T > &vec, QTextStream &file )
{
	// Write elements
	for( int i = 0; i < vec.size(); i++ )
	{
		file << vec[ i ] << ",";
	}
	// The vector is terminated with a line containing "end"
	file << "\n";
	file << "end\n";
}

// Write nested std::vector to file
template < typename T >
void writeDoubleVector( const std::vector< std::vector< T > > &vec, QTextStream &file )
{
	// Write elements
	for( int i = 0; i < vec.size(); i++ )
	{
		for( int j = 0; j < vec[ i ].size(); j++ )
		{
			file << vec[ i ][ j ] << ",";
		}
		file << "\n";
	}
	// The vector is terminated with a line containing "end"
	file << "end\n";
}

// Read std::vector from file
////////IMPORTANT: T must be a type that can be initialized with a single double///////////
template < typename T >
std::vector< T > readVector( QTextStream &file )
{
	std::vector< T > vec;

	if( !file.atEnd() )
	{
		// Read lines
		QString line = file.readLine();

		// Split lines among commas
		QStringList vals = line.split( "," );

		// For every line element
		for( QString val : vals )
		{
			// Convert it to double and add it to T
			// For a custom T element you need to implement the constructor T::T( const QString& val )
			if( !val.isEmpty() )
				vec.push_back( val.toDouble() );
		}
	}

	// Read "end" in the next line to ensure the file pointer is in the right place
	file.readLine();

	// Resturn result
	return vec;
}

// Read nested std::vector from file
////////IMPORTANT: T must be a type that can be initialized with a single double///////////
template < typename T >
std::vector< std::vector< T > > readDoubleVector( QTextStream &file )
{
	std::vector< std::vector< T > > vec;

	while( !file.atEnd() )
	{
		std::vector< T > tVec;

		// Read lines
		QString line = file.readLine();

		// If the new line is an "end" then we have reached the end of the vector
		if( !line.compare( "end" ) )
		{
			break;
		}

		// Split lines among commas
		QStringList vals = line.split( "," );

		// For every line element
		for( QString val : vals )
		{
			// Convert it to double and add it to T
			// For a custom T element you need to implement the constructor T::T( const QString& val )
			if( !val.isEmpty() )
				tVec.push_back( val.toDouble() );
		}

		// Add current line to the nested vector
		vec.push_back( tVec );
	}

	// Return result
	return vec;
}

// Function for writing QStringList to file
void writeQStringList(const QStringList &list, QTextStream &file);

// Function for reading QStringlist from a file
QStringList readQStringList( QTextStream &file );

// Write vector of Points to a file
void writePointList( const std::vector< Point > &list, QTextStream &file );

// Read vector of Points from a file
std::vector< Point > readPointList( QTextStream &file );

// Make string file name conform
void removeInvalidChars(QString &string);

// Write nested Point vector
void writePointDoubleList( const std::vector< std::vector< Point > > &list, QTextStream &file );

// Read nested Point vector
std::vector< std::vector< Point > > readPointDoubleList( QTextStream &file );

// Write Measurement vector
void writeMeasList( const std::vector< Meas* > &list, QTextStream &file );

// Read Measurement vector
std::vector< Meas* > readMeasList( QTextStream &file );

// Read & Write images with unicode name
cv::Mat imgRead(QString fileName, const cv::Mat &A, const cv::Mat &d, int code = 1);
void imgWrite(QString fileName, const cv::Mat &img);

// Check if rectangle is out of bounds
void checkInBounds(cv::Rect &rect, const cv::Size & imSize);

// Static class containing translatable strings for objects that do not inherit from QObject (therefore translation is not available to them directly)
class VAMTranslatedStrings : public QObject
{
	Q_OBJECT
public:

	static QString csvID();
	static QString htmlID();
	static QString errorOut1();
	static QString errorOut2();
	static QString errorSchemaOpen1();
	static QString errorSchemaOpen2();
	static QString errorMeasOpen1();
	static QString errorMeasOpen2();
	static QString errorDBOpen1();
	static QString errorDBOpen2();
	static QString errorProjOpen1();
	static QString errorProjOpen2();
	static QString measName();
	static QString value();
	static QString animDB();
	static QString measurement();
	static QString schema();
	static QString schemaSign();
	static QString etalonSign();
	static QString video();
	static QString etalonSize();
	static QString correction();
	static QString correctionFactor();
	static QString animCnt();
	static QString image();
	static QString measImage();
	static QString confidence();
	static QString measTipMove();
	static QString measTipZoom();

};

class VAMOptions
{
public:
	static OrderingType VAMImageOrderingType;
};

class VAMLogger
{
private:

	static QFile *file;

public:

	static bool enabled;

	static void openLog( QString &fName );

	static void log( const QString &msg );
};

class VAMFileAgent
{
private:
    
    static QString *projectPath;
    
public:
    
    static bool openFile( QString &fName );

	static QString updateProjPath(QString fName);

    static void rel2abs( QString &fName );
    
    static void abs2rel( QString &fName );
    
    static void setProjPath( const QString &projPath );
    
    static bool isInProjLib( const QString &fName);
    
};
