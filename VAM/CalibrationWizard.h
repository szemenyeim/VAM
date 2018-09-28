#pragma once
#include <QWizard>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QProgressbar>
#include "Utility.h"


class CalibrationWizard :
	public QWizard
{
	Q_OBJECT
public:
	enum {
		Page_Intro, Page_Video,	Page_Conclusion
	};

	CalibrationWizard(VAMImageIndex _idx, QString projLib, QWidget *parent = 0);
private:
	VAMImageIndex idx;
};

class IntroPage : public QWizardPage
{
	Q_OBJECT

public:
	IntroPage(QWidget *parent = 0);
	int nextId() const override;
	
private:
	QLabel *topLabel;
	QLabel *textLabel;
	QPushButton *printButton;

private slots:
	void printChessBoard();
};

class VideoPage : public QWizardPage
{
	Q_OBJECT

public:
	VideoPage(VAMImageIndex _idx, QString _projLib, QWidget *parent = 0);
	int nextId() const override;

signals:
	void computed();

private:
	QLabel *videoLabel;
	QLabel *calibLabel;
	QLabel *spinLabel;
	QPushButton *loadVideoBtn;
	QPushButton *calibrateBtn;
	QCheckBox *distortion;
	QProgressBar *progressBar;

	QSpinBox *maxFrameBox;

	VAMImageIndex idx;
	QString projLib;

	int skipNum;
	int maxVal;

	private slots:
	void getVideoFile();
	void calibrate();
	void calibrate_thread();
	void imageDone();
};

