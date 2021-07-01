/********************************************************************************
** Form generated from reading UI file 'marker.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKER_H
#define UI_MARKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomLabel.h"
#include "markerwindow.h"

QT_BEGIN_NAMESPACE

class Ui_MarkerWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionPrevious_Image;
    QAction *actionNext_image;
    QAction *actionSelection_mode;
    QAction *actionErase_points;
    QAction *actionDone;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLabel *pointName;
    QLabel *label_4;
    QLabel *imgDoneLabel;
    QLabel *label_3;
    QLabel *imgRemLabel;
    QLabel *label_5;
    QLabel *animalIDLabel;
    QCheckBox *autoCorrection;
    QLabel *tipLabel;
    QHBoxLayout *horizontalLayout_3;
    CustomScrollArea *imageScrollArea;
    QWidget *scrollAreaWidgetContents;
    CustomLabel *imageLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *confBox;
    QLabel *label_8;
    QListView *imagesRemList;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MarkerWindow)
    {
        if (MarkerWindow->objectName().isEmpty())
            MarkerWindow->setObjectName(QString::fromUtf8("MarkerWindow"));
        MarkerWindow->resize(1200, 870);
        MarkerWindow->setMinimumSize(QSize(1200, 870));
        MarkerWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(MarkerWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionSave_as = new QAction(MarkerWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon1);
        actionPrevious_Image = new QAction(MarkerWindow);
        actionPrevious_Image->setObjectName(QString::fromUtf8("actionPrevious_Image"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1462036195_arrow-left1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious_Image->setIcon(icon2);
        actionNext_image = new QAction(MarkerWindow);
        actionNext_image->setObjectName(QString::fromUtf8("actionNext_image"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462036198_arrow-right1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_image->setIcon(icon3);
        actionSelection_mode = new QAction(MarkerWindow);
        actionSelection_mode->setObjectName(QString::fromUtf8("actionSelection_mode"));
        actionSelection_mode->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelection_mode->setIcon(icon4);
        actionErase_points = new QAction(MarkerWindow);
        actionErase_points->setObjectName(QString::fromUtf8("actionErase_points"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1462036280_trashcan-delete2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionErase_points->setIcon(icon5);
        actionDone = new QAction(MarkerWindow);
        actionDone->setObjectName(QString::fromUtf8("actionDone"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon6);
        centralwidget = new QWidget(MarkerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(150, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_6);

        pointName = new QLabel(centralwidget);
        pointName->setObjectName(QString::fromUtf8("pointName"));
        pointName->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(pointName);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(150, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_4);

        imgDoneLabel = new QLabel(centralwidget);
        imgDoneLabel->setObjectName(QString::fromUtf8("imgDoneLabel"));
        imgDoneLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(imgDoneLabel);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(200, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        imgRemLabel = new QLabel(centralwidget);
        imgRemLabel->setObjectName(QString::fromUtf8("imgRemLabel"));
        imgRemLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(imgRemLabel);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(200, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_5);

        animalIDLabel = new QLabel(centralwidget);
        animalIDLabel->setObjectName(QString::fromUtf8("animalIDLabel"));
        animalIDLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(animalIDLabel);

        autoCorrection = new QCheckBox(centralwidget);
        autoCorrection->setObjectName(QString::fromUtf8("autoCorrection"));
        autoCorrection->setMaximumSize(QSize(200, 20));
        autoCorrection->setChecked(true);

        horizontalLayout->addWidget(autoCorrection);


        verticalLayout_2->addLayout(horizontalLayout);

        tipLabel = new QLabel(centralwidget);
        tipLabel->setObjectName(QString::fromUtf8("tipLabel"));
        tipLabel->setMinimumSize(QSize(0, 20));
        tipLabel->setMaximumSize(QSize(16777215, 20));
        tipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(tipLabel);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        imageScrollArea = new CustomScrollArea(centralwidget);
        imageScrollArea->setObjectName(QString::fromUtf8("imageScrollArea"));
        imageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        imageScrollArea->setWidgetResizable(false);
        imageScrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 168, 1159, 364));
        imageScrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(imageScrollArea);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        imageLabel = new CustomLabel(centralwidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(imageLabel, 5, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(200, 20));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        confBox = new QSpinBox(centralwidget);
        confBox->setObjectName(QString::fromUtf8("confBox"));
        confBox->setMaximumSize(QSize(50, 20));
        confBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        confBox->setMaximum(100);
        confBox->setSingleStep(5);
        confBox->setValue(100);

        horizontalLayout_4->addWidget(confBox);


        verticalLayout->addLayout(horizontalLayout_4);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(200, 20));
        label_8->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(label_8);

        imagesRemList = new QListView(centralwidget);
        imagesRemList->setObjectName(QString::fromUtf8("imagesRemList"));
        imagesRemList->setMaximumSize(QSize(200, 60000));
        imagesRemList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(imagesRemList);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MarkerWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MarkerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MarkerWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MarkerWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MarkerWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar->addAction(actionPrevious_Image);
        toolBar->addAction(actionNext_image);
        toolBar->addSeparator();
        toolBar->addAction(actionSelection_mode);
        toolBar->addAction(actionErase_points);

        retranslateUi(MarkerWindow);

        QMetaObject::connectSlotsByName(MarkerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MarkerWindow)
    {
        MarkerWindow->setWindowTitle(QCoreApplication::translate("MarkerWindow", "Mark measurement points", nullptr));
        actionSave->setText(QCoreApplication::translate("MarkerWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MarkerWindow", "Save measurement", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MarkerWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("MarkerWindow", "Save as", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as->setToolTip(QCoreApplication::translate("MarkerWindow", "Save measurement", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("MarkerWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPrevious_Image->setText(QCoreApplication::translate("MarkerWindow", "Previous Image", nullptr));
#if QT_CONFIG(tooltip)
        actionPrevious_Image->setToolTip(QCoreApplication::translate("MarkerWindow", "Display the previous image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPrevious_Image->setShortcut(QCoreApplication::translate("MarkerWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNext_image->setText(QCoreApplication::translate("MarkerWindow", "Next image", nullptr));
#if QT_CONFIG(tooltip)
        actionNext_image->setToolTip(QCoreApplication::translate("MarkerWindow", "Display the mext image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNext_image->setShortcut(QCoreApplication::translate("MarkerWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelection_mode->setText(QCoreApplication::translate("MarkerWindow", "Selection mode", nullptr));
#if QT_CONFIG(tooltip)
        actionSelection_mode->setToolTip(QCoreApplication::translate("MarkerWindow", "Toggle the marker selection mode", nullptr));
#endif // QT_CONFIG(tooltip)
        actionErase_points->setText(QCoreApplication::translate("MarkerWindow", "Erase points", nullptr));
#if QT_CONFIG(tooltip)
        actionErase_points->setToolTip(QCoreApplication::translate("MarkerWindow", "Removes all marks from the current image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionErase_points->setShortcut(QCoreApplication::translate("MarkerWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDone->setText(QCoreApplication::translate("MarkerWindow", "Done", nullptr));
#if QT_CONFIG(tooltip)
        actionDone->setToolTip(QCoreApplication::translate("MarkerWindow", "Return to the main window", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("MarkerWindow", "Next Point:", nullptr));
        pointName->setText(QString());
        label_4->setText(QCoreApplication::translate("MarkerWindow", "Images done:", nullptr));
        imgDoneLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("MarkerWindow", "Images remaining:", nullptr));
        imgRemLabel->setText(QString());
        label_5->setText(QCoreApplication::translate("MarkerWindow", "Next animal ID:", nullptr));
        animalIDLabel->setText(QString());
#if QT_CONFIG(tooltip)
        autoCorrection->setToolTip(QCoreApplication::translate("MarkerWindow", "Automatically account for the diference in the etalon's and animal's position using the measurement of the animal's height", nullptr));
#endif // QT_CONFIG(tooltip)
        autoCorrection->setText(QCoreApplication::translate("MarkerWindow", "Automatic Correction", nullptr));
        tipLabel->setText(QString());
        imageLabel->setText(QString());
        label->setText(QCoreApplication::translate("MarkerWindow", "Measurement Confidence (%):", nullptr));
        label_8->setText(QCoreApplication::translate("MarkerWindow", "Remaining Images", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MarkerWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MarkerWindow: public Ui_MarkerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKER_H
