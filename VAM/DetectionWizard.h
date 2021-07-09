#pragma once
#include <QWizard>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QProgressbar>
#include "Utility.h"
#include "StillDB.h"
#include "CustomLabel.h"


class DetectionWizard :
	public QWizard
{
	Q_OBJECT
public:
	enum {
		Page_Intro, Page_Video, Page_Conclusion
	};

	DetectionWizard(StillDB *db, QWidget* parent = 0);
private:
	StillDB* currentDB;
};

class IntroPage_2 : public QWizardPage
{
	Q_OBJECT

public:
	IntroPage_2(QWidget* parent = 0);
	int nextId() const override;

private:
	QLabel* topLabel;
	QLabel* textLabel;

};

class VideoPage_2 : public QWizardPage
{
	Q_OBJECT

public:
	VideoPage_2(StillDB* db, QWidget* parent = 0);
	int nextId() const override;

signals:
	void computed();
	void videoComputed();

private:

	StillDB* currentDB;

	QLabel* videoLabel;
	QLabel* calibLabel;
	QPushButton* selectAreaBtn;
	QPushButton* detectBtn;
	QProgressBar* progressBar;
	QProgressBar* progressBar2;

	QLabel* delayLabel;
	QSpinBox* delayBox;
	QLabel* motionLabel;
	QDoubleSpinBox* motionBox;
	QLabel* confidenceLabel;
	QDoubleSpinBox* confidenceBox;
	QLabel* areaLabel;
	QDoubleSpinBox* areaBox;

	VAMImageIndex idx;
	QString projLib;

	int frameCnt;

	std::vector<cv::Rect> RoIs;
	std::vector< QStringList > newImages;

	int delay;
	float confT;
	float motionT;
	float areaT;

	bool checkCattle(const cv::Mat& img);

private slots:
	void getActiveArea();
	void detect();
	void detect_thread();
	void imageDone();
	void videoDone();
	void areaSelectFinished(std::vector<cv::Rect> _RoIs);
};

class AreaSelectWindow : public QDialog
{
	Q_OBJECT
public:

	AreaSelectWindow(StillDB* db, QWidget* parent = 0);
private:

	std::vector<CustomLabel*> images;
	std::vector<cv::Rect> RoIs;
	bool drawing;
	QPoint pt1, pt2;

private slots:

	// Slot for button
	void donePushed();

	// Slot for handling image clicks
	void imageClicked(const QPoint& p, VAMImageIndex idx);

	// Slot for handling mouse movement over the image (for crosshair)
	void imageHovered(const QPoint& p, VAMImageIndex idx);

	// Slot for handling click release
	void imageReleased(const QPoint& p, VAMImageIndex idx);

signals:

	void finished(std::vector<cv::Rect> RoIs);

};