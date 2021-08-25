
#pragma warning(push, 0)
#include <torch/script.h>
#include <torchvision/vision.h>
#pragma warning(pop)
#include "DetectionWizard.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrent>
#include <opencv2\opencv.hpp>
#include "AutoStillDialog.h"

static torch::jit::script::Module model;

DetectionWizard::DetectionWizard(Project* proj, StillDB *db, QWidget* parent) : QWizard(parent)
{
	setPage(Page_Intro, new IntroPage_2);
	setPage(Page_Video, new VideoPage_2(proj, db));

	setStartId(Page_Intro);

	setWizardStyle(ModernStyle);

	setPixmap(QWizard::LogoPixmap, QPixmap(":/VAM/Icons/1462455465_centimeter.png"));

	setWindowTitle(tr("Automatic Detection"));
}


IntroPage_2::IntroPage_2(QWidget* parent)
	: QWizardPage(parent)
{
	setTitle(tr("Introduction"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

	topLabel = new QLabel(tr("This wizard will launch automatic cattle detection."));
	topLabel->setWordWrap(true);

	textLabel = new QLabel(tr("As a first step, you will have to select the area in the videos where the cattle should be detected.\nThen you can set some parameters regarding the sensitivity of the detection. Finally, you can launch the detection."));
	topLabel->setWordWrap(true);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	layout->addWidget(textLabel);
	setLayout(layout);
}

int IntroPage_2::nextId() const
{
	return DetectionWizard::Page_Video;

}

VideoPage_2::VideoPage_2(Project *proj, StillDB *db, QWidget* parent)
	: currentProject(proj), currentDB(db), QWizardPage(parent)
{
	setTitle(tr("Detection"));
	setSubTitle(tr("First select the detection areas on the videos, then press detect."));

	videoLabel = new QLabel("Progress");
	calibLabel = new QLabel("Current video progress");
	delayLabel = new QLabel(tr("Motion is ignored for this many seconds after a detection."));
	motionLabel = new QLabel(tr("Motion detection sensitivity [0-1]."));
	confidenceLabel = new QLabel(tr("AI detection confidence threshold [0-1]."));
	areaLabel = new QLabel(tr("Cattle size threshold [0-1]."));

	selectAreaBtn = new QPushButton(tr("Select Detection Area"));
	detectBtn = new QPushButton(tr("Detect"));
	detectBtn->setEnabled(false);

	delayBox = new QSpinBox();
	delayBox->setMinimum(1);
	delayBox->setMaximum(20);
	delayBox->setValue(4);

	motionBox = new QDoubleSpinBox();
	motionBox->setMinimum(0.05);
	motionBox->setMaximum(0.5);
	motionBox->setValue(0.15);
	motionBox->setDecimals(2);

	confidenceBox = new QDoubleSpinBox();
	confidenceBox->setMinimum(0.25);
	confidenceBox->setMaximum(1.0);
	confidenceBox->setValue(0.7);
	confidenceBox->setDecimals(1);

	areaBox = new QDoubleSpinBox();
	areaBox->setMinimum(0.01);
	areaBox->setMaximum(0.75);
	areaBox->setValue(0.05);
	areaBox->setDecimals(2);

	progressBar = new QProgressBar();
	progressBar->setMaximum(VAMMaxVideos);
	progressBar->setValue(0);

	progressBar2 = new QProgressBar();
	progressBar2->setMaximum(20000);
	progressBar2->setValue(0);

	logBox = new QTextEdit();
	logBox->setReadOnly(true);

	model = torch::jit::load("./model.pt");
	model.eval();

	canceled_flag = false;
	finished = false;

	connect(selectAreaBtn, &QPushButton::clicked, this, &VideoPage_2::getActiveArea);
	connect(detectBtn, &QPushButton::clicked, this, &VideoPage_2::detect);
	connect(this, &VideoPage_2::computed, this, &VideoPage_2::imageDone);
	connect(this, &VideoPage_2::videoComputed, this, &VideoPage_2::videoDone);
	connect(this, &VideoPage_2::logChanged, this, &VideoPage_2::display_log);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(selectAreaBtn);
	layout->addWidget(delayLabel);
	layout->addWidget(delayBox);
	layout->addWidget(motionLabel);
	layout->addWidget(motionBox);
	layout->addWidget(confidenceLabel);
	layout->addWidget(confidenceBox);
	layout->addWidget(areaLabel);
	layout->addWidget(areaBox);
	layout->addWidget(detectBtn);
	layout->addWidget(videoLabel);
	layout->addWidget(progressBar);
	layout->addWidget(calibLabel);
	layout->addWidget(progressBar2);
	layout->addWidget(logBox);
	setLayout(layout);
}

void VideoPage_2::getActiveArea()
{
	AreaSelectWindow* window = new AreaSelectWindow(currentDB);
	connect(window, &AreaSelectWindow::finished, this, &VideoPage_2::areaSelectFinished);

	selectAreaBtn->setEnabled(false);
	detectBtn->setEnabled(false);

	window->setWindowTitle(tr("Select detection area."));
	window->setWindowModality(Qt::ApplicationModal);
	window->show();
}

bool VideoPage_2::checkCattle(const cv::Mat& img)
{
	cv::Mat resized;
	cv::Size newSize(512, (512.0 / img.cols) * img.rows);
	cv::resize(img, resized, newSize);
	cv::cvtColor(resized, resized, cv::COLOR_BGR2RGB);

	float imgSize = 1.0 / (512.0 * 256.0);

	cv::Mat padded;
	int padding = 256 - resized.rows;
	if (padding < 0)
	{
		int lPad, rPad;
		lPad = rPad = -padding / 2;
		if (padding % 2 == 1)
			lPad += 1;

		cv::Rect myROI(0, lPad, resized.cols, resized.rows + padding);
		padded = resized(myROI);
	}
	else {
		int lPad, rPad;
		lPad = rPad = padding / 2;
		if (padding % 2 == 1)
			lPad += 1;

		cv::copyMakeBorder(resized, padded, lPad, rPad, 0, 0, cv::BORDER_CONSTANT, cv::Scalar(0));
	}

	auto tensor_image = torch::from_blob(padded.data, { padded.rows, padded.cols, padded.channels() }, at::kByte);
	tensor_image = tensor_image.permute({ 2,0,1 });
	tensor_image = tensor_image.toType(c10::kFloat).mul(0.00392156862);
	tensor_image.to(c10::DeviceType::CPU);

	// Create a vector of inputs.
	std::vector < torch::jit::IValue > inputs;
	std::vector<torch::Tensor> input;
	input.push_back(tensor_image);
	inputs.push_back(input);
	inputs.push_back(0);

	try {
		// Execute the model and turn its output into a tensor.
		auto output = model.forward(inputs).toTuple()->elements()[1].toList().get(0).toGenericDict();

		auto bbs = output.at("boxes").toTensor();
		auto confs = output.at("scores").toTensor();

		auto size = bbs.sizes()[0];

		for (int i = 0; i < size; i++)
		{
			auto bb = bbs[i];
			auto conf = confs[i].item().toFloat();

			float bbSize = ((bb[3] - bb[1]) * (bb[2] - bb[0])).item().toFloat() * imgSize;

			logText += "Cattle check: Confidence: " + QString::number(conf) +
				" with ratio: " + QString::number(bbSize) + " - ";
			
			bool accept = false;

			if (conf > confT)
			{
				if (bbSize > areaT)
				{
					accept = true;
				}
			}

			if (accept)
			{
				logText += "Accepted\n";
				emit logChanged();
				return true;
			}
			else {
				logText += "Rejected\n";
				emit logChanged();
			}

		}

		
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		QMessageBox::warning(this, tr("Run failed"), tr("The neural network run has failed"));
	}

	return false;
}

void VideoPage_2::waitForFinished()
{
	while (!finished)
	{
		;
	}
}

void VideoPage_2::detect()
{
	progressBar->setMaximum(currentDB->getVideoCnt());
	progressBar->setValue(0);

	auto videos = currentDB->getVideos()[0];
	frameCnt = 0;
	for (auto video : videos)
	{
		cv::VideoCapture cap(video.toStdString());
		frameCnt += cap.get(cv::CAP_PROP_FRAME_COUNT);
	}

	progressBar2->setMaximum(frameCnt);
	progressBar2->setValue(0);

	delay = delayBox->value();
	motionT = motionBox->value();
	confT = confidenceBox->value();
	areaT = areaBox->value();

	logText = "Starting detection...\n";
	logBox->setText(logText);

	selectAreaBtn->setEnabled(false);
	detectBtn->setEnabled(false);
	wizard()->button(QWizard::BackButton)->setEnabled(false);
	wizard()->button(QWizard::FinishButton)->setEnabled(false);
	connect(wizard()->button(QWizard::CancelButton), &QPushButton::pressed, this, &VideoPage_2::canceled);
	connect(wizard()->button(QWizard::FinishButton), &QPushButton::pressed, this, &VideoPage_2::finished_slot);


	QtConcurrent::run(this, &VideoPage_2::detect_thread);

}

void VideoPage_2::detect_thread()
{
	for (int i = 0; i < currentDB->getVideoCnt(); i++)
	{
		auto videos = currentDB->getVideos()[i];
		bool sense = true;
		int cntr = 0;
		int lastFrame = 0;
		newImages.push_back(QStringList());

		for (auto video : videos)
		{
			cv::VideoCapture cap(video.toStdString());

			if (!cap.isOpened())
			{
				QMessageBox::critical(this, tr("Cannot open video file!"), tr("Please make sure it is not corrupt or deleted!"));
				return;
			}

			auto fgbg = cv::createBackgroundSubtractorMOG2();

			float fps = cap.get(cv::CAP_PROP_FPS);
			int frameSkip = fps * delay;

			while (true)
			{
				if (canceled_flag)
				{
					finished = true;
					return;
				}
				cv::Mat orig;
				bool ret = cap.read(orig);
				if (!ret)
				{
					break;
				}

				cv::Mat img;
				cv::resize(orig, img, cv::Size(640, 360));
				img = img(RoIs[i]);
				float frameSize = 1.0 / (img.cols * img.rows * 255.0);

				cv::Mat fgmask;
				fgbg->apply(img, fgmask);

				if (sense)
				{
					float ratio = cv::sum(fgmask)[0] * frameSize;
					if (ratio > motionT)
					{
						sense = false;
						lastFrame = cntr;

						logText += "Motion detected in frame " + QString::number(cntr) +
							" with ratio: " + QString::number(ratio) + "\n";
						emit logChanged();

						// check cattle
						if (checkCattle(orig))
						{
							QString baseDir = currentProject->getAbsProjLib() + "/Database/images/";
							QString name = baseDir + QString::number(i) + "_" + QString::number(cntr) + ".jpg";
							cv::imwrite(name.toStdString(), orig);
							newImages[i].push_back(name);

						}
					}
				}
				else if ((cntr - lastFrame) > frameSkip)
				{
					sense = true;
				}

				cntr++;
				emit computed();
			}
		}
		emit videoComputed();
	}
}

void VideoPage_2::display_log()
{
	logBox->setText(logText);
	logBox->verticalScrollBar()->setValue(logBox->verticalScrollBar()->maximum());
}

void VideoPage_2::finished_slot()
{
	AutoStillDialog* dialog = new AutoStillDialog();
	dialog->setWindowModality(Qt::ApplicationModal);

	if (dialog->showDialog(newImages, currentDB) )
		wizard()->close();
}

void VideoPage_2::videoDone()
{
	int i = progressBar->value();
	progressBar->setValue(i + 1);
	if (i >= currentDB->getVideoCnt() - 1)
	{
		detectBtn->setEnabled(true);
		selectAreaBtn->setEnabled(true);
		if (i != progressBar->maximum())
		{
			progressBar->setValue(progressBar->maximum());
		}

		wizard()->button(QWizard::FinishButton)->setEnabled(true);
		finished = true;
	}
	else {

		auto videos = currentDB->getVideos()[i+1];
		frameCnt = 0;
		for (auto video : videos)
		{
			cv::VideoCapture cap(video.toStdString());
			frameCnt += cap.get(cv::CAP_PROP_FRAME_COUNT);
		}

		progressBar2->setMaximum(frameCnt);
		progressBar2->setValue(0);
	}
}

void VideoPage_2::areaSelectFinished(std::vector<cv::Rect> _RoIs)
{
	RoIs = _RoIs;
	selectAreaBtn->setEnabled(true);
	detectBtn->setEnabled(true);
}

void VideoPage_2::canceled()
{
	canceled_flag = true;
	waitForFinished();
}


void VideoPage_2::imageDone()
{
	int i = progressBar2->value();
	progressBar2->setValue(i + 1);
}

int VideoPage_2::nextId() const
{
	return -1;
}

AreaSelectWindow::AreaSelectWindow(StillDB* db, QWidget* parent)
{
	drawing = false;

	QVBoxLayout* layout = new QVBoxLayout();
	QLabel* text = new QLabel(tr("Please draw the Region of Interest (RoI) on all images."));
	QHBoxLayout* imageLayoutT = new QHBoxLayout();
	QVBoxLayout* layout1 = new QVBoxLayout();
	QVBoxLayout* layout2 = new QVBoxLayout();
	for (int i = 0; i < VAMMaxVideos; i++)
	{
		CustomLabel* imgLabel = new CustomLabel();
		imgLabel->paintRect = true;
		images.push_back(imgLabel);
	}
	QPushButton* doneBtn = new QPushButton(tr("Done"));
	layout1->addWidget(images[0]);
	layout1->addWidget(images[1]);
	layout2->addWidget(images[2]);
	layout2->addWidget(images[3]);
	imageLayoutT->addLayout(layout1);
	imageLayoutT->addLayout(layout2);
	layout->addWidget(text);
	layout->addLayout(imageLayoutT);
	layout->addWidget(doneBtn);

	setLayout(layout);

	connect(doneBtn, &QPushButton::pressed, this, &AreaSelectWindow::donePushed);

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

	for (int i = 0; i < db->getVideoCnt(); i++)
	{
		auto imgLabel = images[i];
		connect(imgLabel, &CustomLabel::mousePressed,
			std::bind(&AreaSelectWindow::imageClicked, this, std::placeholders::_1, toIdx(i)));
		connect(imgLabel, &CustomLabel::mouseMoved,
			std::bind(&AreaSelectWindow::imageHovered, this, std::placeholders::_1, toIdx(i)));
		connect(imgLabel, &CustomLabel::mouseReleased,
			std::bind(&AreaSelectWindow::imageReleased, this, std::placeholders::_1, toIdx(i)));

		if (db->getVideos()[i].isEmpty())
		{
			QMessageBox::warning(this, tr("Video list empty"), tr("One or more video lists are empty. Please add videos for all cameras!"));
			this->close();
			return;
		}

		auto video = db->getVideos()[i][0];
		cv::VideoCapture cap(video.toStdString());
		cv::Mat img;
		bool ret = cap.read(img);
		if (ret)
		{
			cv::resize(img, img, cv::Size(640, 360));
			imgLabel->setPixmap(QPixmap::fromImage(cvMatToQImage(img)));
			imgLabel->update();
		}
		else {
			QMessageBox::warning(this, tr("Video missing"), tr("One or more video files are missing! Please make sure all video files in the database are available and try again!"));
			this->close();
			return;
		}

		RoIs.push_back(cv::Rect(256, 120, 128, 160));
		images[i]->x = 256;
		images[i]->y = 120;
		images[i]->x2 = 384;
		images[i]->y2 = 280;
		images[i]->update();
	}
}

void AreaSelectWindow::closeEvent(QCloseEvent* event)
{
	emit finished(RoIs);
	event->accept();
}

void AreaSelectWindow::donePushed()
{
	for (auto rect:RoIs)
	{
		if (rect.x == -1)
		{
			QMessageBox::warning(this, tr("RoIs missing"), tr("Please select the RoI on all images!"));
			return;
		}
	}
	emit finished(RoIs);
	this->close();
}

void AreaSelectWindow::imageClicked(const QPoint& p, VAMImageIndex idx)
{
	drawing = true;
	pt1 = p;
	images[idx]->x = p.x();
	images[idx]->y = p.y();
}

void AreaSelectWindow::imageHovered(const QPoint& p, VAMImageIndex idx)
{
	if (drawing)
	{
		pt2 = p;
		images[idx]->x2 = p.x();
		images[idx]->y2 = p.y();
		images[idx]->update();
	}
}

void AreaSelectWindow::imageReleased(const QPoint& p, VAMImageIndex idx)
{
	drawing = false;
	RoIs[idx] = cv::Rect(cv::Point(pt1.x(), pt1.y()), cv::Point(pt2.x(), pt2.y()));
}
