/********************************************************************************
** Form generated from reading UI file 'video.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_H
#define UI_VIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QAction *actionRename_still;
    QAction *actionDelete_still;
    QAction *actionEtalon;
    QAction *actionDone;
    QAction *actionVideo_Order;
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
            VideoWindow->setObjectName(QStringLiteral("VideoWindow"));
        VideoWindow->setWindowModality(Qt::ApplicationModal);
        VideoWindow->resize(1250, 900);
        VideoWindow->setMinimumSize(QSize(1250, 900));
        VideoWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(VideoWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionSave_as = new QAction(VideoWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon1);
        actionSave_stills = new QAction(VideoWindow);
        actionSave_stills->setObjectName(QStringLiteral("actionSave_stills"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/VAM/Icons/1462024260_Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_stills->setIcon(icon2);
        actionOpen_still = new QAction(VideoWindow);
        actionOpen_still->setObjectName(QStringLiteral("actionOpen_still"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/VAM/Icons/1462367694_folder_open-add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_still->setIcon(icon3);
        actionRename_still = new QAction(VideoWindow);
        actionRename_still->setObjectName(QStringLiteral("actionRename_still"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRename_still->setIcon(icon4);
        actionDelete_still = new QAction(VideoWindow);
        actionDelete_still->setObjectName(QStringLiteral("actionDelete_still"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_still->setIcon(icon5);
        actionEtalon = new QAction(VideoWindow);
        actionEtalon->setObjectName(QStringLiteral("actionEtalon"));
        actionEtalon->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEtalon->setIcon(icon6);
        actionDone = new QAction(VideoWindow);
        actionDone->setObjectName(QStringLiteral("actionDone"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon7);
        actionVideo_Order = new QAction(VideoWindow);
        actionVideo_Order->setObjectName(QStringLiteral("actionVideo_Order"));
        actionVideo_Order->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QStringLiteral(":/VAM/Icons/if_tile_windows_vertically_16x16_10027.png"), QSize(), QIcon::Normal, QIcon::On);
        icon8.addFile(QStringLiteral(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Active, QIcon::Off);
        icon8.addFile(QStringLiteral(":/VAM/Icons/if_tile_windows_vertically_16x16_10027.png"), QSize(), QIcon::Active, QIcon::On);
        icon8.addFile(QStringLiteral(":/VAM/Icons/if_tile_windows_horizontally_16x16_10026.png"), QSize(), QIcon::Selected, QIcon::Off);
        actionVideo_Order->setIcon(icon8);
        centralwidget = new QWidget(VideoWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        horizontalLayout_35->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        verticalLayout_20->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        videoName1 = new QLabel(centralwidget);
        videoName1->setObjectName(QStringLiteral("videoName1"));
        videoName1->setMaximumSize(QSize(450, 20));

        verticalLayout_21->addWidget(videoName1);

        videoL1 = new QVBoxLayout();
        videoL1->setObjectName(QStringLiteral("videoL1"));

        verticalLayout_21->addLayout(videoL1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
        prevVid1 = new QPushButton(centralwidget);
        prevVid1->setObjectName(QStringLiteral("prevVid1"));
        prevVid1->setMaximumSize(QSize(30, 25));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/VAM/Icons/1462036188_Fast-Backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevVid1->setIcon(icon9);

        horizontalLayout_38->addWidget(prevVid1);

        frameBack1 = new QPushButton(centralwidget);
        frameBack1->setObjectName(QStringLiteral("frameBack1"));
        frameBack1->setMaximumSize(QSize(30, 25));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/VAM/Icons/1462036208_Skip-Backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameBack1->setIcon(icon10);

        horizontalLayout_38->addWidget(frameBack1);

        play1 = new QPushButton(centralwidget);
        play1->setObjectName(QStringLiteral("play1"));
        play1->setMaximumSize(QSize(30, 25));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/VAM/Icons/1462036191_Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        play1->setIcon(icon11);

        horizontalLayout_38->addWidget(play1);

        frameForward1 = new QPushButton(centralwidget);
        frameForward1->setObjectName(QStringLiteral("frameForward1"));
        frameForward1->setMaximumSize(QSize(30, 25));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/VAM/Icons/1462036208_Skip-Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameForward1->setIcon(icon12);

        horizontalLayout_38->addWidget(frameForward1);

        nextVid1 = new QPushButton(centralwidget);
        nextVid1->setObjectName(QStringLiteral("nextVid1"));
        nextVid1->setMaximumSize(QSize(30, 25));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/VAM/Icons/1462036188_Fast-Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextVid1->setIcon(icon13);

        horizontalLayout_38->addWidget(nextVid1);


        verticalLayout_21->addLayout(horizontalLayout_38);


        horizontalLayout_36->addLayout(verticalLayout_21);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        videoName2 = new QLabel(centralwidget);
        videoName2->setObjectName(QStringLiteral("videoName2"));
        videoName2->setMaximumSize(QSize(450, 20));

        verticalLayout_22->addWidget(videoName2);

        videoL2 = new QVBoxLayout();
        videoL2->setObjectName(QStringLiteral("videoL2"));

        verticalLayout_22->addLayout(videoL2);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
        prevVid2 = new QPushButton(centralwidget);
        prevVid2->setObjectName(QStringLiteral("prevVid2"));
        prevVid2->setMaximumSize(QSize(30, 25));
        prevVid2->setIcon(icon9);

        horizontalLayout_40->addWidget(prevVid2);

        frameBack2 = new QPushButton(centralwidget);
        frameBack2->setObjectName(QStringLiteral("frameBack2"));
        frameBack2->setMaximumSize(QSize(30, 25));
        frameBack2->setIcon(icon10);

        horizontalLayout_40->addWidget(frameBack2);

        play2 = new QPushButton(centralwidget);
        play2->setObjectName(QStringLiteral("play2"));
        play2->setMaximumSize(QSize(30, 25));
        play2->setIcon(icon11);

        horizontalLayout_40->addWidget(play2);

        frameForward2 = new QPushButton(centralwidget);
        frameForward2->setObjectName(QStringLiteral("frameForward2"));
        frameForward2->setMaximumSize(QSize(30, 25));
        frameForward2->setIcon(icon12);

        horizontalLayout_40->addWidget(frameForward2);

        nextVid2 = new QPushButton(centralwidget);
        nextVid2->setObjectName(QStringLiteral("nextVid2"));
        nextVid2->setMaximumSize(QSize(30, 25));
        nextVid2->setIcon(icon13);

        horizontalLayout_40->addWidget(nextVid2);


        verticalLayout_22->addLayout(horizontalLayout_40);


        horizontalLayout_36->addLayout(verticalLayout_22);


        verticalLayout_20->addLayout(horizontalLayout_36);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QStringLiteral("horizontalLayout_41"));
        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        videoName3 = new QLabel(centralwidget);
        videoName3->setObjectName(QStringLiteral("videoName3"));
        videoName3->setMaximumSize(QSize(450, 20));

        verticalLayout_23->addWidget(videoName3);

        videoL3 = new QVBoxLayout();
        videoL3->setObjectName(QStringLiteral("videoL3"));

        verticalLayout_23->addLayout(videoL3);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
        prevVid3 = new QPushButton(centralwidget);
        prevVid3->setObjectName(QStringLiteral("prevVid3"));
        prevVid3->setMaximumSize(QSize(30, 25));
        prevVid3->setIcon(icon9);

        horizontalLayout_43->addWidget(prevVid3);

        frameBack3 = new QPushButton(centralwidget);
        frameBack3->setObjectName(QStringLiteral("frameBack3"));
        frameBack3->setMaximumSize(QSize(30, 25));
        frameBack3->setIcon(icon10);

        horizontalLayout_43->addWidget(frameBack3);

        play3 = new QPushButton(centralwidget);
        play3->setObjectName(QStringLiteral("play3"));
        play3->setMaximumSize(QSize(30, 25));
        play3->setIcon(icon11);

        horizontalLayout_43->addWidget(play3);

        frameForward3 = new QPushButton(centralwidget);
        frameForward3->setObjectName(QStringLiteral("frameForward3"));
        frameForward3->setMaximumSize(QSize(30, 25));
        frameForward3->setIcon(icon12);

        horizontalLayout_43->addWidget(frameForward3);

        nextVid3 = new QPushButton(centralwidget);
        nextVid3->setObjectName(QStringLiteral("nextVid3"));
        nextVid3->setMaximumSize(QSize(30, 25));
        nextVid3->setIcon(icon13);

        horizontalLayout_43->addWidget(nextVid3);


        verticalLayout_23->addLayout(horizontalLayout_43);


        horizontalLayout_41->addLayout(verticalLayout_23);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        videoName4 = new QLabel(centralwidget);
        videoName4->setObjectName(QStringLiteral("videoName4"));
        videoName4->setMaximumSize(QSize(450, 20));

        verticalLayout_24->addWidget(videoName4);

        videoL4 = new QVBoxLayout();
        videoL4->setObjectName(QStringLiteral("videoL4"));

        verticalLayout_24->addLayout(videoL4);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
        prevVid4 = new QPushButton(centralwidget);
        prevVid4->setObjectName(QStringLiteral("prevVid4"));
        prevVid4->setMaximumSize(QSize(30, 25));
        prevVid4->setIcon(icon9);

        horizontalLayout_45->addWidget(prevVid4);

        frameBack4 = new QPushButton(centralwidget);
        frameBack4->setObjectName(QStringLiteral("frameBack4"));
        frameBack4->setMaximumSize(QSize(30, 25));
        frameBack4->setIcon(icon10);

        horizontalLayout_45->addWidget(frameBack4);

        play4 = new QPushButton(centralwidget);
        play4->setObjectName(QStringLiteral("play4"));
        play4->setMaximumSize(QSize(30, 25));
        play4->setIcon(icon11);

        horizontalLayout_45->addWidget(play4);

        frameForward4 = new QPushButton(centralwidget);
        frameForward4->setObjectName(QStringLiteral("frameForward4"));
        frameForward4->setMaximumSize(QSize(30, 25));
        frameForward4->setIcon(icon12);

        horizontalLayout_45->addWidget(frameForward4);

        nextVid4 = new QPushButton(centralwidget);
        nextVid4->setObjectName(QStringLiteral("nextVid4"));
        nextVid4->setMaximumSize(QSize(30, 25));
        nextVid4->setIcon(icon13);

        horizontalLayout_45->addWidget(nextVid4);


        verticalLayout_24->addLayout(horizontalLayout_45);


        horizontalLayout_41->addLayout(verticalLayout_24);


        verticalLayout_20->addLayout(horizontalLayout_41);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(35, 25));
        label->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/volume.png")));

        horizontalLayout_2->addWidget(label);

        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setMaximumSize(QSize(200, 30));
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(50);
        volumeSlider->setOrientation(Qt::Horizontal);
        volumeSlider->setTickPosition(QSlider::TicksBelow);
        volumeSlider->setTickInterval(5);

        horizontalLayout_2->addWidget(volumeSlider);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout_20->addLayout(horizontalLayout_2);


        horizontalLayout_35->addLayout(verticalLayout_20);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(200, 20));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(label_7);

        stillImageList = new QListView(centralwidget);
        stillImageList->setObjectName(QStringLiteral("stillImageList"));
        stillImageList->setMinimumSize(QSize(0, 0));
        stillImageList->setMaximumSize(QSize(200, 200000));
        stillImageList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_19->addWidget(stillImageList);


        horizontalLayout_35->addLayout(verticalLayout_19);


        horizontalLayout->addLayout(horizontalLayout_35);

        VideoWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(VideoWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        VideoWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(VideoWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        VideoWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(VideoWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        toolBar_2->setLayoutDirection(Qt::RightToLeft);
        toolBar_2->setToolButtonStyle(Qt::ToolButtonIconOnly);
        VideoWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar_2->addAction(actionDelete_still);
        toolBar_2->addAction(actionEtalon);
        toolBar_2->addAction(actionRename_still);
        toolBar_2->addAction(actionOpen_still);
        toolBar_2->addAction(actionSave_stills);
        toolBar_2->addSeparator();
        toolBar_2->addAction(actionVideo_Order);

        retranslateUi(VideoWindow);

        QMetaObject::connectSlotsByName(VideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VideoWindow)
    {
        VideoWindow->setWindowTitle(QApplication::translate("VideoWindow", "Take Snapshots", Q_NULLPTR));
        actionSave->setText(QApplication::translate("VideoWindow", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("VideoWindow", "Save Database", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("VideoWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_as->setText(QApplication::translate("VideoWindow", "Save as...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_as->setToolTip(QApplication::translate("VideoWindow", "Save Database", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("VideoWindow", "Ctrl+Shift+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_stills->setText(QApplication::translate("VideoWindow", "Save stills", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_stills->setToolTip(QApplication::translate("VideoWindow", "Save still pictures", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_stills->setShortcut(QApplication::translate("VideoWindow", "Ctrl+G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionOpen_still->setText(QApplication::translate("VideoWindow", "Open still", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen_still->setToolTip(QApplication::translate("VideoWindow", "Open still pictures", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen_still->setShortcut(QApplication::translate("VideoWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionRename_still->setText(QApplication::translate("VideoWindow", "Rename still", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRename_still->setToolTip(QApplication::translate("VideoWindow", "Rename the selected still", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRename_still->setShortcut(QApplication::translate("VideoWindow", "Ctrl+R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDelete_still->setText(QApplication::translate("VideoWindow", "Delete still", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDelete_still->setToolTip(QApplication::translate("VideoWindow", "Remove the selected still", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDelete_still->setShortcut(QApplication::translate("VideoWindow", "Ctrl+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionEtalon->setText(QApplication::translate("VideoWindow", "Etalon", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEtalon->setToolTip(QApplication::translate("VideoWindow", "Set the selected image as the global etalon", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionEtalon->setShortcut(QApplication::translate("VideoWindow", "Ctrl+E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDone->setText(QApplication::translate("VideoWindow", "Done", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDone->setToolTip(QApplication::translate("VideoWindow", "Return to the main window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionVideo_Order->setText(QApplication::translate("VideoWindow", "Video Order", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionVideo_Order->setToolTip(QApplication::translate("VideoWindow", "Check to order videos vertically first", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        videoName1->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevVid1->setToolTip(QApplication::translate("VideoWindow", "Previous video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        prevVid1->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameBack1->setToolTip(QApplication::translate("VideoWindow", "Step back", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameBack1->setText(QString());
#ifndef QT_NO_TOOLTIP
        play1->setToolTip(QApplication::translate("VideoWindow", "Play", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        play1->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameForward1->setToolTip(QApplication::translate("VideoWindow", "Step forward", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameForward1->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextVid1->setToolTip(QApplication::translate("VideoWindow", "Next video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        nextVid1->setText(QString());
        videoName2->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevVid2->setToolTip(QApplication::translate("VideoWindow", "Previous video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        prevVid2->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameBack2->setToolTip(QApplication::translate("VideoWindow", "Step back", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameBack2->setText(QString());
#ifndef QT_NO_TOOLTIP
        play2->setToolTip(QApplication::translate("VideoWindow", "Play", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        play2->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameForward2->setToolTip(QApplication::translate("VideoWindow", "Step forward", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameForward2->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextVid2->setToolTip(QApplication::translate("VideoWindow", "Next video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        nextVid2->setText(QString());
        videoName3->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevVid3->setToolTip(QApplication::translate("VideoWindow", "Previous video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        prevVid3->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameBack3->setToolTip(QApplication::translate("VideoWindow", "Step back", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameBack3->setText(QString());
#ifndef QT_NO_TOOLTIP
        play3->setToolTip(QApplication::translate("VideoWindow", "Play", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        play3->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameForward3->setToolTip(QApplication::translate("VideoWindow", "Step forward", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameForward3->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextVid3->setToolTip(QApplication::translate("VideoWindow", "Next video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        nextVid3->setText(QString());
        videoName4->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevVid4->setToolTip(QApplication::translate("VideoWindow", "Previous video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        prevVid4->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameBack4->setToolTip(QApplication::translate("VideoWindow", "Step back", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameBack4->setText(QString());
#ifndef QT_NO_TOOLTIP
        play4->setToolTip(QApplication::translate("VideoWindow", "Play", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        play4->setText(QString());
#ifndef QT_NO_TOOLTIP
        frameForward4->setToolTip(QApplication::translate("VideoWindow", "Step forward", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        frameForward4->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextVid4->setToolTip(QApplication::translate("VideoWindow", "Next video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        nextVid4->setText(QString());
        label_2->setText(QString());
        label->setText(QString());
        label_3->setText(QString());
        label_7->setText(QApplication::translate("VideoWindow", "Saved stills", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("VideoWindow", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("VideoWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoWindow: public Ui_VideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_H
