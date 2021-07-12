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

#include "StillDB.h"
#include <set>


StillDB::StillDB(void)
{
	// Reserve new models
	stillModel = new QStringListModel();

	// Default parameters
	globalEtalonSize = 1;
	usingVideos = true;
	etalonDistances.resize(VAMMaxVideos - 1, 1);
	stillNames.resize(VAMMaxVideos);
	videos.resize(VAMMaxVideos);

}

QString StillDB::getStill(int index, VAMImageIndex imageIdx)
{
	// Return the name of the indexth still
	return stillNames[imageIdx][index];
}

void StillDB::addStill(QString still, QString ID, float stillPos, VAMImageIndex imageIdx, bool fromOpen)
{
    // Convert filename
    if( VAMFileAgent::isInProjLib(still) )
        VAMFileAgent::abs2rel(still);
    
	// Determine variables
	QStringList *stillList = &stillNames[imageIdx];
	QStringList *IDList = &IDs;

	removeInvalidChars(ID);

	// Add entry to etalon vector
	hasEtalon.push_back(false);

	// Add still name and ID to the lists
	stillList->push_back(still);
	if (imageIdx == 0)
	{
		IDList->push_back(ID);
        framePos.push_back(std::vector<float>(videoCnt));

		// Update the model
		stillModel->insertRows(stillModel->rowCount(), 1);
		stillModel->setData(stillModel->index(stillModel->rowCount() - 1), ID);
	}

	framePos.back()[imageIdx] = stillPos;

	// If the still was from an already existing file, add it to the deletion exception list
	exceptionList.push_back(still);
}

void StillDB::renameStillImage(int stillIdx, QString still, float stillPos, VAMImageIndex imageIdx)
{
	// Convert filename
	if (VAMFileAgent::isInProjLib(still))
		VAMFileAgent::abs2rel(still);

	// Determine variables
	QStringList* stillList = &stillNames[imageIdx];
	(*stillList)[stillIdx] = still;
	framePos[stillIdx][imageIdx] = stillPos;
}

void StillDB::removeVideo(QString video, VAMImageIndex imageIdx)
{
	QStringList *list = &videos[imageIdx];

	// Get index of the video file
	int idx = list->indexOf(video);

	// If present, erase it
	if (idx != -1)
		list->erase(list->begin() + idx);
}

void StillDB::addEtalon(int index)
{
	// Add index to etalon vector
	hasEtalon[index] = true;
}

void StillDB::removeEtalon(int index)
{
	// Remove index from etalon vector
	hasEtalon[index] = false;
}

void StillDB::save(QString _name)
{
	// Try to open file
    VAMFileAgent::openFile(_name);
    QFile file(_name);
    if(VAMFileAgent::isInProjLib(_name))
        VAMFileAgent::abs2rel(_name);

	fileName = _name;

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Database save error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return;
	}

	QTextStream out(&file);

	// Write header, name, and parameters
	out << "VATEM2 stilldb file\n" << "v4.0\n" << name << "\n" << globalEtalonSize << "\n";
	
	for (auto ind:globalEtalonIndex)
	{
		out << ind << ",";
	}

	out << "\n" << videoCnt << "\n" << usingVideos << "\n";

	// Write ID IDs and positions
	writeQStringList(IDs, out);
    writeDoubleVector<float>(framePos, out);

	// Write etalon indices
	writeVector< bool >(hasEtalon, out);

	for (int i = 0; i < videoCnt; i++)
	{
		if (i > 0)
			out << etalonDistances[i - 1] << "\n";

		// Write video names
		writeQStringList(videos[i], out);

		// Write still file names
		writeQStringList(stillNames[i], out);
	}

	// Remove still images pending delete
    for (QString currStill : stillsToDelete)
    {
        VAMFileAgent::openFile(currStill);
		QFile::remove(currStill);
    }
}

bool StillDB::read(QString _name)
{
	// Try to open file
    VAMFileAgent::openFile(_name);
    QFile file(_name);
    if(VAMFileAgent::isInProjLib(_name))
        VAMFileAgent::abs2rel(_name);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		VAMLogger::log("Database read error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorDBOpen1(), VAMTranslatedStrings::errorDBOpen2());
		return false;
	}

	// Set file name
	fileName = _name;

	QTextStream in(&file);

	// Read header
	in.readLine();

	QString version = in.readLine();
	if (version.compare("v4.0"))
	{
		file.close();
		return readLegacy(_name);
	}

	// Read name
	name = in.readLine();

	// Read parameters
	globalEtalonSize = in.readLine().toDouble();
	auto etalonIndices = in.readLine().split(",");
	for (auto ind : etalonIndices)
	{
		if (ind != "")
		{
			globalEtalonIndex.push_back(ind.toInt());
		}
	}
	videoCnt = in.readLine().toInt();
	usingVideos = in.readLine().toInt();

	// Resize lists
	etalonDistances.resize(VAMMaxVideos - 1);
	videos.resize(VAMMaxVideos);
	stillNames.resize(VAMMaxVideos);

	exceptionList.clear();

	// Read ID list and positions
	IDs = readQStringList(in);
	for( auto &ID:IDs )
		removeInvalidChars(ID);
	
    framePos = readDoubleVector<float>(in);

	// Read etalon indices
	hasEtalon = readVector< bool >(in);

	std::set<int> removeIndices;

	for (int i = 0; i < videoCnt; i++)
	{
		if (i > 0)
			etalonDistances[i - 1] = in.readLine().toDouble();

		// Read video, ID ID and Still lists
        videos[i] = readQStringList(in);
		stillNames[i] = readQStringList(in);

		// We cannot delete the images that were created at an earlier time
		exceptionList.append(stillNames[i]);
	}
	
	// Update models
	stillModel->setStringList(IDs);
	for(auto ind:globalEtalonIndex)
		stillModel->setData(stillModel->index(ind), IDs[ind] + VAMTranslatedStrings::etalonSign());

	return true;
}

bool StillDB::readLegacy(QString _name)
{
	// Try to open file
	VAMFileAgent::openFile(_name);
	QFile file(_name);
	if (VAMFileAgent::isInProjLib(_name))
		VAMFileAgent::abs2rel(_name);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		VAMLogger::log("Database read error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorDBOpen1(), VAMTranslatedStrings::errorDBOpen2());
		return false;
	}

	// Set file name
	fileName = _name;

	QTextStream in(&file);

	// Read header
	in.readLine();

	QString version = in.readLine();

	// Read name
	name = in.readLine();

	// Read parameters
	globalEtalonSize = in.readLine().toDouble();
	videoCnt = in.readLine().toInt();
	usingVideos = in.readLine().toInt();

	// Resize lists
	etalonDistances.resize(VAMMaxVideos - 1);
	videos.resize(VAMMaxVideos);
	stillNames.resize(VAMMaxVideos);

	exceptionList.clear();

	// Read ID list and positions
	IDs = readQStringList(in);
	for (auto &ID : IDs)
		removeInvalidChars(ID);

	framePos = readDoubleVector<float>(in);

	// Read etalon indices
	auto etalonIndices = in.readLine().split(",");
	in.readLine();
	hasEtalon.resize(IDs.size(), false);
	for (auto ind : etalonIndices)
	{
		if (ind != "" && ind != "-1")
		{
			hasEtalon[ind.toInt()] = true;
		}
	}

	std::set<int> removeIndices;

	for (int i = 0; i < videoCnt; i++)
	{
		if (i > 0)
			etalonDistances[i - 1] = in.readLine().toDouble();

		// Read video, ID ID and Still lists
		videos[i] = readQStringList(in);
		stillNames[i] = readQStringList(in);

		// We cannot delete the images that were created at an earlier time
		exceptionList.append(stillNames[i]);
	}

	// Update models
	stillModel->setStringList(IDs);
	for (auto ind : globalEtalonIndex)
		stillModel->setData(stillModel->index(ind), IDs[ind] + VAMTranslatedStrings::etalonSign());

	this->save(fileName);

	return true;
}

int StillDB::IDexists(QString ID)
{
	// Find ID in the side list
	for (int i = 0; i < IDs.size(); i++)
	{
		if (!IDs.at(i).compare(ID))
		{
			return i;
		}
	}
	// Return -1 if not found
	return -1;
}

bool StillDB::isIDNew(QString name)
{
	return !(IDexists(name) != -1);
}

bool StillDB::isStillUsed(QString fileName, VAMImageIndex imageIdx)
{
	QStringList *list = &stillNames[imageIdx];

	// Return true, if the fileName is present in the vector
	for (int i = 0; i < list->size(); i++)
	{
		if (!fileName.compare(list->at(i)))
			return true;
	}
	return false;
}

void StillDB::deleteStill(int index)
{

	for (int i = 0; i < videoCnt; i++)
	{
		QString stillName = getStill(index, toIdx(i));

		// Determine variables
		QStringList *stillList = &stillNames[i];
		stillList->erase(stillList->begin() + index);

		// If the still is not used in other places, and not added to the exception list, prepare for deletion
		if (!isStillUsed(stillName, toIdx(i)) && exceptionList.indexOf(stillName) == -1)
			stillsToDelete.push_back(stillName);
	}

	// Remove still
	IDs.erase(IDs.begin() + index);
	framePos.erase(framePos.begin() + index);
	hasEtalon.erase(hasEtalon.begin() + index);

	// Update model
	stillModel->removeRow(index);

	// Update etalons
	for( int i = globalEtalonIndex.size()-1; i >= 0; i--)
	{
		int idx = globalEtalonIndex[i];
		if (idx == index)
		{
			globalEtalonIndex.erase(globalEtalonIndex.begin() + i);

			if (globalEtalonIndex.empty())
			{
				globalEtalonSize = 1.0;
			}
		}
		else if (idx > index)
		{
			globalEtalonIndex[i]--;
		}
	}
}
