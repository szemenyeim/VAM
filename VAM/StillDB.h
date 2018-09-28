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

// Class representing a still image database
class StillDB
{
public:

	// Constructor and desctrutor
	StillDB( void );
	~StillDB( void ) {}

	// Get still image from the database
	QString getStill( int index, VAMImageIndex imageIdx );

	// Add still image to the database
    void addStill( QString still, QString ID, float stillPos, VAMImageIndex imageIdx, bool fromOpen = false );

	// Deletes still image
	void deleteStill( int index );

	// Changes the ID of a still image
	inline void renameStill( int index, QString _name )
	{
		IDs[ index ] = _name;
		stillModel->setData( stillModel->index( index ), _name );
	}

	// Adds the indexth image to the etalons
	void addEtalon( int index );

	// Removes the indexth image from the etalons
	void removeEtalon( int index );

	// Set global etalon
	inline void toggleGlobalEtalonIndex(int index)
	{
		auto it = std::find(globalEtalonIndex.begin(), globalEtalonIndex.end(), index);
		if (it != globalEtalonIndex.end())
		{
			stillModel->setData(stillModel->index(index), IDs[index]);
			globalEtalonIndex.erase(it);
			return;
		}
		// Set new value and add a star to the distance name
		globalEtalonIndex.push_back(index);
		stillModel->setData(stillModel->index(index), IDs[index] + VAMTranslatedStrings::etalonSign());
	}

	inline std::vector<int> getGlobalEtalonIndex() { return globalEtalonIndex; }
	inline float getGlobalEtalonSize() { return globalEtalonSize; }
	inline void setGlobalEtalonSize( float val) { globalEtalonSize = val; }

	// Get video list
	inline QStringList getVideos( VAMImageIndex imageIdx ) { return videos[ imageIdx ]; }
	inline std::vector<QStringList> getVideos() const { return videos; }

	// Add video
	inline void setVideos(VAMImageIndex imageIdx, QStringList _videos ) { videos[imageIdx] = _videos; }

	// Remove video
	void removeVideo( QString video, VAMImageIndex imageIdx );

	// Get string list models for listViews
	inline QStringListModel *getModel() { return stillModel; }

	// Get vector containing the indices of etalon images
	inline const std::vector< bool > &getEtalons() const { return hasEtalon; }

	// Get full list of still image IDs
	inline QStringList getIDs(bool justOnce = false)
	{
		if (justOnce)
			return IDs;
		QStringList list;
		if( getCnt() )
		{
			for( int vidIdx = 0; vidIdx < videoCnt; vidIdx++ )
			{
				list.append( IDs );
			}
		}
		return list;
	}

	// Get full list of still image file names
	inline QStringList getImages()
	{
		QStringList list;
		if( getCnt() )
		{
			for( int vidIdx = 0; vidIdx < videoCnt; vidIdx++ )
			{
				list.append( stillNames[ vidIdx ] );
			}
		}
		return list;
	}

	// Returns index of the animal ID ID, -1 if not found
	int IDexists( QString ID );

	// Returns true if an image with a specific ID is not present
	bool isIDNew( QString name );

	// Returns true if the still is in the database
	bool isStillUsed( QString fileName, VAMImageIndex imageIdx );

	// Get number of side, upper or total stills
	inline int getCnt( VAMImageIndex imageIdx ) { return stillNames[ imageIdx ].size(); }
	inline int getCnt()
	{
		int ret = 0;
		for( int vidIdx = 0; vidIdx < videoCnt; vidIdx++ )
		{
			ret += stillNames[ vidIdx ].size();
		}
		return ret;
	}
	inline std::vector< int > getCounts()
	{
		std::vector< int > counts;
		for( int vidIdx = 0; vidIdx < VAMMaxVideos; vidIdx++ )
		{
			counts.push_back( stillNames[ vidIdx ].size() );
		}
		return counts;
	}

	// Getters and setters for Etalon distance variables
	inline double getEtalonDistance( VAMImageIndex imageIdx ) { return etalonDistances[ imageIdx ]; }
	inline void setEtalonDistance( double val, VAMImageIndex imageIdx ) { etalonDistances[ imageIdx ] = val; }
		
	// Getter and setter for the name
	inline void setName( QString _name ) { name = _name; }
	inline QString getName() { return name; }

	// Returns the name of the file containing the database
	inline QString getFileName() { return fileName; }
	inline void setFileName(QString _fName) { fileName = _fName; }

	// Clears list of stills to detele
	inline void clearStillsToDelete() { stillsToDelete.clear(); }

	// File IO operations for the Database
	void save( QString _name );
	bool read( QString _name );
	bool readLegacy( QString _name );

	// Getter-setter for videoCnt
	inline void setVideoCnt( int val ) { 
		videoCnt = val;
		if( videoCnt > VAMMaxVideos ) 
			videoCnt = VAMMaxVideos; 
		if( videoCnt < 1 ) 
			videoCnt = 1;
		//videos.resize(videoCnt);
	
	};
	inline int getVideoCnt() const { return videoCnt; }

	// Getter-setter for usingvideos
	inline void setUsingVideos( bool val ) { usingVideos = val; }
	inline bool getUsingVideos() { return usingVideos; }

	// Get time position of stills
    inline std::vector< float >& getStillTimes(int index) { return framePos[index]; }

private:

	// Video count
	int videoCnt;

	// Video
	bool usingVideos;

	// Still names
	std::vector<QStringList> stillNames;

	// ID IDs
	QStringList IDs;
    std::vector< std::vector < float > > framePos;

	// Video names
	std::vector<QStringList> videos;

	// Database and file names
	QString name;
	QString fileName;

	// List of still image files to delete on saving
	QStringList stillsToDelete;

	// List of still files that may not be deleted
	QStringList exceptionList;

	// Models for list view
	QStringListModel* stillModel;

	// Etalon indices
	std::vector< bool > hasEtalon;

	// Size of the etalon used
	float globalEtalonSize;
	std::vector<int> globalEtalonIndex;

	// Distance of the etalon from the cameras
	std::vector<double> etalonDistances;

};

