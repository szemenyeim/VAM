#pragma once
#include <qdialog.h>
#include "Utility.h"
#include "CustomLabel.h"
#include <ui_autoStillDiag.h>
#include "StillDB.h"

class AutoStillDialog : public QDialog
{
	Q_OBJECT

public:
	AutoStillDialog(QWidget* parent = 0);

	void showDialog(std::vector< QStringList > stills, StillDB* db);

private:
	Ui::Dialog ui;

	std::vector < QStringList > stillLists;
	std::vector < QStringListModel* > stillListModels;

	std::vector < QLabel* > videoTitles;
	std::vector < CustomLabel* > images;
	std::vector < QListView* > lists;

	std::vector< QStringList > outStillList;
	std::vector< std::vector<int> > stillIndices;
	QStringList outENAR;
	QStringListModel* outModel;

	StillDB* currentDB;

	int videoCnt;
	
	void addStill();
	void removeStill();

	void saveBtn();
	void cancelBtn();

	void stillClicked(QModelIndex index, VAMImageIndex idx);

signals:

	void newData(std::vector < QStringList > stillLists);

};

