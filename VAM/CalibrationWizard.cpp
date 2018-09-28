#include "CalibrationWizard.h"
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrent>
#include <opencv2\opencv.hpp>



CalibrationWizard::CalibrationWizard(VAMImageIndex _idx, QString projLib, QWidget *parent) : idx(_idx), QWizard(parent)
{
	setPage(Page_Intro, new IntroPage);
	setPage(Page_Video, new VideoPage(idx, projLib));

	setStartId(Page_Intro);

	setWizardStyle(ModernStyle);
	
	setPixmap(QWizard::LogoPixmap, QPixmap(":/VAM/Icons/1462455465_centimeter.png"));

	setWindowTitle(tr("Calibration"));
}


IntroPage::IntroPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Introduction"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

	topLabel = new QLabel(tr("This wizard will help you calibrate your camera."));
	topLabel->setWordWrap(true);

	textLabel = new QLabel(tr("As a first step, print this calibration image (if you haven't already), and tape it to a smooth surface!") + "\n" + 
		tr("Then create a short (< 1 min) video where the calibration object is seen fully from different angles!"));
	topLabel->setWordWrap(true);

	printButton = new QPushButton(tr("Save Calibration File"));
	connect(printButton, &QPushButton::clicked, this, &IntroPage::printChessBoard);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	layout->addWidget(textLabel);
	layout->addWidget(printButton);
	setLayout(layout);
}

void IntroPage::printChessBoard()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Calibration Image"),
		QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/chessboard.png",
		tr("PNG Images (*.png)"));
	QFile file(":/VAM/Icons/chessboard.png");
	if (file.open(QIODevice::ReadOnly))
	{
		file.copy(fileName);
	}

}

int IntroPage::nextId() const
{
	return CalibrationWizard::Page_Video;
	
}

VideoPage::VideoPage(VAMImageIndex _idx, QString _projLib, QWidget *parent)
	: idx(_idx), projLib(_projLib), QWizardPage(parent)
{
	setTitle(tr("Calibrate"));
	setSubTitle(tr("Please load the created video, then press calibrate."));

	videoLabel = new QLabel("");
	calibLabel = new QLabel("");
	spinLabel = new QLabel(tr("Maximum number of frames to search for chessboard"));

	loadVideoBtn = new QPushButton(tr("Load Video"));
	calibrateBtn = new QPushButton(tr("Calibrate"));

	distortion = new QCheckBox(tr("Estimate radial distortion"));
	maxFrameBox = new QSpinBox();
	maxFrameBox->setMinimum(1);
	maxFrameBox->setMaximum(10000);
	maxFrameBox->setValue(2500);

	progressBar = new QProgressBar();
	progressBar->setMaximum(2500);
	progressBar->setValue(0);

	connect(loadVideoBtn, &QPushButton::clicked, this, &VideoPage::getVideoFile);
	connect(calibrateBtn, &QPushButton::clicked, this, &VideoPage::calibrate);
	connect(this, &VideoPage::computed, this, &VideoPage::imageDone);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(loadVideoBtn);
	layout->addWidget(videoLabel);
	layout->addWidget(distortion);
	layout->addWidget(spinLabel);
	layout->addWidget(maxFrameBox);
	layout->addWidget(calibrateBtn);
	layout->addWidget(progressBar);
	layout->addWidget(calibLabel);
	setLayout(layout);
}

void VideoPage::getVideoFile()
{
	QString video = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.avi *.mp4 *.mkv *.vid *.mv4 *.mts *.m4v)"));
	videoLabel->setText(video);
}

void VideoPage::calibrate()
{
	QString video = videoLabel->text();

	if (video.isEmpty())
	{
		QMessageBox::warning(this, tr("No Video"), tr("Please set the video first!"));
		return;
	}

	cv::VideoCapture cap(video.toStdString());
	if (!cap.isOpened())
	{
		QMessageBox::critical(this, tr("Cannot open video file!"), tr("Please make sure it is not corrupt or deleted!"));
		return;
	}
	cap.release();
	skipNum = 50;
	maxVal = maxFrameBox->value();

	progressBar->setMaximum(maxVal);
	progressBar->setValue(0);

	loadVideoBtn->setEnabled(false);
	calibrateBtn->setEnabled(false);

	QtConcurrent::run(this, &VideoPage::calibrate_thread);

}

void VideoPage::calibrate_thread()
{
	calibLabel->setText("");
	QString video = videoLabel->text(); 
	cv::VideoCapture cap(video.toStdString());

	bool dist = distortion->isChecked();

	int fCnt = 0;
	int skipCnt = skipNum;

	std::vector<std::vector<cv::Point2f>> imgPts;
	std::vector<std::vector<cv::Point3f>> worldPts;
	cv::Size cbSize(9, 6);
	cv::Size imgSize;
	std::vector<cv::Point3f> cbPts;
	for (int i = 0; i < cbSize.height; i++)
	{
		for (int j = 0; j < cbSize.width; j++)
		{
			cbPts.push_back(cv::Point3f(j, i, 0));
		}
	}

	cv::Mat image;
	while (cap.read(image))
	{
		emit computed();

		imgSize = image.size();
		fCnt++;
		if (skipCnt < skipNum)
		{
			skipCnt++;
			continue;
		}

		std::vector<cv::Point2f> pts;
		float ratio = 640.0 / imgSize.width;
		cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
		cv::Mat lowRes;
		cv::resize(image, lowRes, cv::Size(0, 0), ratio, ratio);
		skipCnt = 0;
		if (cv::findChessboardCorners(lowRes, cbSize, pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE))
		{
			if( !cv::findChessboardCorners(image, cbSize, pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE) )
				continue;
			cornerSubPix(image, pts, cv::Size(11, 11),
				cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 60, 0.01));
			imgPts.push_back(pts);
			worldPts.push_back(cbPts);
		}
		if (fCnt > maxVal || imgPts.size() >= 25)
		{
			break;
		}
	}

	maxVal = fCnt;

	if (imgPts.empty())
	{
		calibLabel->setText(tr("Calibration failed! No chessboard found"));
		emit computed();
		return;
	}
	calibLabel->setText(tr("Computing camera parameters"));

	cv::Mat A = cv::Mat::zeros(3, 3, CV_64F), d, rv, tv;
	/*A.at<double>(0, 0) = A.at<double>(1, 1) = 1000.0;
	A.at<double>(2, 2) = 1.0;
	A.at<double>(0, 2) = (imgSize.width-1) / 2.0;
	A.at<double>(1, 2) = (imgSize.height-1) / 2.0;*/
	int flags = cv::CALIB_ZERO_TANGENT_DIST /*+ cv::CALIB_USE_INTRINSIC_GUESS*/ + cv::CALIB_FIX_PRINCIPAL_POINT + cv::CALIB_FIX_K5 + cv::CALIB_FIX_K6;
	if (!dist)
	{
		flags += cv::CALIB_FIX_K1 + cv::CALIB_FIX_K2 + cv::CALIB_FIX_K3 + cv::CALIB_FIX_K4;
	}

	float error = cv::calibrateCamera(worldPts, imgPts, imgSize, A, d, rv, tv, flags);

	calibLabel->setText(tr("Calibration successful! Calibration error: ") + QString::number(error));

	cv::FileStorage fs((projLib + "/Database/cam" + QString::number(idx) + ".yaml").toStdString(), cv::FileStorage::WRITE);
	fs << "cam" << A << "dist" << d;
	emit computed();
}


void VideoPage::imageDone()
{
	int i = progressBar->value();
	progressBar->setValue(i + 1);
	if (i >= maxVal)
	{
		loadVideoBtn->setEnabled(true);
		calibrateBtn->setEnabled(true);
		if (i != progressBar->maximum())
		{
			progressBar->setValue(progressBar->maximum());
		}
	}
}

int VideoPage::nextId() const
{
	return -1;
}
