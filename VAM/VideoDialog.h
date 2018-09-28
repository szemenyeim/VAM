#pragma once

#include<QtWidgets\qdialog.h>
#include "Utility.h"
#include<ui_videoDiag.h>

class VideoDialog : public QDialog
{
	Q_OBJECT

public:
	VideoDialog(QWidget *parent = 0);

	void showDialog(QStringList videos);

	void setBoxVal(double val);
    
    void hideDistBox();

private:
	Ui::VideoDialog ui;

	QStringList videoList; 
	
	QStringListModel * model;
    
    double videoBox;

	// Sort the list of videos based on start date
	void sortVidList(QStringList &in, QStringList &out);

	// Get the start date of the video
	long getVidTime(QString &val);

	void addVideo();
	void removeVideo();
	void videoUp();
	void videoDown();

	void saveBtn();
	void cancelBtn();
    
    // Spinbox value change handler functions
    void videoBoxChanged(double val);

signals:

	void newData(QStringList list);
    void distChanged(double val);

};
