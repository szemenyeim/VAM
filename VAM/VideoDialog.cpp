#include <VideoDialog.h>

extern "C"
{
#include <vlc\vlc.h>
}
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <QDateTime>

VideoDialog::VideoDialog(QWidget *parent) : QDialog(parent) {}

void VideoDialog::showDialog(QStringList videos)
{
	ui.setupUi(this);
	videoList = videos;
	model = new QStringListModel(videoList);
	ui.dbListView->setModel(model);

	connect(ui.addVid, &QPushButton::clicked, this, &VideoDialog::addVideo);
	connect(ui.deleteVid, &QPushButton::clicked, this, &VideoDialog::removeVideo);
	connect(ui.vidUp, &QPushButton::clicked, this, &VideoDialog::videoUp);
	connect(ui.vidDown, &QPushButton::clicked, this, &VideoDialog::videoDown);
	connect(ui.saveBtn, &QPushButton::clicked, this, &VideoDialog::saveBtn);
	connect(ui.cancelBtn, &QPushButton::clicked, this, &VideoDialog::cancelBtn);
    
    connect(ui.camDistBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &VideoDialog::videoBoxChanged);

	this->show();

}

void VideoDialog::setBoxVal(double val)
{
	ui.camDistBox->setValue(val);
    videoBox = val;
}

void VideoDialog::hideDistBox()
{
    ui.camDistBox->setVisible(false);
    ui.label->setVisible(false);
}

void VideoDialog::sortVidList(QStringList &in, QStringList &out)
{

	// Check for emptyness
	if (in.isEmpty())
		return;

	// Sort alphabetically (default if video start date is unavailable)
	in.sort();

	// Store videos here with start date (map orders according to the key automatically)
	QMap< int, QString > map;

	for (int i = 0; i < in.size(); i++)
	{
		// Get video time
		QString vidName = in.at(i);
		long timeVal = getVidTime(vidName);

		VAMLogger::log("Video " + vidName + " time: " + QString::number(timeVal));

		// If such a time is already present, then increment it to make sure it's unique
		if (map.find(timeVal) != map.end())
			timeVal += i;

		// Add it to map
		map[timeVal] = in.at(i);
	}
	// Reset output list
	out.clear();

	// Put elements of the map into a vector
	for (auto currVal : map)
	{
		out.push_back(currVal);
	}

}

long VideoDialog::getVidTime(QString &val)
{
	qunsetenv("VLC_PLUGIN_PATH");

	VlcCommon::setPluginPath(QString("plugins"));

	VlcInstance instance(VlcCommon::args(), this);
	VlcMedia media(val, true, &instance);
	QDateTime dateTime = QDateTime::fromString(libvlc_media_get_meta(media.core(), libvlc_meta_Date));

	return dateTime.currentSecsSinceEpoch();
}

void VideoDialog::addVideo()
{
	QStringList addition = QFileDialog::getOpenFileNames(this, tr("Open Video File(s)"), "", tr("Video Files (*.avi *.mp4 *.mkv *.vid *.mv4 *.mts *.m4v)"));
    videoList.append(addition);
	
	// Order videos according to their start date
	sortVidList(videoList, videoList);
    
    for( auto video: videoList)
    {
        // Convert filename
        if( VAMFileAgent::isInProjLib(video) )
            VAMFileAgent::abs2rel(video);
    }


	model->setStringList(videoList);
	ui.dbListView->setModel(model);
}

void VideoDialog::removeVideo()
{
	QModelIndexList list = ui.dbListView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a video to delete!"));
		return;
	}

	videoList.erase(videoList.begin() + list[0].row());
	model->setStringList(videoList);
	ui.dbListView->setModel(model);
}

void VideoDialog::videoUp()
{
	QModelIndexList list = ui.dbListView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a video to move!"));
		return;
	}

	int index = list[0].row();
	QString element = videoList.at(index);
	videoList.erase(videoList.begin() + index);
	videoList.insert(index - 1, element);
	model->setStringList(videoList);
	ui.dbListView->setModel(model);
}

void VideoDialog::videoDown()
{
	QModelIndexList list = ui.dbListView->selectionModel()->selectedRows();
	if (list.isEmpty())
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
			tr("Please select a video to move!"));
		return;
	}

	int index = list[0].row();
	QString element = videoList.at(index);
	videoList.erase(videoList.begin() + index);
	videoList.insert(index + 1, element);
	model->setStringList(videoList);
	ui.dbListView->setModel(model);
}

void VideoDialog::videoBoxChanged(double val)
{
    videoBox = val;
}

void VideoDialog::saveBtn()
{
    emit distChanged( videoBox );
	emit newData(videoList);
	this->close();
}

void VideoDialog::cancelBtn()
{
	this->close();
}