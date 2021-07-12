/********************************************************************************
** Form generated from reading UI file 'video.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_H
#define UI_VIDEO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionSave_stills;
    QAction *actionOpen_still;
    QAction *actionEdit_still;
    QAction *actionDelete_still;
    QAction *actionEtalon;
    QAction *actionDone;
    QAction *actionVideo_Order;
    QAction *actionDetect;
    QAction *actionComplete;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_35;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *horizontalLayout_36;
    QVBoxLayout *verticalLayout_21;
    QLabel *videoName1;
    QVBoxLayout *videoL1;
    QHBoxLayout *horizontalLayout_38;
    QPushButton *prevVid1;
    QPushButton *frameBack1;
    QPushButton *play1;
    QPushButton *frameForward1;
    QPushButton *nextVid1;
    QVBoxLayout *verticalLayout_22;
    QLabel *videoName2;
    QVBoxLayout *videoL2;
    QHBoxLayout *horizontalLayout_40;
    QPushButton *prevVid2;
    QPushButton *frameBack2;
    QPushButton *play2;
    QPushButton *frameForward2;
    QPushButton *nextVid2;
    QHBoxLayout *horizontalLayout_41;
    QVBoxLayout *verticalLayout_23;
    QLabel *videoName3;
    QVBoxLayout *videoL3;
    QHBoxLayout *horizontalLayout_43;
    QPushButton *prevVid3;
    QPushButton *frameBack3;
    QPushButton *play3;
    QPushButton *frameForward3;
    QPushButton *nextVid3;
    QVBoxLayout *verticalLayout_24;
    QLabel *videoName4;
    QVBoxLayout *videoL4;
    QHBoxLayout *horizontalLayout_45;
    QPushButton *prevVid4;
    QPushButton *frameBack4;
    QPushButton *play4;
    QPushButton *frameForward4;
    QPushButton *nextVid4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label;
    QSlider *volumeSlider;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_7;
    QListView *stillImageList;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *VideoWindow)
    {
        if (VideoWindow->objectName().isEmpty())
            VideoWindow->setObjectName(QString::fromUtf8("VideoWindow"));
        VideoWindow->setWindowModality(Qt::NonModal);
        VideoWindow->resize(1250, 900);
        VideoWindow->setMinimumSize(QSize(1250, 900));
        VideoWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(VideoWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionSave_as = new QAction(VideoWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon1);
        actionSave_stills = new QAction(VideoWindow);
        actionSave_stills->setObjectName(QString::fromUtf8("actionSave_stills"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1462024260_Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_stills->setIcon(icon2);
        actionOpen_still = new QAction(VideoWindow);
        actionOpen_still->setObjectName(QString::fromUtf8("actionOpen_still"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462367694_folder_open-add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_still->setIcon(icon3);
        actionEdit_still = new QAction(VideoWindow);
        actionEdit_still->setObjectName(QString::fromUtf8("actionEdit_still"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit_still->setIcon(icon4);
        actionDelete_still = new QAction(VideoWindow);
        actionDelete_still->setObjectName(QString::fromUtf8("actionDelete_still"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_still->setIcon(icon5);
        actionEtalon = new QAction(VideoWindow);
        actionEtalon->setObjectName(QString::fromUtf8("actionEtalon"));
        actionEtalon->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEtalon->setIcon(icon6);
        actionDone = new QAction(VideoWindow);
        actionDone->setObjectName(QString::fromUtf8("actionDone"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon7);
        actionVideo_Order = new QAction(VideoWindow);
        actionVideo_Order->setObjectName(QString::fromUtf8("actionVideo_Order"));
        actionVideo_Order->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/VAM/Icons/if_tile_windows_vertically_16x16_10027.png"), QSize(), QIcon::Normal, QIcon::On);
        icon8.addFile(QString::fromUtf8(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Active, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/VAM/Icons/if_tile_windows_vertically_16x16_10027.png"), QSize(), QIcon::Active, QIcon::On);
        icon8.addFile(QString::fromUtf8(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Selected, QIcon::Off);
        actionVideo_Order->setIcon(icon8);
        actionDetect = new QAction(VideoWindow);
        actionDetect->setObjectName(QString::fromUtf8("actionDetect"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/VAM/Icons/1462036191_Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDetect->setIcon(icon9);
        actionComplete = new QAction(VideoWindow);
        actionComplete->setObjectName(QString::fromUtf8("actionComplete"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionComplete->setIcon(icon10);
        centralwidget = new QWidget(VideoWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        videoName1 = new QLabel(centralwidget);
        videoName1->setObjectName(QString::fromUtf8("videoName1"));
        videoName1->setMaximumSize(QSize(450, 20));

        verticalLayout_21->addWidget(videoName1);

        videoL1 = new QVBoxLayout();
        videoL1->setObjectName(QString::fromUtf8("videoL1"));

        verticalLayout_21->addLayout(videoL1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        prevVid1 = new QPushButton(centralwidget);
        prevVid1->setObjectName(QString::fromUtf8("prevVid1"));
        prevVid1->setMaximumSize(QSize(30, 25));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/VAM/Icons/1462036188_Fast-Backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevVid1->setIcon(icon11);

        horizontalLayout_38->addWidget(prevVid1);

        frameBack1 = new QPushButton(centralwidget);
        frameBack1->setObjectName(QString::fromUtf8("frameBack1"));
        frameBack1->setMaximumSize(QSize(30, 25));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/VAM/Icons/1462036208_Skip-Backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameBack1->setIcon(icon12);

        horizontalLayout_38->addWidget(frameBack1);

        play1 = new QPushButton(centralwidget);
        play1->setObjectName(QString::fromUtf8("play1"));
        play1->setMaximumSize(QSize(30, 25));
        play1->setIcon(icon9);

        horizontalLayout_38->addWidget(play1);

        frameForward1 = new QPushButton(centralwidget);
        frameForward1->setObjectName(QString::fromUtf8("frameForward1"));
        frameForward1->setMaximumSize(QSize(30, 25));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/VAM/Icons/1462036208_Skip-Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameForward1->setIcon(icon13);

        horizontalLayout_38->addWidget(frameForward1);

        nextVid1 = new QPushButton(centralwidget);
        nextVid1->setObjectName(QString::fromUtf8("nextVid1"));
        nextVid1->setMaximumSize(QSize(30, 25));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/VAM/Icons/1462036188_Fast-Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextVid1->setIcon(icon14);

        horizontalLayout_38->addWidget(nextVid1);


        verticalLayout_21->addLayout(horizontalLayout_38);


        horizontalLayout_36->addLayout(verticalLayout_21);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        videoName2 = new QLabel(centralwidget);
        videoName2->setObjectName(QString::fromUtf8("videoName2"));
        videoName2->setMaximumSize(QSize(450, 20));

        verticalLayout_22->addWidget(videoName2);

        videoL2 = new QVBoxLayout();
        videoL2->setObjectName(QString::fromUtf8("videoL2"));

        verticalLayout_22->addLayout(videoL2);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        prevVid2 = new QPushButton(centralwidget);
        prevVid2->setObjectName(QString::fromUtf8("prevVid2"));
        prevVid2->setMaximumSize(QSize(30, 25));
        prevVid2->setIcon(icon11);

        horizontalLayout_40->addWidget(prevVid2);

        frameBack2 = new QPushButton(centralwidget);
        frameBack2->setObjectName(QString::fromUtf8("frameBack2"));
        frameBack2->setMaximumSize(QSize(30, 25));
        frameBack2->setIcon(icon12);

        horizontalLayout_40->addWidget(frameBack2);

        play2 = new QPushButton(centralwidget);
        play2->setObjectName(QString::fromUtf8("play2"));
        play2->setMaximumSize(QSize(30, 25));
        play2->setIcon(icon9);

        horizontalLayout_40->addWidget(play2);

        frameForward2 = new QPushButton(centralwidget);
        frameForward2->setObjectName(QString::fromUtf8("frameForward2"));
        frameForward2->setMaximumSize(QSize(30, 25));
        frameForward2->setIcon(icon13);

        horizontalLayout_40->addWidget(frameForward2);

        nextVid2 = new QPushButton(centralwidget);
        nextVid2->setObjectName(QString::fromUtf8("nextVid2"));
        nextVid2->setMaximumSize(QSize(30, 25));
        nextVid2->setIcon(icon14);

        horizontalLayout_40->addWidget(nextVid2);


        verticalLayout_22->addLayout(horizontalLayout_40);


        horizontalLayout_36->addLayout(verticalLayout_22);


        verticalLayout_20->addLayout(horizontalLayout_36);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        videoName3 = new QLabel(centralwidget);
        videoName3->setObjectName(QString::fromUtf8("videoName3"));
        videoName3->setMaximumSize(QSize(450, 20));

        verticalLayout_23->addWidget(videoName3);

        videoL3 = new QVBoxLayout();
        videoL3->setObjectName(QString::fromUtf8("videoL3"));

        verticalLayout_23->addLayout(videoL3);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        prevVid3 = new QPushButton(centralwidget);
        prevVid3->setObjectName(QString::fromUtf8("prevVid3"));
        prevVid3->setMaximumSize(QSize(30, 25));
        prevVid3->setIcon(icon11);

        horizontalLayout_43->addWidget(prevVid3);

        frameBack3 = new QPushButton(centralwidget);
        frameBack3->setObjectName(QString::fromUtf8("frameBack3"));
        frameBack3->setMaximumSize(QSize(30, 25));
        frameBack3->setIcon(icon12);

        horizontalLayout_43->addWidget(frameBack3);

        play3 = new QPushButton(centralwidget);
        play3->setObjectName(QString::fromUtf8("play3"));
        play3->setMaximumSize(QSize(30, 25));
        play3->setIcon(icon9);

        horizontalLayout_43->addWidget(play3);

        frameForward3 = new QPushButton(centralwidget);
        frameForward3->setObjectName(QString::fromUtf8("frameForward3"));
        frameForward3->setMaximumSize(QSize(30, 25));
        frameForward3->setIcon(icon13);

        horizontalLayout_43->addWidget(frameForward3);

        nextVid3 = new QPushButton(centralwidget);
        nextVid3->setObjectName(QString::fromUtf8("nextVid3"));
        nextVid3->setMaximumSize(QSize(30, 25));
        nextVid3->setIcon(icon14);

        horizontalLayout_43->addWidget(nextVid3);


        verticalLayout_23->addLayout(horizontalLayout_43);


        horizontalLayout_41->addLayout(verticalLayout_23);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        videoName4 = new QLabel(centralwidget);
        videoName4->setObjectName(QString::fromUtf8("videoName4"));
        videoName4->setMaximumSize(QSize(450, 20));

        verticalLayout_24->addWidget(videoName4);

        videoL4 = new QVBoxLayout();
        videoL4->setObjectName(QString::fromUtf8("videoL4"));

        verticalLayout_24->addLayout(videoL4);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        prevVid4 = new QPushButton(centralwidget);
        prevVid4->setObjectName(QString::fromUtf8("prevVid4"));
        prevVid4->setMaximumSize(QSize(30, 25));
        prevVid4->setIcon(icon11);

        horizontalLayout_45->addWidget(prevVid4);

        frameBack4 = new QPushButton(centralwidget);
        frameBack4->setObjectName(QString::fromUtf8("frameBack4"));
        frameBack4->setMaximumSize(QSize(30, 25));
        frameBack4->setIcon(icon12);

        horizontalLayout_45->addWidget(frameBack4);

        play4 = new QPushButton(centralwidget);
        play4->setObjectName(QString::fromUtf8("play4"));
        play4->setMaximumSize(QSize(30, 25));
        play4->setIcon(icon9);

        horizontalLayout_45->addWidget(play4);

        frameForward4 = new QPushButton(centralwidget);
        frameForward4->setObjectName(QString::fromUtf8("frameForward4"));
        frameForward4->setMaximumSize(QSize(30, 25));
        frameForward4->setIcon(icon13);

        horizontalLayout_45->addWidget(frameForward4);

        nextVid4 = new QPushButton(centralwidget);
        nextVid4->setObjectName(QString::fromUtf8("nextVid4"));
        nextVid4->setMaximumSize(QSize(30, 25));
        nextVid4->setIcon(icon14);

        horizontalLayout_45->addWidget(nextVid4);


        verticalLayout_24->addLayout(horizontalLayout_45);


        horizontalLayout_41->addLayout(verticalLayout_24);


        verticalLayout_20->addLayout(horizontalLayout_41);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(35, 25));
        label->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/volume.png")));

        horizontalLayout_2->addWidget(label);

        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMaximumSize(QSize(200, 30));
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(50);
        volumeSlider->setOrientation(Qt::Horizontal);
        volumeSlider->setTickPosition(QSlider::TicksBelow);
        volumeSlider->setTickInterval(5);

        horizontalLayout_2->addWidget(volumeSlider);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout_20->addLayout(horizontalLayout_2);


        horizontalLayout_35->addLayout(verticalLayout_20);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(200, 20));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(label_7);

        stillImageList = new QListView(centralwidget);
        stillImageList->setObjectName(QString::fromUtf8("stillImageList"));
        stillImageList->setMinimumSize(QSize(0, 0));
        stillImageList->setMaximumSize(QSize(200, 200000));
        stillImageList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_19->addWidget(stillImageList);


        horizontalLayout_35->addLayout(verticalLayout_19);


        horizontalLayout->addLayout(horizontalLayout_35);

        VideoWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(VideoWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        VideoWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(VideoWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        VideoWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(VideoWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        toolBar_2->setLayoutDirection(Qt::RightToLeft);
        toolBar_2->setToolButtonStyle(Qt::ToolButtonIconOnly);
        VideoWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar->addAction(actionDetect);
        toolBar_2->addAction(actionDelete_still);
        toolBar_2->addAction(actionEtalon);
        toolBar_2->addAction(actionEdit_still);
        toolBar_2->addAction(actionOpen_still);
        toolBar_2->addAction(actionComplete);
        toolBar_2->addAction(actionSave_stills);
        toolBar_2->addSeparator();
        toolBar_2->addAction(actionVideo_Order);

        retranslateUi(VideoWindow);

        QMetaObject::connectSlotsByName(VideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VideoWindow)
    {
        VideoWindow->setWindowTitle(QCoreApplication::translate("VideoWindow", "Take Snapshots", nullptr));
        actionSave->setText(QCoreApplication::translate("VideoWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("VideoWindow", "Save Database", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("VideoWindow", "Save as...", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as->setToolTip(QCoreApplication::translate("VideoWindow", "Save Database", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_stills->setText(QCoreApplication::translate("VideoWindow", "Save stills", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_stills->setToolTip(QCoreApplication::translate("VideoWindow", "Save still pictures", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_stills->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_still->setText(QCoreApplication::translate("VideoWindow", "Open still", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen_still->setToolTip(QCoreApplication::translate("VideoWindow", "Open still pictures", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen_still->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEdit_still->setText(QCoreApplication::translate("VideoWindow", "Edit still", nullptr));
#if QT_CONFIG(tooltip)
        actionEdit_still->setToolTip(QCoreApplication::translate("VideoWindow", "Edit the selected still", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionEdit_still->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete_still->setText(QCoreApplication::translate("VideoWindow", "Delete still", nullptr));
#if QT_CONFIG(tooltip)
        actionDelete_still->setToolTip(QCoreApplication::translate("VideoWindow", "Remove the selected still", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDelete_still->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEtalon->setText(QCoreApplication::translate("VideoWindow", "Etalon", nullptr));
#if QT_CONFIG(tooltip)
        actionEtalon->setToolTip(QCoreApplication::translate("VideoWindow", "Set the selected image as the global etalon", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionEtalon->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDone->setText(QCoreApplication::translate("VideoWindow", "Done", nullptr));
#if QT_CONFIG(tooltip)
        actionDone->setToolTip(QCoreApplication::translate("VideoWindow", "Return to the main window", nullptr));
#endif // QT_CONFIG(tooltip)
        actionVideo_Order->setText(QCoreApplication::translate("VideoWindow", "Video Order", nullptr));
#if QT_CONFIG(tooltip)
        actionVideo_Order->setToolTip(QCoreApplication::translate("VideoWindow", "Check to order videos vertically first", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDetect->setText(QCoreApplication::translate("VideoWindow", "Automatic Detection", nullptr));
#if QT_CONFIG(tooltip)
        actionDetect->setToolTip(QCoreApplication::translate("VideoWindow", "Launch automatic cattle detection", nullptr));
#endif // QT_CONFIG(tooltip)
        actionComplete->setText(QCoreApplication::translate("VideoWindow", "Complete Entry", nullptr));
#if QT_CONFIG(tooltip)
        actionComplete->setToolTip(QCoreApplication::translate("VideoWindow", "Add missing still to incomplete entry", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionComplete->setShortcut(QCoreApplication::translate("VideoWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        videoName1->setText(QString());
#if QT_CONFIG(tooltip)
        prevVid1->setToolTip(QCoreApplication::translate("VideoWindow", "Previous video", nullptr));
#endif // QT_CONFIG(tooltip)
        prevVid1->setText(QString());
#if QT_CONFIG(tooltip)
        frameBack1->setToolTip(QCoreApplication::translate("VideoWindow", "Step back", nullptr));
#endif // QT_CONFIG(tooltip)
        frameBack1->setText(QString());
#if QT_CONFIG(tooltip)
        play1->setToolTip(QCoreApplication::translate("VideoWindow", "Play", nullptr));
#endif // QT_CONFIG(tooltip)
        play1->setText(QString());
#if QT_CONFIG(tooltip)
        frameForward1->setToolTip(QCoreApplication::translate("VideoWindow", "Step forward", nullptr));
#endif // QT_CONFIG(tooltip)
        frameForward1->setText(QString());
#if QT_CONFIG(tooltip)
        nextVid1->setToolTip(QCoreApplication::translate("VideoWindow", "Next video", nullptr));
#endif // QT_CONFIG(tooltip)
        nextVid1->setText(QString());
        videoName2->setText(QString());
#if QT_CONFIG(tooltip)
        prevVid2->setToolTip(QCoreApplication::translate("VideoWindow", "Previous video", nullptr));
#endif // QT_CONFIG(tooltip)
        prevVid2->setText(QString());
#if QT_CONFIG(tooltip)
        frameBack2->setToolTip(QCoreApplication::translate("VideoWindow", "Step back", nullptr));
#endif // QT_CONFIG(tooltip)
        frameBack2->setText(QString());
#if QT_CONFIG(tooltip)
        play2->setToolTip(QCoreApplication::translate("VideoWindow", "Play", nullptr));
#endif // QT_CONFIG(tooltip)
        play2->setText(QString());
#if QT_CONFIG(tooltip)
        frameForward2->setToolTip(QCoreApplication::translate("VideoWindow", "Step forward", nullptr));
#endif // QT_CONFIG(tooltip)
        frameForward2->setText(QString());
#if QT_CONFIG(tooltip)
        nextVid2->setToolTip(QCoreApplication::translate("VideoWindow", "Next video", nullptr));
#endif // QT_CONFIG(tooltip)
        nextVid2->setText(QString());
        videoName3->setText(QString());
#if QT_CONFIG(tooltip)
        prevVid3->setToolTip(QCoreApplication::translate("VideoWindow", "Previous video", nullptr));
#endif // QT_CONFIG(tooltip)
        prevVid3->setText(QString());
#if QT_CONFIG(tooltip)
        frameBack3->setToolTip(QCoreApplication::translate("VideoWindow", "Step back", nullptr));
#endif // QT_CONFIG(tooltip)
        frameBack3->setText(QString());
#if QT_CONFIG(tooltip)
        play3->setToolTip(QCoreApplication::translate("VideoWindow", "Play", nullptr));
#endif // QT_CONFIG(tooltip)
        play3->setText(QString());
#if QT_CONFIG(tooltip)
        frameForward3->setToolTip(QCoreApplication::translate("VideoWindow", "Step forward", nullptr));
#endif // QT_CONFIG(tooltip)
        frameForward3->setText(QString());
#if QT_CONFIG(tooltip)
        nextVid3->setToolTip(QCoreApplication::translate("VideoWindow", "Next video", nullptr));
#endif // QT_CONFIG(tooltip)
        nextVid3->setText(QString());
        videoName4->setText(QString());
#if QT_CONFIG(tooltip)
        prevVid4->setToolTip(QCoreApplication::translate("VideoWindow", "Previous video", nullptr));
#endif // QT_CONFIG(tooltip)
        prevVid4->setText(QString());
#if QT_CONFIG(tooltip)
        frameBack4->setToolTip(QCoreApplication::translate("VideoWindow", "Step back", nullptr));
#endif // QT_CONFIG(tooltip)
        frameBack4->setText(QString());
#if QT_CONFIG(tooltip)
        play4->setToolTip(QCoreApplication::translate("VideoWindow", "Play", nullptr));
#endif // QT_CONFIG(tooltip)
        play4->setText(QString());
#if QT_CONFIG(tooltip)
        frameForward4->setToolTip(QCoreApplication::translate("VideoWindow", "Step forward", nullptr));
#endif // QT_CONFIG(tooltip)
        frameForward4->setText(QString());
#if QT_CONFIG(tooltip)
        nextVid4->setToolTip(QCoreApplication::translate("VideoWindow", "Next video", nullptr));
#endif // QT_CONFIG(tooltip)
        nextVid4->setText(QString());
        label_2->setText(QString());
        label->setText(QString());
        label_3->setText(QString());
        label_7->setText(QCoreApplication::translate("VideoWindow", "Saved stills", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("VideoWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QCoreApplication::translate("VideoWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoWindow: public Ui_VideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_H
