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

#include "Measurement.h"

void Measurement::save( QString fName )
{
    // Open file
    VAMFileAgent::openFile(fName);
    QFile file( fName );
    if(VAMFileAgent::isInProjLib(fName))
        VAMFileAgent::abs2rel(fName);
    
    fileName = fName;
    
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		QMessageBox::warning( NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2() );

		VAMLogger::log( "Measurement save error" );
		return;
	}

	QTextStream out( &file );

	// Write header, filename, name, and simple variables
	out << "VATEM2 measurement file\n" << "v2.0\n" << fileName << "\n" << name << "\n" << autoCorrect << "\n" << DB.getFileName() << "\n" << schema.getFileName() << "\n";

	writeQStringList( IDs, out );

	for( int i = 0; i < VAMMaxVideos; i++ )
	{
		// Write point and image list
		writeQStringList( points[ i ], out );
	}

	// Write finished flags
	writeVector< bool >( marked, out );

	// Write marker data
	writePointDoubleList( markPositions, out );

	// Write confidence data
	writeVector< int >( confidences, out );

}

bool Measurement::read( QString fName )
{
    // Try to open file
    VAMFileAgent::openFile(fName);
    QFile file( fName );    
    if(VAMFileAgent::isInProjLib(fName))
        VAMFileAgent::abs2rel(fName);
    
	fileName = fName;

	if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		QMessageBox::warning( NULL, VAMTranslatedStrings::errorMeasOpen1().append( fName ), VAMTranslatedStrings::errorMeasOpen2() );

		VAMLogger::log( "Measurement read error" );
		return false;
	}

	QTextStream in( &file );

	points.resize( VAMMaxVideos );

	// Read irrelevant lines
	in.readLine();
	if( in.readLine().compare( "v2.0" ) )
	{
		file.close();
		return readLegacy( fName );
	}
	in.readLine();

	// Read name, and simple variables
	name = in.readLine();
	autoCorrect = in.readLine().toInt();
	DB.read(in.readLine());
	schema.read( in.readLine() );

	IDs = readQStringList( in );

	// Read point and image list
	for( int i = 0; i < VAMMaxVideos; i++ )
	{
		points[ i ] = readQStringList( in );
	}

	// Read finished flags
	marked = readVector< bool >( in );

	// Read marker data
	markPositions = readPointDoubleList( in );

	// Read confidence data
	confidences = readVector< int >( in );

	return true;
}

bool Measurement::readLegacy( QString fName )
{
	// Try to open file
	fileName = fName;
	QFile file( fileName );

	if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		QMessageBox::warning( NULL, VAMTranslatedStrings::errorMeasOpen1().append( fName ), VAMTranslatedStrings::errorMeasOpen2() );

		VAMLogger::log( "Measurement read error" );
		return false;
	}

	QTextStream in( &file );

	// Read irrelevant lines
	in.readLine();
	in.readLine();

	// Read name, and simple variables
	name = in.readLine();
	autoCorrect = in.readLine().toInt();
	//DB = in.readLine();
	//schema = in.readLine();

	// Read point and image list
	IDs = readQStringList( in );
	QStringList IDs2 = readQStringList( in );
	points[ 0 ] = readQStringList( in );
	points[ 1 ] = readQStringList( in );

	// Read finished flags
	marked = readVector< bool >( in );

	// Read marker data
	markPositions = readPointDoubleList( in );

	// Read confidence data
	confidences = readVector< int >( in );

	// If the only video is the upper, swap the points
	if( !IDs2.isEmpty() && IDs.isEmpty() )
	{
		points[ 0 ].swap( points[ 1 ] );
		IDs.swap( IDs2 );
	}

	return true;
}


double Measurement::getDist(const Point &p1, const Point &p2, int dim, VAMImageIndex idx)
{
	double pixelRatio = pixRatio[idx];
	if (dim > 0)
	{ 
		if (A[idx].data)
		{
			pixelRatio *= A[idx].at<double>(0, 0) / (A[idx].at<double>(0, 0) + 1e-5);
		}
		return pixelRatio * (p2.y - p1.y);
	}
	else
	{
		return p2.x - p1.x;;
	}
}

double Measurement::getEtalonSize(int index, VAMImageIndex vidIdx)
{
	Point etalonPS1 = getMark(index, 0), etalonPS2 = getMark(index, 1);
	if (etalonPS1.x >= 0 && etalonPS2.x >= 0)
	{
		double xDist = getDist(etalonPS1, etalonPS2, 0, vidIdx);
		double yDist = getDist(etalonPS1, etalonPS2, 1, vidIdx);
		return sqrt(xDist*xDist + yDist*yDist);
	}
	return -1.0;
}

double Measurement::getEtalonSize(int index, std::vector<int> etalonIndices, VAMImageIndex vidIdx)
{
	if (etalonIndices.size() == 1)
	{
		return getEtalonSize(index + etalonIndices[0], vidIdx);
	}

	pixRatio[vidIdx] = 1.0;
	cv::Mat theta(cv::Size(2, 1), CV_64FC1);
	std::vector<cv::Point2f> X_v;
	std::vector<float> Y_v;

	for (auto etIdx : etalonIndices)
	{
		int idx = etIdx + index;
		Point etalonPS1 = getMark(idx, 0), etalonPS2 = getMark(idx, 1);
		if (etalonPS1.x >= 0 && etalonPS2.x >= 0)
		{
			X_v.push_back(cv::Point2f(powf(getDist(etalonPS1, etalonPS2, 0, vidIdx),2), powf(getDist(etalonPS1, etalonPS2, 1, vidIdx),2)));
			Y_v.push_back(1);
		}
	}

	if (X_v.size() < 2)
	{
		return -1.0;
	}

	//cv::Mat X(X_v.size()/2,2,CV_64FC1), Y(Y_v.size(), 1, CV_64FC1);
	cv::Mat X(X_v), Y(Y_v);
	X = X.reshape(1);
	//Y = Y.reshape(1, 2);

	cv::Mat cov = X.t()*X, eig;
	cv::eigen(cov, eig);
	float ratio = fabs(eig.at<float>(0, 0)) / eig.at<float>(1, 0);
	if (ratio > 4 || ratio < 0.5)
	{
		pixRatio[vidIdx] = 1;

		float runningSum = 0;
		for (int i = 0; i < X.rows; i++)
		{
			runningSum += sqrtf(X.at<float>(i, 0) + X.at<float>(i, 1));
		}
		return runningSum / X.rows;
	}

	theta = (cov.inv())*(X.t()*Y);

	pixRatio[vidIdx] = sqrtf(theta.at<float>(1, 0)) /sqrtf((theta.at<float>(0, 0)+1e-5));

	return 1.0/sqrtf(theta.at<float>(0,0));
}

double Measurement::getPixelSize(int index, std::vector<int> etalonIndices, VAMImageIndex vidIdx)
{
	if (etalonIndices.size() == 1)
	{
		double val = getEtalonSize(index + etalonIndices[0], vidIdx);
		return val*val;
	}

	pixRatio[vidIdx] = 1.0;
	cv::Mat theta(cv::Size(2, 1), CV_64FC1);
	std::vector<cv::Point2f> X_v;
	std::vector<float> Y_v;

	for (auto etIdx : etalonIndices)
	{
		int idx = etIdx + index;
		Point etalonPS1 = getMark(idx, 0), etalonPS2 = getMark(idx, 1);
		if (etalonPS1.x >= 0 && etalonPS2.x >= 0)
		{
			X_v.push_back(cv::Point2f(powf(getDist(etalonPS1, etalonPS2, 0, vidIdx), 2), powf(getDist(etalonPS1, etalonPS2, 1, vidIdx), 2)));
			Y_v.push_back(1);
		}
	}

	if (X_v.size() < 2)
	{
		return 1.0;
	}

	//cv::Mat X(X_v.size()/2,2,CV_64FC1), Y(Y_v.size(), 1, CV_64FC1);
	cv::Mat X(X_v), Y(Y_v);
	X = X.reshape(1, 2);
	Y = Y.reshape(1, 2);

	theta = ((X.t()*X).inv())*(X.t()*Y);
	
	return sqrtf(theta.at<float>(0, 0))*sqrtf(theta.at<float>(1, 0));
}

std::vector<std::vector<double>> Measurement::getMetricPoints(const std::vector<std::vector<int>>& ptIndices)
{
	std::vector<std::vector<double>> ret;

	// Get relevant data
	int videoCnt = DB.getVideoCnt();
	std::vector<double> upCamDist(videoCnt - 1);// = currDB.getUpperEtalonDistance();
	etalonSize = DB.getGlobalEtalonSize();

	// Default etalon size
	std::vector<double> etalonSizes(videoCnt, etalonSize);

	// Compute etalon size from etalon pictures
	std::vector<int> pictureListOffset(4, DB.getCnt() + 1);
	pictureListOffset[0] = 0;
	for (int i = 0; i < videoCnt; i++)
	{
		if (i > 0)
		{
			pictureListOffset[i] = pictureListOffset[i - 1] + DB.getCnt(toIdx(i - 1));
			upCamDist[i - 1] = DB.getEtalonDistance(toIdx(i - 1));
		}
		if (!DB.getGlobalEtalonIndex().empty())
		{
			etalonSizes[i] = getEtalonSize(pictureListOffset[i], DB.getGlobalEtalonIndex(), toIdx(i));
			if (etalonSizes[i] < 0.0)
			{
				etalonSizes[i] = 1.0;
			}
		}
	}

	// Get schema and ID ID list
	QStringList IDs = DB.getIDs();

	// For every image
	for (int imgCnt = 0, currentIndex = 0; imgCnt < IDs.size(); imgCnt++)
	{
		// Variables to make handling both side and upper images easy
		VAMImageIndex imageIdx = imgCnt < pictureListOffset[1] ? VAMImageIndex::_1 :
			imgCnt < pictureListOffset[2] ? VAMImageIndex::_2 :
			imgCnt < pictureListOffset[3] ? VAMImageIndex::_3 : VAMImageIndex::_4;

		int imgNum = imgCnt - pictureListOffset[imageIdx];

		bool autoCorr = autoCorrect && (imageIdx > VAMImageIndex::_1) && (schema.getHeightMeasIdx(toIdx(imageIdx - 1)) != -1);

		// If the current image is etalon, we don't compute anything
		auto etalons = DB.getGlobalEtalonIndex();
		if (std::find(etalons.begin(), etalons.end(), imgNum) != etalons.end())
		{
			continue;
		}

		QString currID = IDs[imgCnt];

		// If not, create new animal
		if (imageIdx == _1)
		{
			ret.push_back(std::vector<double>(ptIndices.size()*2, -1.0));
		} else if (currentIndex >= ret.size())
		{
			currentIndex = 0;
		}

		// Currently modified animal
		std::vector<double> &currVec(ret[currentIndex]);

		// Get correction factor
		double autoCorrFactor = 1.0;
		if (autoCorr) {
			double etSize = DB.getEtalons()[imgNum] ? getEtalonSize(imgCnt, toIdx(imageIdx - 1)) : etalonSizes[imageIdx - 1];
			double height = compute(getMarkRow(imgCnt), schema.getHeightMeasVal(toIdx(imageIdx - 1)), etSize, imageIdx);
			if (height > 0) {
				autoCorrFactor = upCamDist[imageIdx - 1] / (upCamDist[imageIdx - 1] - height);
			}
		}

		// Size of etalon in pixels
		double etSize = DB.getEtalons()[imgNum] ? getEtalonSize(imgCnt, imageIdx) : etalonSizes[imageIdx];
		double etalonPix = etSize * autoCorrFactor;

		// Compute all points for this image
		for (int j = 0; j < ptIndices.size(); j++)
		{
			if (ptIndices[j].size() == 2 && ptIndices[j][1] == imageIdx)
			{
				Point pt = getMark(imgCnt,ptIndices[j][0]);
				if (pt.x != -1.0)
				{
					ret[currentIndex][2 * j] = pt.x * etalonSize / etalonPix;
					ret[currentIndex][2 * j + 1] = pt.y * etalonSize / etalonPix * pixRatio[imageIdx];
					if (A[imageIdx].data)
					{
						ret[currentIndex][2 * j + 1] *= A[imageIdx].at<double>(0, 0) / (A[imageIdx].at<double>(0, 0) + 1e-5);
					}
				}
			}
		}

		currentIndex++;
	}

	return ret;
}


void Measurement::calculate(QString path,int index,cv::Mat &image)
{

	// Get relevant data
	int videoCnt = DB.getVideoCnt();
	std::vector<double> upCamDist(videoCnt - 1);// = currDB.getUpperEtalonDistance();
	etalonSize = DB.getGlobalEtalonSize();

	// Default etalon size
	std::vector<double> etalonSizes(videoCnt, etalonSize);

	// Compute etalon size from etalon pictures
	std::vector<int> pictureListOffset(4, DB.getCnt() + 1);
	pictureListOffset[0] = 0;
	for (int i = 0; i < videoCnt; i++)
	{
		if (i > 0)
		{
			pictureListOffset[i] = pictureListOffset[i - 1] + DB.getCnt(toIdx(i - 1));
			upCamDist[i - 1] = DB.getEtalonDistance(toIdx(i - 1));
		}
		if (!DB.getGlobalEtalonIndex().empty())
		{
			etalonSizes[i] = getEtalonSize(pictureListOffset[i], DB.getGlobalEtalonIndex(), toIdx(i));
			if (etalonSizes[i] < 0.0)
			{
				etalonSizes[i] = 1.0;
			}
		}
	}

	// Get animal data, and clear it
	std::vector< Animal > &animals = getAnimals();
	animals.clear();

	// Get schema and ID ID list
	QStringList IDs = DB.getIDs();
	QStringList images = DB.getImages();

	// For every image
	for (int imgCnt = 0; imgCnt < IDs.size(); imgCnt++)
	{
		if (index >= 0)
			imgCnt = index;
		// Variables to make handling both side and upper images easy
		VAMImageIndex imageIdx = imgCnt < pictureListOffset[1] ? VAMImageIndex::_1 :
			imgCnt < pictureListOffset[2] ? VAMImageIndex::_2 :
			imgCnt < pictureListOffset[3] ? VAMImageIndex::_3 : VAMImageIndex::_4;

		int imgNum = imgCnt - pictureListOffset[imageIdx];

		bool autoCorr = autoCorrect && (imageIdx > VAMImageIndex::_1) && (schema.getHeightMeasIdx(toIdx(imageIdx - 1)) != -1);

		// If the current image is etalon, we don't compute anything
		auto etalons = DB.getGlobalEtalonIndex();
		if (std::find(etalons.begin(), etalons.end(), imgNum) != etalons.end())
		{
			continue;
		}

		QString currID = IDs[imgCnt];
		int currentIndex = animals.size();

		// Detect if we already had an image with this ID ID
		bool secondPic = false;
		for (int i = 0; i < animals.size(); i++)
		{
			if (!currID.compare(animals[i].getID()))
			{
				secondPic = true;
				currentIndex = i;
				break;
			}
		}

		// If not, create new animal
		if (!secondPic)
		{
			Animal newAnim;
			newAnim.setID(currID);
			newAnim.measImages.resize(DB.getVideoCnt());
			newAnim.videoCnt = DB.getVideoCnt();
			animals.push_back(newAnim);
		}

		// Currently modified animal
		Animal &currAnim(animals[currentIndex]);

		currAnim.confidences[imageIdx] = getConfidence(imgCnt);

		int measCnt = schema.measCnt(imageIdx);
        
        // Get correction factor
        double autoCorrFactor = 1.0;
        if (autoCorr) {
            double height = currAnim.getMeasurement(schema.getHeightMeas(toIdx(imageIdx - 1)));
            if (height > 0) {
                autoCorrFactor = upCamDist[imageIdx - 1] / (upCamDist[imageIdx - 1] - height);
            }
        }
        
        // Size of etalon in pixels
		double etSize = DB.getEtalons()[imgNum] ? getEtalonSize(imgCnt, imageIdx) : etalonSizes[imageIdx];
		double etalonPix = etSize * autoCorrFactor;

		// Get image to draw on, and add to animal
		if (index < 0)
		{
			image = imgRead(images[imgCnt], A[imageIdx], d[imageIdx]);
			double resizeScale = 1920.0 / (double)image.cols;
			cv::resize(image, image, cv::Size(0, 0), resizeScale, resizeScale);
			currAnim.width = 1920.0;
			currAnim.height = image.rows;
		}

		reservedImage = new cv::Mat(image.size(), CV_8UC1, cv::Scalar(0, 0, 0));
		drawImage = &image;

		// Compute all measurements for this image
		for (int j = 0; j < measCnt; j++)
		{
			Meas *meas = schema.getMeas(j, imageIdx);
			currAnim.addMeasurement(meas->getName(), compute(getMarkRow(imgCnt), meas, etalonPix, imageIdx));
		}

		QStringList list = { "First", "Second", "Third", "Fourth" };

		// Save image
		if (index < 0)
		{
			QString name = getName();
			removeInvalidChars(name);
			currAnim.measImages[imageIdx] = path + "/Output/" +	name + currID + list[imageIdx] + ".png";
			//cv::imwrite(currAnim.measImages[imageIdx].toStdString(), image);
			imgWrite(currAnim.measImages[imageIdx], image);
		}

		if (autoCorr)
		{
			currAnim.addMeasurement(VAMTranslatedStrings::correctionFactor() + " #" + QString::number(imageIdx), autoCorrFactor);
		}

		if (index >= 0)
			imgCnt = IDs.size();

		emit signal->computed();

	}
}

double Measurement::compute(std::vector<Point>& currMeas, Meas * meas, double etalonPix, VAMImageIndex vidIdx)
{
	double res;

	if (meas->getType() == Meas::MeasDistance)
	{
		// If the etalon size is unknown, we return -1
		if (etalonPix == 0)
		{
			return -1;
		}

		Distance *dist = static_cast<Distance*>(meas);

		// Point names
		QString name1 = dist->getPoint(0).getName(), name2 = dist->getPoint(1).getName();

		Point p1(-1, -1), p2(-1, -1);

		// Get first point coordinates
		for (int i = 0; i < currMeas.size(); i++)
		{
			if (!name1.compare(currMeas[i].getName()))
			{
				p1 = currMeas[i];
			}
		}

		// Get second point coordinates
		for (int i = 0; i < currMeas.size(); i++)
		{
			if (!name2.compare(currMeas[i].getName()))
			{
				p2 = currMeas[i];
			}
		}

		if (p1.x == -1 || p2.x == -1)
			return -1;

		// Compute distance between points
		double xDist = getDist(p1, p2, 0, vidIdx);
		double yDist = getDist(p1, p2, 1, vidIdx);
		res = sqrt(xDist*xDist + yDist*yDist)*etalonSize / etalonPix;

		QString measStr = meas->getName() + "=" +  QString::number(res,'f',2);

		// Draw line
		cv::Point2f pt1(p1.x*drawImage->cols, p1.y*drawImage->cols), pt2(p2.x*drawImage->cols, p2.y*drawImage->cols);
		cv::Scalar currCol(0, 0, 255);
		//cv::Scalar currCol(rand() % 256, rand() % 256, rand() % 256);
		/*if (currCol[0] > 150 && currCol[1] > 150 && currCol[2] > 150)
		{
			currCol[rand() % 3] = 0;
		}*/
		cv::line(*drawImage, pt1, pt2, currCol);

		cv::Point2f origin = (pt1 + pt2) / 2;

		for (int i = 0; i < 100; i++)
		{
			rect = cv::Rect(origin.x + 5, origin.y - 17, measStr.size() * 10, 17);
			checkInBounds(rect, reservedImage->size());
			cv::Point2f magnet = checkIfFilled((*reservedImage)(rect));
			if (magnet.x >= 0)
			{
				moveOrigin(origin, magnet);
			}
			else
			{
				break;
			}
		}

		// Draw rectangle
		origin = cv::Point2f(rect.x - 5, rect.y + 17);
		rect = cv::Rect(origin.x + 5, origin.y - 17, measStr.size() * 10, 17);
		cv::rectangle(*drawImage, rect, cv::Scalar(255, 255, 255), cv::FILLED);
		cv::rectangle(*reservedImage, rect, cv::Scalar(255, 255, 255), cv::FILLED);

		QColor color = QColor(currCol[2], currCol[1], currCol[0]);

		// draw name and value
		//cv::putText( *drawImage, measStr, cv::Point( origin.x + 10, origin.y - 3 ), cv::FONT_HERSHEY_PLAIN, 1, currCol );
		drawText(*drawImage, cv::Point(origin.x + 10, origin.y - 3), measStr, color);
		//cv::addText(*drawImage, measStr, cv::Point(origin.x + 10, origin.y - 3), cv::fontQt("Times", 1, currCol));

	}
	else
	{

		Angle *angle = static_cast<Angle*>(meas);

		// Point names
		QString name1 = angle->getPoint(0).getName(), name2 = angle->getPoint(1).getName(), name3 = angle->getPoint(2).getName();

		Point p1(-1, -1), p2(-1, -1), p3(-1, -1);

		// Get first point coordinates
		for (int i = 0; i < currMeas.size(); i++)
		{
			if (!name1.compare(currMeas[i].getName()))
			{
				p2 = currMeas[i];
			}
		}

		// Get second point coordinates
		for (int i = 0; i < currMeas.size(); i++)
		{
			if (!name2.compare(currMeas[i].getName()))
			{
				p1 = currMeas[i];
			}
		}

		// Get third point coordinates
		for (int i = 0; i < currMeas.size(); i++)
		{
			if (!name3.compare(currMeas[i].getName()))
			{
				p3 = currMeas[i];
			}
		}

		if (p1.x == -1 || p2.x == -1 || p3.x == -1)
			return -1000;

		// Compute angle from three points
		double xDist12 = getDist(p1, p2, 0, vidIdx);
		double yDist12 = getDist(p1, p2, 1, vidIdx);
		double p12 = sqrt(xDist12*xDist12 + yDist12*yDist12);
		double xDist13 = getDist(p1, p3, 0, vidIdx);
		double yDist13 = getDist(p1, p3, 1, vidIdx);
		double p13 = sqrt(xDist13*xDist13 + yDist13*yDist13);
		double xDist23 = getDist(p2, p3, 0, vidIdx);
		double yDist23 = getDist(p2, p3, 1, vidIdx);
		double p23 = xDist23*xDist23 + yDist23*yDist23;

		if (p12 < 0.0001 || p13 < 0.0001)
			return -1000;

		res = (p12 * p12 + p13 * p13 - p23) / (2 * p12 * p13);

		if (abs(res) > 1)
			return -1000;

		res = acos(res) / 3.1415 * 180;

		QString measStr = meas->getName() + "=" + QString::number(res, 'f', 2);

		// Draw line
		cv::Point2f pt1(p1.x*drawImage->cols, p1.y*drawImage->cols), pt2(p2.x*drawImage->cols, p2.y*drawImage->cols), pt3(p3.x*drawImage->cols, p3.y*drawImage->cols);
		cv::Point2f drpt2 = pt1 - (pt1 - pt2) * 0.25, drpt3 = pt1 - (pt1 - pt3) * 0.25;

		cv::Scalar currCol(0, 0, 255);
		/*cv::Scalar currCol(rand() % 256, rand() % 256, rand() % 256);
		if (currCol[0] > 150 && currCol[1] > 150 && currCol[2] > 150)
		{
			currCol[rand() % 3] = 0;
		}*/
		cv::line(*drawImage, pt1, drpt2, currCol);
		cv::line(*drawImage, pt1, drpt3, currCol);

		// Draw rectangle
		cv::Point2f origin = pt1;

		for (int i = 0; i < 100; i++)
		{
			rect = cv::Rect(origin.x + 5, origin.y - 17, measStr.size() * 10, 17);
			checkInBounds(rect, reservedImage->size());
			cv::Point2f magnet = checkIfFilled((*reservedImage)(rect));
			if (magnet.x >= 0)
			{
				moveOrigin(origin, magnet);
			}
			else
			{
				break;
			}
		}

		origin = cv::Point2f(rect.x - 5, rect.y + 17);
		rect = cv::Rect(origin.x + 5, origin.y - 17, measStr.size() * 10, 17);
		cv::rectangle(*drawImage, rect, cv::Scalar(255, 255, 255), cv::FILLED);
		cv::rectangle(*reservedImage, rect, cv::Scalar(255, 255, 255), cv::FILLED);

		QColor color = QColor(currCol[2], currCol[1], currCol[0]);

		// draw name and value
		//cv::putText( *drawImage, measStr, cv::Point( origin.x + 10, origin.y - 3 ), cv::FONT_HERSHEY_PLAIN, 1, currCol );
		drawText(*drawImage, cv::Point(origin.x + 10, origin.y - 3), measStr, color);

	}

	return res;
}

cv::Point2f Measurement::checkIfFilled(const cv::Mat &img)
{
	cv::Moments mom = cv::moments(img, true);

	return cv::Point2f(mom.m10 / mom.m00, mom.m01 / mom.m00);

}

void Measurement::moveOrigin(cv::Point2f &in, const cv::Point2f &magnet)
{
	int deltaX = magnet.x < rect.width / 2 ? 5 : -5;
	int deltaY = magnet.y < rect.height / 2 ? 5 : -5;

	if (magnet.x < rect.width / 4)
		deltaX += 5;
	else if (magnet.x > rect.width*0.75)
		deltaX -= 5;

	if (magnet.y < rect.height / 4)
		deltaY += 5;
	else if (magnet.y > rect.height*0.75)
		deltaY -= 5;

	in = in + cv::Point2f(deltaX, deltaY);
}

void Measurement::resize( int imgCnt, const std::vector< int > &imgCnts, const std::vector< int > &ptCnts, const std::vector< bool > &etalonIndices, const std::vector<int> &globalEtalonIdx )
{
	// Resize marker data
	markPositions.resize( imgCnt );

	// Get camera matrices and distortions
	A.resize(imgCnt);
	d.resize(imgCnt);

	// Resize finished flags and set them all false
	marked.resize( imgCnt, false );
	marked.assign( marked.size(), false );

	// Resize confidence data and set them all false
	confidences.resize( imgCnt, 100 );
	confidences.assign( confidences.size(), 100 );

	// Set the size of marker data entries
	int offset = 0;

	for( int j = 0; j < VAMMaxVideos; j++ )
	{
		if( imgCnts[ j ] == 0 )
			continue;

		for( int i = 0; i < imgCnts[ j ]; i++ )
		{
			int pOffset = etalonIndices[i] ? 2 : 0;
			markPositions[ i + offset ].resize( ptCnts[ j ] + pOffset );
		}

		// Handle etalons separately
		for( auto index:globalEtalonIdx )
		{
			markPositions[ index + offset ].resize( 2 );
		}

		offset += imgCnts[ j ];
	}
}

int Measurement::getFirstUnset( int imageIdx )
{
	// Find the first unset index (A marker is unset if the point's coordinates are (-1,-1)
	for( int i = 0; i < markPositions[ imageIdx ].size(); i++ )
	{
		if( markPositions[ imageIdx ][ i ].x == -1 )
			return i;
	}

	// If finished, return -1
	return -1;
}
