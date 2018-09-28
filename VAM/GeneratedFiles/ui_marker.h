/********************************************************************************
** Form generated from reading UI file 'marker.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKER_H
#define UI_MARKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            MarkerWindow->setObjectName(QStringLiteral("MarkerWindow"));
        MarkerWindow->setWindowModality(Qt::ApplicationModal);
        MarkerWindow->resize(1200, 870);
        MarkerWindow->setMinimumSize(QSize(1200, 870));
        MarkerWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(MarkerWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionSave_as = new QAction(MarkerWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon1);
        actionPrevious_Image = new QAction(MarkerWindow);
        actionPrevious_Image->setObjectName(QStringLiteral("actionPrevious_Image"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/VAM/Icons/1462036195_arrow-left1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious_Image->setIcon(icon2);
        actionNext_image = new QAction(MarkerWindow);
        actionNext_image->setObjectName(QStringLiteral("actionNext_image"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/VAM/Icons/1462036198_arrow-right1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_image->setIcon(icon3);
        actionSelection_mode = new QAction(MarkerWindow);
        actionSelection_mode->setObjectName(QStringLiteral("actionSelection_mode"));
        actionSelection_mode->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelection_mode->setIcon(icon4);
        actionErase_points = new QAction(MarkerWindow);
        actionErase_points->setObjectName(QStringLiteral("actionErase_points"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/VAM/Icons/1462036280_trashcan-delete2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionErase_points->setIcon(icon5);
        actionDone = new QAction(MarkerWindow);
        actionDone->setObjectName(QStringLiteral("actionDone"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon6);
        centralwidget = new QWidget(MarkerWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(150, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_6);

        pointName = new QLabel(centralwidget);
        pointName->setObjectName(QStringLiteral("pointName"));
        pointName->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(pointName);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(150, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_4);

        imgDoneLabel = new QLabel(centralwidget);
        imgDoneLabel->setObjectName(QStringLiteral("imgDoneLabel"));
        imgDoneLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(imgDoneLabel);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(200, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        imgRemLabel = new QLabel(centralwidget);
        imgRemLabel->setObjectName(QStringLiteral("imgRemLabel"));
        imgRemLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(imgRemLabel);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(200, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_5);

        animalIDLabel = new QLabel(centralwidget);
        animalIDLabel->setObjectName(QStringLiteral("animalIDLabel"));
        animalIDLabel->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(animalIDLabel);

        autoCorrection = new QCheckBox(centralwidget);
        autoCorrection->setObjectName(QStringLiteral("autoCorrection"));
        autoCorrection->setMaximumSize(QSize(200, 20));
        autoCorrection->setChecked(true);

        horizontalLayout->addWidget(autoCorrection);


        verticalLayout_2->addLayout(horizontalLayout);

        tipLabel = new QLabel(centralwidget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));
        tipLabel->setMinimumSize(QSize(0, 20));
        tipLabel->setMaximumSize(QSize(16777215, 20));
        tipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(tipLabel);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        imageScrollArea = new CustomScrollArea(centralwidget);
        imageScrollArea->setObjectName(QStringLiteral("imageScrollArea"));
        imageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        imageScrollArea->setWidgetResizable(false);
        imageScrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 168, 1159, 364));
        imageScrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(imageScrollArea);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        imageLabel = new CustomLabel(centralwidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(imageLabel, 5, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(200, 20));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        confBox = new QSpinBox(centralwidget);
        confBox->setObjectName(QStringLiteral("confBox"));
        confBox->setMaximumSize(QSize(50, 20));
        confBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        confBox->setMaximum(100);
        confBox->setSingleStep(5);
        confBox->setValue(100);

        horizontalLayout_4->addWidget(confBox);


        verticalLayout->addLayout(horizontalLayout_4);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(200, 20));
        label_8->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(label_8);

        imagesRemList = new QListView(centralwidget);
        imagesRemList->setObjectName(QStringLiteral("imagesRemList"));
        imagesRemList->setMaximumSize(QSize(200, 60000));
        imagesRemList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(imagesRemList);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MarkerWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MarkerWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MarkerWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MarkerWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
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
        MarkerWindow->setWindowTitle(QApplication::translate("MarkerWindow", "Mark measurement points", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MarkerWindow", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MarkerWindow", "Save measurement", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MarkerWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_as->setText(QApplication::translate("MarkerWindow", "Save as", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_as->setToolTip(QApplication::translate("MarkerWindow", "Save measurement", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("MarkerWindow", "Ctrl+Shift+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPrevious_Image->setText(QApplication::translate("MarkerWindow", "Previous Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPrevious_Image->setToolTip(QApplication::translate("MarkerWindow", "Display the previous image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionPrevious_Image->setShortcut(QApplication::translate("MarkerWindow", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNext_image->setText(QApplication::translate("MarkerWindow", "Next image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNext_image->setToolTip(QApplication::translate("MarkerWindow", "Display the mext image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNext_image->setShortcut(QApplication::translate("MarkerWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSelection_mode->setText(QApplication::translate("MarkerWindow", "Selection mode", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSelection_mode->setToolTip(QApplication::translate("MarkerWindow", "Toggle the marker selection mode", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionErase_points->setText(QApplication::translate("MarkerWindow", "Erase points", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionErase_points->setToolTip(QApplication::translate("MarkerWindow", "Removes all marks from the current image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionErase_points->setShortcut(QApplication::translate("MarkerWindow", "Ctrl+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDone->setText(QApplication::translate("MarkerWindow", "Done", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDone->setToolTip(QApplication::translate("MarkerWindow", "Return to the main window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("MarkerWindow", "Next Point:", Q_NULLPTR));
        pointName->setText(QString());
        label_4->setText(QApplication::translate("MarkerWindow", "Images done:", Q_NULLPTR));
        imgDoneLabel->setText(QString());
        label_3->setText(QApplication::translate("MarkerWindow", "Images remaining:", Q_NULLPTR));
        imgRemLabel->setText(QString());
        label_5->setText(QApplication::translate("MarkerWindow", "Next animal ID:", Q_NULLPTR));
        animalIDLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        autoCorrection->setToolTip(QApplication::translate("MarkerWindow", "Automatically account for the diference in the etalon's and animal's position using the measurement of the animal's height", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        autoCorrection->setText(QApplication::translate("MarkerWindow", "Automatic Correction", Q_NULLPTR));
        tipLabel->setText(QString());
        imageLabel->setText(QString());
        label->setText(QApplication::translate("MarkerWindow", "Measurement Confidence (%):", Q_NULLPTR));
        label_8->setText(QApplication::translate("MarkerWindow", "Remaining Images", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MarkerWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MarkerWindow: public Ui_MarkerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKER_H
