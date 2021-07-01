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

#include "Project.h"
#include "xlsxwriter.h"

Schema Project::getSchema(QString name)
{
	for (int i = 0; i < schemas.size(); i++)
	{
		// Return if there is a name match
		if (!schemas[i].getName().compare(name))
			return schemas[i];
	}
	// Return default
	return Schema();
}

Measurement Project::getMeasurement(QString name)
{
	for (int i = 0; i < measurements.size(); i++)
	{
		// Return if there is a name match
		if (!measurements[i].getName().compare(name))
			return measurements[i];
	}
	// Return default
	return Measurement();
}

StillDB Project::getDB(QString name)
{
	for (int i = 0; i < DBs.size(); i++)
	{
		// Return if there is a name match
		if (!DBs[i].getName().compare(name))
			return DBs[i];
	}
	// Return default
	return StillDB();
}

void Project::addSchema(Schema schema)
{
	for (int i = 0; i < schemas.size(); i++)
	{
		// Overwrite if there is a name match
		if (!schemas[i].getName().compare(schema.getName()))
		{

			VAMLogger::log("Schema overwritten");
			schemas[i] = schema;
			return;
		}
	}
	// Add new if not
	schemas.push_back(schema);
	// Update model
	schemaModel->insertRows(schemaModel->rowCount(), 1);
	schemaModel->setData(schemaModel->index(schemaModel->rowCount() - 1), schema.getName());
}

void Project::addMeasurement(Measurement measurement)
{
	for (int i = 0; i < measurements.size(); i++)
	{
		// Overwrite if there is a name match
		if (!measurements[i].getName().compare(measurement.getName()))
		{

			VAMLogger::log("Measurement overwritten");
			measurements[i] = measurement;
			return;
		}
	}
	// Add new if not
	measurements.push_back(measurement);
	// Update model
	measModel->insertRows(measModel->rowCount(), 1);
	measModel->setData(measModel->index(measModel->rowCount() - 1), measurement.getName());
}

void Project::addDB(StillDB DB)
{
	for (int i = 0; i < DBs.size(); i++)
	{
		// Overwrite if there is a name match
		if (!DBs[i].getName().compare(DB.getName()))
		{

			VAMLogger::log("DB overwritten");
			DBs[i] = DB;
			return;
		}
	}
	// Add new if not
	DBs.push_back(DB);
	// Update model
	dbModel->insertRows(dbModel->rowCount(), 1);
	dbModel->setData(dbModel->index(dbModel->rowCount() - 1), DB.getName());

}

bool Project::isSchemaNew(const QString & name)
{
	for (int i = 0; i < getSchemaCnt(); i++)
	{
		if (!(name.compare(getSchema(i).getName())))
		{
			return false;
		}
	}
	return true;
}

bool Project::isMeasNew(const QString & name)
{
	for (int i = 0; i < getMeasCnt(); i++)
	{
		if (!(name.compare(getMeasurement(i).getName())))
		{
			return false;
		}
	}
	return true;
}

bool Project::isDBNew(const QString & name)
{
	for (int i = 0; i < DBCnt(); i++)
	{
		if (!(name.compare(getDB(i).getName())))
		{
			return false;
		}
	}
	return true;
}

Project Project::read(QString path)
{
    // Try to open file
    QFile file(path);

	Project proj;

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		VAMLogger::log("Project read error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorProjOpen1(), VAMTranslatedStrings::errorProjOpen2());
		return Project();
	}

	QTextStream in(&file);

	// Read header line
	bool newVersion = false;
	if (in.readLine().contains("v2.0"))
		newVersion = true;

	// Read in name, lib name and format index
	proj.setProjName(in.readLine());
	proj.formatIndex = static_cast<FormatType>(in.readLine().toInt());
	if (newVersion)
		proj.state = static_cast<ProjectState>(in.readLine().toInt());
	proj.projLib = in.readLine();
	if (VAMFileAgent::isInProjLib(path))
	{
		VAMFileAgent::abs2rel(proj.projLib);
	}
	else
	{
		VAMFileAgent::setProjPath(path.split("Projects")[0]);
		VAMFileAgent::abs2rel(proj.projLib);
	}

	QStringList dbList, schemaList, measList;

	// Read in database, schema and measurement lists
	dbList = readQStringList(in);
	schemaList = readQStringList(in);
	measList = readQStringList(in);

	// Read databases, schemas and measurements
	for (int i = 0; i < dbList.size(); i++)
	{
		StillDB db;
		if (db.read(dbList[i]))
			proj.addDB(db);
		else
		{
			proj.addDB(db);			
		}
	}

	for (int i = 0; i < schemaList.size(); i++)
	{
		Schema schem;
		if (schem.read(schemaList[i]))
			proj.addSchema(schem);
	}

	for (int i = 0; i < measList.size(); i++)
	{
		Measurement meas;
		if (meas.read(measList[i]))
			proj.addMeasurement(meas);
	}

	return proj;
}

void Project::save(QString name)
{
    // Try to open file
    VAMFileAgent::openFile(name);
    QFile file(name);
    if(VAMFileAgent::isInProjLib(name))
        VAMFileAgent::abs2rel(name);
    
    projName = name;
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Project save error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return;
	}

	QTextStream out(&file);

	// Write header, name, format index, and project lib
	out << "VATEM2 project file v2.0\n" << name << "\n" << formatIndex << "\n" << state << "\n" << projLib << "\n";

	// Get measurement, database and measurement file names
	QStringList dbList, schemaList, measList;

	for (StillDB &curr : DBs)
	{
        // Convert filename
        QString fName = curr.getFileName();
        if( VAMFileAgent::isInProjLib(fName) )
            VAMFileAgent::abs2rel(fName);
		dbList.push_back(fName);
	}
	for (Schema &curr : schemas)
    {
        // Convert filename
        QString fName = curr.getFileName();
        if( VAMFileAgent::isInProjLib(fName) )
            VAMFileAgent::abs2rel(fName);
		schemaList.push_back(fName);
	}
	for (Measurement &curr : measurements)
    {
        // Convert filename
        QString fName = curr.getFileName();
        if( VAMFileAgent::isInProjLib(fName) )
            VAMFileAgent::abs2rel(fName);
		measList.push_back(fName);
	}

	// Write database, schema and measurement list
	writeQStringList(dbList, out);
	writeQStringList(schemaList, out);
	writeQStringList(measList, out);

}

bool Project::generateOutput()
{
	// Variables for file content and extension
	QString str(""), paramStr("");

	bool headerDone = false;

	switch (formatIndex)
	{
	case CSV:
		// Write header
		str.append(VAMTranslatedStrings::animDB().append("\n")).append(projName).append("\n");

		// Write measurement info header
		str.append(VAMTranslatedStrings::measurement() + "," + VAMTranslatedStrings::schema() + "," + VAMTranslatedStrings::video() + "," +
			VAMTranslatedStrings::etalonSize() + ",");
		for (int i = 1; i < VAMMaxVideos; i++)
		{
			str.append(VAMTranslatedStrings::correction() + " #" + QString::number(i) + ",");
		}
		str.append(VAMTranslatedStrings::animCnt() + "," + "\n");

		// Perform calculation for every measurement
		for (Measurement &currMeas : measurements)
		{
			currMeas.calculate(getAbsProjLib());

			// Get database of the measurement
			StillDB currDB = currMeas.getDB();
			int cnt = -1;
			for (int i = 0; i < VAMMaxVideos; i++)
			{
				int currCnt = currDB.getCnt(toIdx(i)) - currDB.getEtalons().size();
				if (currCnt > cnt)
					cnt = currCnt;
			}

			// Write measurement info
			str.append(currMeas.getName() + "," + currMeas.getSchema().getName() + "," + currMeas.getDB().getName() + "," +
				QString::number(currDB.getGlobalEtalonSize()) + ",");
			for (int i = 0; i < VAMMaxVideos - 1; i++)
			{
				str.append(QString::number(currDB.getEtalonDistance(toIdx(i))) + ",");
			}
			str.append("," + QString::number(cnt) + "," + "\n");

			// Write animal data for all animals
			for (Animal &currAnimal : currMeas.getAnimals())
			{
				if (!headerDone)
				{
					// Add a simple header on the top
					paramStr.append(currAnimal.getCSVData().split("\n")[0]).append("\n");
					headerDone = true;
				}

				paramStr.append(currAnimal.getCSVData().split("\n")[1]).append("\n");
			}

		}
		str.append("\n");
		str.append(paramStr);

		break;
	case HTML:

		// Write header
		str.append("<!DOCTYPE html>\n<html>\n<head>\n<title>" + VAMTranslatedStrings::animDB() + ": " + projName + "</title>\n</head>\n<body>");

		// Perform calculation for every measurement
		for (Measurement &currMeas : measurements)
		{
			currMeas.calculate(getAbsProjLib());

			// Get database of the measurement
			StillDB currDB = DBs[0];
			int cnt = -1;
			for (int i = 0; i < VAMMaxVideos; i++)
			{
				int currCnt = currDB.getCnt(toIdx(i)) - currDB.getEtalons().size();
				if (currCnt > cnt)
					cnt = currCnt;
			}

			// Write measurement info
			str.append("<h1>" + VAMTranslatedStrings::measurement() + ": " + currMeas.getName() + "</h1>\n" + "<h2>" +
				VAMTranslatedStrings::schema() + ": " + currMeas.getSchema().getName() + "</h2>"
				+ "<h2>" + VAMTranslatedStrings::video() + ": " + currMeas.getDB().getName() + "</h2>\n"
				+ "<body>" + VAMTranslatedStrings::etalonSize() + ": " + QString::number(currDB.getGlobalEtalonSize()) + "<br>");
			for (int i = 0; i < VAMMaxVideos - 1; i++)
			{
				str.append(VAMTranslatedStrings::correction() + " #" + QString::number(i + 1) + ": " + QString::number(currDB.getEtalonDistance(toIdx(i))) + "<br>");
			}
			str.append(VAMTranslatedStrings::animCnt() + ": " + QString::number(cnt) + "</body>\n");

			// Write animal data for all animals
			for (Animal &currAnimal : currMeas.getAnimals())
			{
				str.append(currAnimal.getHTMLData());
			}

		}

		// Finish HTML
		str.append("</body>\n</html>");

		break;
	case XLSX:
		/* Create a new workbook and add a worksheet. */
		lxw_workbook  *workbook = workbook_new(fName.toUtf8().constData());
		lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

		/* Add a format. */
		lxw_format *format = workbook_add_format(workbook);

		/* Set the bold property for the format */
		format_set_bold(format);

		// Write header
		worksheet_write_string(worksheet, 0, 0, VAMTranslatedStrings::animDB().toUtf8().constData(), format);
		worksheet_write_string(worksheet, 1, 0, projName.toUtf8().constData(), format);

		int rowIndex = 2;
		// Perform calculation for every measurement
		for (Measurement &currMeas : measurements)
		{
			currMeas.calculate(getAbsProjLib());

			// Get database of the measurement
			StillDB currDB = currMeas.getDB();
			int cnt = -1;
			for (int i = 0; i < VAMMaxVideos; i++)
			{
				int currCnt = currDB.getCnt(toIdx(i)) - currDB.getEtalons().size();
				if (currCnt > cnt)
					cnt = currCnt;
			}

			// Write measurement header
			worksheet_write_string(worksheet, rowIndex, 0, VAMTranslatedStrings::measurement().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 1, VAMTranslatedStrings::schema().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 2, VAMTranslatedStrings::video().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 3, VAMTranslatedStrings::etalonSize().toUtf8().constData(), NULL);
			for (int i = 1; i < VAMMaxVideos; i++)
			{
				worksheet_write_string(worksheet, rowIndex, 3 + i, (VAMTranslatedStrings::correction() + " #" + QString::number(i)).toUtf8().constData(), NULL);
			}
			worksheet_write_string(worksheet, rowIndex++, 3 + VAMMaxVideos, VAMTranslatedStrings::animCnt().toUtf8().constData(), NULL);

			// Write measurement info
			worksheet_write_string(worksheet, rowIndex, 0, currMeas.getName().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 1, currMeas.getSchema().getName().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 2, currMeas.getDB().getName().toUtf8().constData(), NULL);
			worksheet_write_string(worksheet, rowIndex, 3, QString::number(currDB.getGlobalEtalonSize()).toUtf8().constData(), NULL);
			for (int i = 0; i < VAMMaxVideos - 1; i++)
			{
				worksheet_write_string(worksheet, rowIndex, 3 + i, QString::number(currDB.getEtalonDistance(toIdx(i))).toUtf8().constData(), NULL);
			}
			worksheet_write_string(worksheet, rowIndex, 3 + VAMMaxVideos, QString::number(cnt).toUtf8().constData(), NULL);

			rowIndex += 2;

			// Write animal data for all animals
			for (Animal &currAnimal : currMeas.getAnimals())
			{
				if (!headerDone)
				{
					// Add a simple header on the top
					QStringList names = currAnimal.getCSVData().split("\n")[0].split(",");
					for (int i = 0; i < names.size(); i++)
					{
						worksheet_write_string(worksheet, rowIndex, i, names.at(i).toUtf8().constData(), format);
					}
					rowIndex++;
					headerDone = true;
				}

				QStringList vals = currAnimal.getCSVData().split("\n")[1].split(",");
				for (int i = 0; i < vals.size(); i++)
				{
					worksheet_write_string(worksheet, rowIndex, i, vals.at(i).toUtf8().constData(), NULL);
				}
				rowIndex++;
			}
			rowIndex++;
		}
		workbook_close(workbook);
		return true;
		break;
	}

	// Open output file
	QFile file(fName);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		VAMLogger::log("Output generation error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return false;
	}

	// Write data
	QTextStream out(&file);

	out << str;

	return true;

}
