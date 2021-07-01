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

#include "Utility.h"
#include "Point.h"
#include "Angle.h"
#include "Distance.h"
#include <QStandardPaths>
#include <qpainter.h>
#include <fstream>
#include "zbar.h" 


cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData)
{
	switch (inImage.format())
	{
		// 8-bit, 4 channel
	case QImage::Format_RGB32:
	{
		cv::Mat  mat(inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());

		return (inCloneImageData ? mat.clone() : mat);
	}

	// 8-bit, 3 channel
	case QImage::Format_RGB888:
	{

		QImage   swapped = inImage.rgbSwapped();

		return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine()).clone();
	}

	// 8-bit, 1 channel
	case QImage::Format_Indexed8:
	{
		cv::Mat  mat(inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());

		return (inCloneImageData ? mat.clone() : mat);
	}

	default:
		break;
	}

	return cv::Mat();
}

QImage cvMatToQImage(const cv::Mat &inMat)
{
	switch (inMat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32);

		return image;
	}

	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);

		return image.rgbSwapped();
	}

	// 8-bit, 1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable;

		// only create our color table once
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
				sColorTable.push_back(qRgb(i, i, i));
		}

		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);

		image.setColorTable(sColorTable);

		return image;
	}

	default:
		break;
	}

	return QImage();
}

void drawText(cv::Mat &image, const cv::Point &pt, const QString &text, const QColor &color)
{
	QImage img = cvMatToQImage(image);
	QPainter p(&img);
	p.setPen(QPen(color));
	p.setFont(QFont("Times", 12));
	QPointF point(pt.x, pt.y);
	p.drawText(point, text);
	bool bEnd = p.end();
	image = QImageToCvMat(img, true);
}

QString readQRBarCode(const QString & name)
{
	QString ID;
	zbar::ImageScanner scanner;
	scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
	cv::Mat img = imgRead(name, cv::Mat(), cv::Mat(), 0);
	if (img.data)
	{
		int width = img.cols;
		int height = img.rows;
		uchar *raw = (uchar *)img.data;
		zbar::Image image(width, height, "Y800", raw, width * height);
		// scan the image for barcodes
		int n = scanner.scan(image);
		// extract results
		for (zbar::Image::SymbolIterator symbol = image.symbol_begin();
			symbol != image.symbol_end();
			++symbol)
		{
			ID = QString::fromStdString(symbol->get_data());
		}
	}

	return ID;
}

bool checkString(const QString &str)
{
	for (const char c : str.toStdString())
	{
		if (c < 32 || c == 47 || (c >= 60 && c <= 62) || c == 92)
			return false;
	}
	return true;
}

bool getName(const QString & title, const QString & msg, const QString & empty, const QString & already, QString & text, std::function<bool(QString)> func)
{
	bool ok;

	QString message = msg;

	while (1)
	{
		text = QInputDialog::getText(NULL, title,
			message, QLineEdit::Normal,
			text, &ok);

		if (!ok)
			return false;

		if (text.isEmpty())
		{
			message = empty;
			continue;
		}

		if (!checkString(text))
		{
			message = QObject::tr("Name contains invalid characters!");
			continue;
		}

		if (func(text))
			return true;

		message = already;
	}
	return ok;
}

/*bool getName( const QString & title, const QString & msg, const QString & empty, const QString & already, QString & text, std::function<bool( QString, VAMImageIndex )> func )
{
	bool ok;

	QString message = msg;

	while( 1 )
	{
		text = QInputDialog::getText( NULL, title,
			message, QLineEdit::Normal,
			text, &ok );

		if( !ok )
			return false;

		if( text.isEmpty() )
		{
			message = empty;
			continue;
		}

		if( func( text ) )
			return true;

		message = already;
	}
	return ok;
}*/

void writeQStringList(const QStringList &list, QTextStream &file)
{
	// Write all strings in a new line
	for (QString currString : list)
	{
		file << currString << "\n";
	}
	// Terminate with "end"
	file << "end\n";
}

QStringList readQStringList(QTextStream &file)
{
	QStringList list;

	// Read lines
	while (!file.atEnd())
	{
		QString line = file.readLine();

		// If line equals "end", the finished
		if (!line.compare("end"))
		{
			break;
		}

		list.push_back(line);
	}

	return list;
}

void writePointList(const std::vector< Point > &list, QTextStream &file)
{
	// Write all points to a new line
	// Note: Point is convertible to QString
	for (const QString currString : list)
	{
		file << currString << "\n";
	}
	// Terminate with end
	file << "end\n";
}

std::vector< Point > readPointList(QTextStream &file)
{
	std::vector< Point > pointList;

	// Read lines
	while (!file.atEnd())
	{
		QString line = file.readLine();

		// If line equals "end", the finished
		if (!line.compare("end"))
		{
			break;
		}

		// Converting QString to Point
		// Point::fromString() is not safe!!! Might return something stupid without error.
		pointList.push_back(Point::fromString(line));
	}

	return pointList;
}

void removeInvalidChars(QString & string)
{
	string.replace(QString(" "), QString("_"));
	string.replace(QString("\t"), QString(""));
	string.replace(QString("\n"), QString(""));
	string.replace(QString("\\"), QString(""));
	string.replace(QString("/"), QString(""));
	string.replace(QString("%%"), QString(""));
	string.replace(QString("\""), QString(""));
	string.replace(QString(":"), QString(""));
	string.replace(QString(";"), QString(""));
	string.replace(QString("."), QString(""));
	string.replace(QString(","), QString(""));
	string.replace(QString("*"), QString(""));
	string.replace(QString("="), QString(""));
	string.replace(QString("["), QString(""));
	string.replace(QString("]"), QString(""));
}

void writePointDoubleList(const std::vector< std::vector< Point > > &list, QTextStream &file)
{
	// Write all points
	for (const std::vector< Point > currList : list)
	{
		for (const QString currString : currList)
		{
			file << currString << "\n";
		}
		// Nested vector is terminated with "endline"
		file << "endline\n";
	}
	// Terminate vector with and "end"
	file << "end\n";
}

std::vector< std::vector< Point > > readPointDoubleList(QTextStream &file)
{
	std::vector< std::vector< Point > > pointList;

	// Read lines
	while (!file.atEnd())
	{
		std::vector< Point > smallList;

		QString line = file.readLine();

		// Detect end of the vector
		if (!line.compare("end"))
		{
			break;
		}

		// Read lines until reaching the end of the nested vector
		while (!file.atEnd())
		{
			if (!line.compare("endline"))
			{
				break;
			}

			smallList.push_back(Point::fromString(line));

			line = file.readLine();

		}

		pointList.push_back(smallList);
	}

	return pointList;
}

void writeMeasList(const std::vector< Meas* > &list, QTextStream &file)
{
	// Write measurements into separate lines
	for (int i = 0; i < list.size(); i++)
	{
		file << list[i]->getStringFrom() << "\n";
	}
	// Terminate with end
	file << "end\n";
}

std::vector< Meas* > readMeasList(QTextStream &file)
{
	std::vector< Meas* > pointList;

	// Read lines
	while (!file.atEnd())
	{
		QString line = file.readLine();

		// Detect end of the vector
		if (!line.compare("end"))
		{
			break;
		}

		// First element of the line contains wether the measurement is Angle or Distance
		if (line.split(",")[0].compare("Angle"))
		{
			pointList.push_back(Distance().create(line));
		}
		else
		{
			pointList.push_back(Angle().create(line));
		}
	}

	return pointList;
}

cv::Mat imgRead(QString fileName, const cv::Mat &A, const cv::Mat &d, int code)
{
    VAMFileAgent::openFile(fileName);
	std::wstring str = fileName.toStdWString();
	std::ifstream file(str, std::ios_base::binary);
	std::vector<char> data;

	file >> std::noskipws;
	std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(), std::back_inserter(data));
	if (data.empty())
		return cv::Mat(480, 640, CV_8UC1, cv::Scalar(0));

	cv::Mat img = cv::imdecode(cv::Mat(data), code);
	if (d.data && A.data)
	{
		cv::Mat undist;
		cv::undistort(img, undist, A, d);
		return undist;
	}
	return img;
}

void imgWrite(QString fileName, const cv::Mat &img)
{
	std::wstring str = fileName.toStdWString();
	std::ofstream file(str, std::ofstream::out | std::ios_base::binary | std::ofstream::trunc);
	std::vector<uchar> data;

	cv::imencode(".png", img, data);
	std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(file));
	file.close();
}

void checkInBounds(cv::Rect & rect, const cv::Size & imSize)
{
	if (rect.x < 0)
		rect.x = 0;
	if (rect.x >= imSize.width)
		rect.x = imSize.width - rect.width - 1;
	if (rect.y < 0)
		rect.y = 0;
	if (rect.y >= imSize.height)
		rect.y = imSize.height - -rect.height - 1;
	if (rect.width < 1)
		rect.width = 1;
	if (rect.height < 1)
		rect.height = 1;
	if (rect.x + rect.width >= imSize.width)
		rect.x = imSize.width - rect.width - 1;
	if (rect.y + rect.height >= imSize.height)
		rect.y = imSize.height - -rect.height - 1;
	if (rect.x < 0)
		rect.x = 0;
	if (rect.y < 0)
		rect.y = 0;

}


// Translated string literals
QString VAMTranslatedStrings::csvID() { return tr("ID"); }
QString VAMTranslatedStrings::htmlID() {
	return  tr("Animal ID");
}
QString VAMTranslatedStrings::errorOut1() {
	return  tr("Error opening output file");
}
QString VAMTranslatedStrings::errorOut2() {
	return  tr("Please try another location.");
}
QString VAMTranslatedStrings::errorSchemaOpen1() {
	return  tr("Error opening schema file ");
}
QString VAMTranslatedStrings::errorSchemaOpen2() {
	return  tr("The schema will be removed from the project.");
}
QString VAMTranslatedStrings::errorMeasOpen1() {
	return  tr("Error opening measurement file ");
}
QString VAMTranslatedStrings::errorMeasOpen2() {
	return  tr("The measurement will be removed from the project.");
}
QString VAMTranslatedStrings::errorDBOpen1() {
	return  tr("Error opening database file ");
}
QString VAMTranslatedStrings::errorDBOpen2() {
	return  tr("The database will be removed from the project.");
}
QString VAMTranslatedStrings::errorProjOpen1() {
	return  tr("Error opening project file");
}
QString VAMTranslatedStrings::errorProjOpen2() {
	return  tr("Please try another location.");
}
QString VAMTranslatedStrings::measName() {
	return  tr("Measurement name");
}
QString VAMTranslatedStrings::value() {
	return  tr("Value");
}
QString VAMTranslatedStrings::animDB() {
	return  tr("Animal database");
}
QString VAMTranslatedStrings::measurement() {
	return tr("Measurement");
}
QString VAMTranslatedStrings::schema() {
	return  tr("Schema");
}
QString VAMTranslatedStrings::schemaSign() {
	return  tr(" --- (this distance is set as animal height)");
}
QString VAMTranslatedStrings::etalonSign() {
	return  tr(" --- (global etalon)");
}
QString VAMTranslatedStrings::video() {
	return  tr("Video database");
}
QString VAMTranslatedStrings::etalonSize() {
	return tr("Etalon Size");
}
QString VAMTranslatedStrings::correction() {
	return  tr("Camera distance");
}
QString VAMTranslatedStrings::correctionFactor() {
	return  tr("Correction coefficient");
}
QString VAMTranslatedStrings::animCnt() {
	return  tr("Animal count");
}
QString VAMTranslatedStrings::image() {
	return  tr("Image");
}
QString VAMTranslatedStrings::measImage() {
	return  tr("Measurements");
}
QString VAMTranslatedStrings::confidence() {
	return  tr("Confidence");
}
QString VAMTranslatedStrings::measTipMove() {
	return  tr("Tip: Use <w, a, s, d> to move the selected point, <del> to delete it");
}
QString VAMTranslatedStrings::measTipZoom() {
	return  tr("Tip: Use the mouse wheel to zoom in and out of the image");
}
QString VAMTranslatedStrings::doneStr() {
	return  tr(" --- (Done)");
}


OrderingType VAMOptions::VAMImageOrderingType = OrderByImageType;

QFile* VAMLogger::file;

bool VAMLogger::enabled = false;

void VAMLogger::openLog(QString &path)
{
	/*QDir dir( "Logs" );
	if( !dir.exists() )
		dir.mkpath( "." );*/

	file = new QFile(path);

	file->open(QIODevice::WriteOnly | QIODevice::Text);
}

void VAMLogger::log(const QString &msg)
{
	if (enabled)
	{
		if (!file || !file->isOpen())
		{
			QString appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(QString("/log.txt"));
			openLog(appDir);
		}

		QTextStream out(file);

		out << msg << "\n";
	}
}

QString* VAMFileAgent::projectPath;


bool VAMFileAgent::openFile( QString &fName )
{
    if (QFile::exists(fName))
        return true;
    QString fName2 = *projectPath + fName;
    if (QFile::exists(fName2))
	{
		fName = fName2;
        return true;
	}
	if (!isInProjLib(fName))
		fName = fName2;
    return false;
}

QString VAMFileAgent::updateProjPath(QString fName)
{
	if (QFile::exists(fName))
		return fName;
	QString fName2 = *projectPath;
	if (QFile::exists(fName2))
	{
		return fName2;
	}
	return fName2;
}

void VAMFileAgent::abs2rel( QString &fName )
{
    if (!fName.contains(*projectPath))
        return;
    fName = fName.split(*projectPath)[1];
}

void VAMFileAgent::rel2abs( QString &fName )
{
    if (fName.contains(*projectPath))
        return;
    fName = *projectPath + fName;
}

bool VAMFileAgent::isInProjLib( const QString &fName )
{
    if (fName.contains(*projectPath))
        return true;
    return false;
}

void VAMFileAgent::setProjPath( const QString &projPath )
{
    projectPath = new QString(projPath);
}



