#include "AutoStillDialog.h"

AutoStillDialog::AutoStillDialog(QWidget* parent) : QDialog(parent) {}

void AutoStillDialog::showDialog(std::vector<QStringList> stills, StillDB* db)
{
	ui.setupUi(this);
	stillLists = stills;
	videoCnt = stills.size();

	currentDB = db;

	images = { ui.image1, ui.image3, ui.image2, ui.image4 };
	videoTitles = { ui.label1, ui.label3, ui.label2, ui.label4 };
	lists = { ui.stillList1, ui.stillList3, ui.stillList2, ui.stillList4 };

	outModel = new QStringListModel(outENAR);
	ui.pairedList->setModel(outModel);

	for (int i = 0; i < VAMMaxVideos; i++)
	{
		if (i < videoCnt)
		{
			stillListModels.push_back(new QStringListModel(stillLists[i]));
			lists[i]->setModel(stillListModels[i]);
			outStillList.push_back(QStringList());
			connect(lists[i], &QListView::clicked,
				std::bind(&AutoStillDialog::stillClicked, this, std::placeholders::_1, toIdx(i)));
			lists[i]->setCurrentIndex(stillListModels[i]->index(0));
			stillClicked(stillListModels[i]->index(0), toIdx(i));
		}
		images[i]->setHidden(i >= videoCnt);
		lists[i]->setHidden(i >= videoCnt);
		videoTitles[i]->setHidden(i >= videoCnt);
	}

	connect(ui.addElem, &QPushButton::clicked, this, &AutoStillDialog::addStill);
	connect(ui.deleteElem, &QPushButton::clicked, this, &AutoStillDialog::removeStill);
	connect(ui.saveBtn, &QPushButton::clicked, this, &AutoStillDialog::saveBtn);
	connect(ui.cancelBtn, &QPushButton::clicked, this, &AutoStillDialog::cancelBtn);

	this->show();
}

void AutoStillDialog::addStill()
{
	std::vector< int > indices;
	std::vector< QString > stillNames;
	QString ENAR = "";
	bool complete = true;
	int firstGoodIdx = 0;

	for (int i = 0; i < videoCnt; i++)
	{
		int idx = lists[i]->currentIndex().row();
		if (idx < 0)
		{
			indices.push_back(-1);
			stillNames.push_back("#NONE");
			complete = false;
			if (firstGoodIdx == i)
			{
				firstGoodIdx++;
			}
			continue;
		}

		indices.push_back(idx);
		stillNames.push_back(stillLists[i][idx]);
	}

	if (firstGoodIdx == videoCnt)
	{
		indices.clear();
		stillNames.clear();
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select at least one image!"));
		return;
	}

	for (int j = 0; j < videoCnt; j++)
	{
		ENAR = readQRBarCode(stillNames[j]);
	}
	bool foundCode = ENAR.isEmpty();

	// Prompt for ID
	using std::placeholders::_1;
	std::function<bool(QString)> func = std::bind(&StillDB::isIDNew, currentDB, std::placeholders::_1);
	if (getName(tr("Specify ID"),
		foundCode ? tr("No QR/Barcode found") : tr("Found QR/Barcode:"),
		tr("Please specify a name!"),
		tr("An animal with this ID already exists!"),
		foundCode ? ENAR = stillNames[firstGoodIdx].split("/").back().split(".")[0] : ENAR,
		func))
	{
		stillIndices.push_back(indices);
		if (!complete)
		{
			ENAR += tr(" - INCOMPLETE");
		}
		outENAR.push_back(ENAR);
		outModel->setStringList(outENAR);
		ui.pairedList->update();

		for (int i = 0; i < videoCnt; i++)
		{
			outStillList[i].push_back(stillNames[i]);
			lists[i]->clearSelection();
			lists[i]->setCurrentIndex(stillListModels[i]->index(-1));
			if (indices[i] >= 0)
				lists[i]->setRowHidden(indices[i], true);
		}
	}
}

void AutoStillDialog::removeStill()
{
	int idx = ui.pairedList->currentIndex().row();
	if (idx < 0)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select an entry from the list!"));
		return;
	}

	auto indices = stillIndices[idx];

	for (int i = 0; i < videoCnt; i++)
	{
		if (indices[i] >= 0)
			lists[i]->setRowHidden(indices[i], false);
		outStillList[i].erase(outStillList[i].begin() + idx);
	}
	stillIndices.erase(stillIndices.begin() + idx);
	outENAR.erase(outENAR.begin() + idx);
	outModel->setStringList(outENAR);
	ui.pairedList->update();
}

void AutoStillDialog::saveBtn()
{
	// Add still

	for (int i = 0; i < videoCnt; i++)
	{
		for (int j = 0; j < outENAR.size(); j++)
		{
			currentDB->addStill(outStillList[i][j], outENAR[j], 0, toIdx(i), true);
		}
	}
	this->close();
}

void AutoStillDialog::cancelBtn()
{
	this->close();
}

void AutoStillDialog::stillClicked(QModelIndex index, VAMImageIndex idx)
{
	QString imName = stillLists[idx][index.row()];
	cv::Mat img = imgRead(imName, cv::Mat(), cv::Mat());

	if (!img.data)
	{
		VAMLogger::log("Non existing images...");
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load").append(" %1.").arg(QDir::toNativeSeparators(imName)));

		return;
	}

	float imgRatio = (float)img.cols / (float)img.rows;
	float labelRatio = (float)images[idx]->size().width() / (float)images[idx]->size().height();
	float sideFact = imgRatio < labelRatio ? 
		(float)images[idx]->size().height() / (float)img.rows : 
		(float)images[idx]->size().width() / (float)img.cols;
	cv::resize(img, img, cv::Size(0, 0), sideFact, sideFact);
	images[idx]->setPixmap(QPixmap::fromImage(cvMatToQImage(img)));
}
