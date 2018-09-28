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

#include "MorphoWindow.h"
#include <qmenu.h>


MorphoWindow::MorphoWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ptModel = new QStringListModel();
	// Default window state
	resetWindow();
}


MorphoWindow::~MorphoWindow(void)
{
	delete ptModel;
}

void MorphoWindow::resetWindow()
{
	// Setup UI
	ui.setupUi(this);

	// Default variable values
	morphoModified = false;

	// Fill up UI element lists
	addPtButtons = { ui.addBtn1, ui.addBtn2, ui.addBtn3, ui.addBtn4 };
	pointViews = { ui.pointView1, ui.pointView2, ui.pointView3, ui.pointView4 };
	labels = { ui.pl1, ui.pl2, ui.pl3, ui.pl4 };

	// Connect action slots
	connect(ui.actionSave, &QAction::triggered, this, &MorphoWindow::saveMorpho);
	connect(ui.actionExport, &QAction::triggered, this, &MorphoWindow::exportMorpho);
	connect(ui.actionDone, &QAction::triggered, this, &MorphoWindow::close);

	connect(ui.upButton, &QPushButton::clicked, this, &MorphoWindow::pointUp);
	connect(ui.downButton, &QPushButton::clicked, this, &MorphoWindow::pointDown);
	connect(ui.delButton, &QPushButton::clicked, this, &MorphoWindow::delPoint);

	// Connect button slots
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		connect(addPtButtons[i], &QPushButton::clicked, std::bind(&MorphoWindow::addPoint, this, toIdx(i)));
	}

	// Setup window buttons
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

}

void MorphoWindow::setupWindow()
{

	vidCnt = currentProject->getDB(0).getVideoCnt();

	// setup list views
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if (i < vidCnt)
		{
			pointViews[i]->setModel(currentSchema.pointModels[i]);
		}
		else
		{
			pointViews[i]->setVisible(false);
			addPtButtons[i]->setVisible(false);
			labels[i]->setVisible(false);
		}
	}

	for (auto pt : selectedPoints)
	{
		if (pt.size() == 2)
		{
			ptNames.push_back(currentSchema.getPoint(pt[0], toIdx(pt[1])).getName());
		}
	}

	ptModel->setStringList(ptNames);
	ui.listView->setModel(ptModel);

	// Not modified
	morphoModified = false;
}

void MorphoWindow::exportMorpho()
{
	VAMLogger::log("Morpho export");

	// Save morpho
	QDir dir;
	dir.setPath(currentProject->getAbsProjLib() + "/Morphometrics/");
	if (!dir.exists())
		dir.mkpath(".");

	QString fName = QFileDialog::getSaveFileName(this, tr("Export Morphometrics Data"), currentProject->getAbsProjLib() + "/Morphometrics/export.nts", tr("NTS file (*.nts)"));
	QFile file(fName);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Morphometrics export error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return;
	}

	QTextStream out(&file);

	auto pts = currentMeasurement.getMetricPoints(selectedPoints);

	if (pts.empty())
		return;

	out << "1 " << pts.size() << "L " << pts[0].size() << " 1 -1 Dim=2\n";

	for (auto anim : pts)
	{
		for (auto pt : anim)
		{
			out << pt << " ";
		}
		out << "\n";
	}

}

void MorphoWindow::pointUp()
{
	QModelIndexList list = ui.listView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to move!"));
		return;
	}

	int index = list[0].row();

	QString name = ptNames.at(index);
	ptNames.erase(ptNames.begin() + index);
	ptNames.insert(index - 1, name);

	std::vector<int> element = selectedPoints.at(index);
	selectedPoints.erase(selectedPoints.begin() + index);
	selectedPoints.insert(selectedPoints.begin() + index - 1, element);

	ptModel->setStringList(ptNames);
	ui.listView->setModel(ptModel);
}

void MorphoWindow::pointDown()
{
	QModelIndexList list = ui.listView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to move!"));
		return;
	}

	int index = list[0].row();

	QString name = ptNames.at(index);
	ptNames.erase(ptNames.begin() + index);
	ptNames.insert(index + 1, name);

	std::vector<int> element = selectedPoints.at(index);
	selectedPoints.erase(selectedPoints.begin() + index);
	selectedPoints.insert(selectedPoints.begin() + index + 1, element);

	ptModel->setStringList(ptNames);
	ui.listView->setModel(ptModel);
}

void MorphoWindow::addPoint(VAMImageIndex idx)
{
	QModelIndexList list = pointViews[idx]->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to add!"));
		return;
	}

	int index = list[0].row();

	ptNames.push_back(currentSchema.getPoint(index, idx).getName());
	selectedPoints.push_back(std::vector<int>({ index,idx }));

	ptModel->setStringList(ptNames);
	ui.listView->setModel(ptModel);
}

void MorphoWindow::delPoint()
{
	QModelIndexList list = ui.listView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a point to delete!"));
		return;
	}

	int index = list[0].row();

	QString name = ptNames.at(index);
	ptNames.erase(ptNames.begin() + index);

	std::vector<int> element = selectedPoints.at(index);
	selectedPoints.erase(selectedPoints.begin() + index);

	ptModel->setStringList(ptNames);
	ui.listView->setModel(ptModel);
}


bool MorphoWindow::saveMorpho()
{	
	VAMLogger::log("Morpho save");

	// Save morpho
	QDir dir;
	dir.setPath(currentProject->getAbsProjLib() + "/Morphometrics/");
	if (!dir.exists())
		dir.mkpath(".");

	QString fname = dir.absolutePath() + "/data.morph";
	QFile file(fname);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

		VAMLogger::log("Morphometrics save error");
		QMessageBox::warning(NULL, VAMTranslatedStrings::errorOut1(), VAMTranslatedStrings::errorOut2());
		return false;
	}

	QTextStream out(&file);
	writeDoubleVector(selectedPoints, out);

	// No longer modified
	morphoModified = false;

	return true;
}

void MorphoWindow::closeEvent(QCloseEvent *event)
{
	// Prompt for save if modified
	if (morphoModified)
	{
		VAMLogger::log("Prompt plani changed");

		QMessageBox msgBox;
		msgBox.setText(tr("The current morphometrics data has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Save)
		{
			VAMLogger::log("Save");
			bool ret = saveMorpho();
			if (!ret)
			{
				event->ignore();
				return;
			}
			event->accept();
		}
		else if (ret == QMessageBox::Cancel)
		{
			VAMLogger::log("Cancel");
			event->ignore();
			return;
		}
		else
		{
			VAMLogger::log("Discard");
			event->accept();
		}
	}
	else
	{
		VAMLogger::log("Bye");
		event->accept();
	}
	delete this;
}

void MorphoWindow::setCurrentProject(Project *value)
{
	currentProject = value;

	if (currentProject->getMeasCnt() <= 0)
	{
		VAMLogger::log("Missing measurement");
		QMessageBox::critical(this, tr("Error: Measuremet file missing"), tr("The measurement file is missing from the project. This shouldn't happen!"));
		return;
	}

	currentMeasurement = currentProject->getMeasurement(0);

	currentSchema = currentMeasurement.getSchema();

	// Read camera files
	std::vector<cv::Mat> A(VAMMaxVideos), d(VAMMaxVideos);
	for (int i = 0; i < currentProject->getDB(0).getVideoCnt(); i++)
	{
		cv::FileStorage fs((currentProject->getAbsProjLib() + "/Database/cam" + QString::number(i) + ".yaml").toStdString(), cv::FileStorage::READ);
		fs["cam"] >> A[i];
		fs["dist"] >> d[i];
	}
	currentMeasurement.setA(A);
	currentMeasurement.setD(d);

	QDir dir;
	dir.setPath(currentProject->getAbsProjLib() + "/Morphometrics/");
	if (!dir.exists())
		dir.mkpath(".");

	// Read from file
	QString fname = dir.absolutePath() + "/data.morph";
	QFile file(fname);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		selectedPoints = readDoubleVector<int>(in);
	}

	setupWindow();
}
