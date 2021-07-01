/********************************************************************************
** Form generated from reading UI file 'plani.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANI_H
#define UI_PLANI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomLabel.h"
#include "markerwindow.h"

QT_BEGIN_NAMESPACE

class Ui_PlaniWindow
{
public:
    QAction *actionSave;
    QAction *actionPrevious_Image;
    QAction *actionNext_image;
    QAction *actionClear_image;
    QAction *actionDone;
    QAction *actionExport;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    CustomLabel *imageLabel;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *methodBox;
    QLabel *label_3;
    QSpinBox *brushBox;
    QRadioButton *addremToggle;
    QPushButton *pushButton;
    QPushButton *rectBtn;
    QPushButton *segBtn;
    QPushButton *floodBtn;
    QPushButton *clearBtn;
    QPushButton *helpBtn;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSlider *threshSlider;
    QHBoxLayout *horizontalLayout_5;
    QLabel *msgLabel;
    QHBoxLayout *horizontalLayout_3;
    CustomScrollArea *imageScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *weightBox;
    QLabel *label_8;
    QListView *imagesRemList;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *PlaniWindow)
    {
        if (PlaniWindow->objectName().isEmpty())
            PlaniWindow->setObjectName(QString::fromUtf8("PlaniWindow"));
        PlaniWindow->resize(1250, 870);
        PlaniWindow->setMinimumSize(QSize(1250, 870));
        PlaniWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(PlaniWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionPrevious_Image = new QAction(PlaniWindow);
        actionPrevious_Image->setObjectName(QString::fromUtf8("actionPrevious_Image"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036195_arrow-left1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious_Image->setIcon(icon1);
        actionNext_image = new QAction(PlaniWindow);
        actionNext_image->setObjectName(QString::fromUtf8("actionNext_image"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1462036198_arrow-right1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_image->setIcon(icon2);
        actionClear_image = new QAction(PlaniWindow);
        actionClear_image->setObjectName(QString::fromUtf8("actionClear_image"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462036280_trashcan-delete2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_image->setIcon(icon3);
        actionDone = new QAction(PlaniWindow);
        actionDone->setObjectName(QString::fromUtf8("actionDone"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon4);
        actionExport = new QAction(PlaniWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon5);
        centralwidget = new QWidget(PlaniWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imageLabel = new CustomLabel(centralwidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(imageLabel, 5, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        methodBox = new QComboBox(centralwidget);
        methodBox->setObjectName(QString::fromUtf8("methodBox"));
        methodBox->setMinimumSize(QSize(120, 20));
        methodBox->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(methodBox);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        brushBox = new QSpinBox(centralwidget);
        brushBox->setObjectName(QString::fromUtf8("brushBox"));
        brushBox->setMinimumSize(QSize(60, 25));
        brushBox->setMaximumSize(QSize(60, 35));
        brushBox->setMinimum(1);
        brushBox->setValue(20);

        horizontalLayout->addWidget(brushBox);

        addremToggle = new QRadioButton(centralwidget);
        addremToggle->setObjectName(QString::fromUtf8("addremToggle"));
        addremToggle->setMinimumSize(QSize(120, 25));
        addremToggle->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(addremToggle);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(120, 25));
        pushButton->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(pushButton);

        rectBtn = new QPushButton(centralwidget);
        rectBtn->setObjectName(QString::fromUtf8("rectBtn"));
        rectBtn->setMinimumSize(QSize(120, 25));
        rectBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(rectBtn);

        segBtn = new QPushButton(centralwidget);
        segBtn->setObjectName(QString::fromUtf8("segBtn"));
        segBtn->setMinimumSize(QSize(120, 25));
        segBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(segBtn);

        floodBtn = new QPushButton(centralwidget);
        floodBtn->setObjectName(QString::fromUtf8("floodBtn"));
        floodBtn->setMinimumSize(QSize(120, 25));
        floodBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(floodBtn);

        clearBtn = new QPushButton(centralwidget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setMinimumSize(QSize(120, 25));
        clearBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(clearBtn);

        helpBtn = new QPushButton(centralwidget);
        helpBtn->setObjectName(QString::fromUtf8("helpBtn"));
        helpBtn->setMinimumSize(QSize(25, 25));
        helpBtn->setMaximumSize(QSize(35, 35));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VAM/Icons/1462037714_information2.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpBtn->setIcon(icon6);

        horizontalLayout->addWidget(helpBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(120, 20));
        label_4->setMaximumSize(QSize(120, 20));

        horizontalLayout_6->addWidget(label_4);

        threshSlider = new QSlider(centralwidget);
        threshSlider->setObjectName(QString::fromUtf8("threshSlider"));
        threshSlider->setMinimumSize(QSize(500, 20));
        threshSlider->setMaximumSize(QSize(16777215, 20));
        threshSlider->setMinimum(1);
        threshSlider->setMaximum(125);
        threshSlider->setValue(10);
        threshSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(threshSlider);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        msgLabel = new QLabel(centralwidget);
        msgLabel->setObjectName(QString::fromUtf8("msgLabel"));
        msgLabel->setMinimumSize(QSize(300, 40));
        msgLabel->setMaximumSize(QSize(16777215, 60));
        msgLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(msgLabel);


        verticalLayout_2->addLayout(horizontalLayout_5);


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
        scrollAreaWidgetContents->setGeometry(QRect(0, 139, 1159, 364));
        imageScrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(imageScrollArea);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(200, 20));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        weightBox = new QDoubleSpinBox(centralwidget);
        weightBox->setObjectName(QString::fromUtf8("weightBox"));
        weightBox->setMinimumSize(QSize(100, 25));
        weightBox->setMaximumSize(QSize(100, 25));
        weightBox->setMaximum(1000.000000000000000);

        horizontalLayout_4->addWidget(weightBox);


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

        PlaniWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(PlaniWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlaniWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(PlaniWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        PlaniWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionPrevious_Image);
        toolBar->addAction(actionNext_image);
        toolBar->addSeparator();
        toolBar->addAction(actionClear_image);
        toolBar->addSeparator();
        toolBar->addAction(actionExport);

        retranslateUi(PlaniWindow);

        QMetaObject::connectSlotsByName(PlaniWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlaniWindow)
    {
        PlaniWindow->setWindowTitle(QCoreApplication::translate("PlaniWindow", "Planimetrics", nullptr));
        actionSave->setText(QCoreApplication::translate("PlaniWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("PlaniWindow", "Save planimetrics", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("PlaniWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPrevious_Image->setText(QCoreApplication::translate("PlaniWindow", "Previous Image", nullptr));
#if QT_CONFIG(tooltip)
        actionPrevious_Image->setToolTip(QCoreApplication::translate("PlaniWindow", "Display the previous image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPrevious_Image->setShortcut(QCoreApplication::translate("PlaniWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNext_image->setText(QCoreApplication::translate("PlaniWindow", "Next image", nullptr));
#if QT_CONFIG(tooltip)
        actionNext_image->setToolTip(QCoreApplication::translate("PlaniWindow", "Display the mext image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNext_image->setShortcut(QCoreApplication::translate("PlaniWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear_image->setText(QCoreApplication::translate("PlaniWindow", "Clear image", nullptr));
#if QT_CONFIG(tooltip)
        actionClear_image->setToolTip(QCoreApplication::translate("PlaniWindow", "Clear the current segmentation", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClear_image->setShortcut(QCoreApplication::translate("PlaniWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDone->setText(QCoreApplication::translate("PlaniWindow", "Done", nullptr));
#if QT_CONFIG(tooltip)
        actionDone->setToolTip(QCoreApplication::translate("PlaniWindow", "Return to the main window", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExport->setText(QCoreApplication::translate("PlaniWindow", "Export", nullptr));
#if QT_CONFIG(tooltip)
        actionExport->setToolTip(QCoreApplication::translate("PlaniWindow", "Export planimetrics data", nullptr));
#endif // QT_CONFIG(tooltip)
        imageLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("PlaniWindow", "Method:", nullptr));
        label_3->setText(QCoreApplication::translate("PlaniWindow", "Brush Size:", nullptr));
        addremToggle->setText(QCoreApplication::translate("PlaniWindow", "Erase mode (E)", nullptr));
#if QT_CONFIG(shortcut)
        addremToggle->setShortcut(QCoreApplication::translate("PlaniWindow", "E", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton->setText(QCoreApplication::translate("PlaniWindow", "Draw Polygon (A)", nullptr));
#if QT_CONFIG(shortcut)
        pushButton->setShortcut(QCoreApplication::translate("PlaniWindow", "A", nullptr));
#endif // QT_CONFIG(shortcut)
        rectBtn->setText(QCoreApplication::translate("PlaniWindow", "Set ROI (R)", nullptr));
#if QT_CONFIG(shortcut)
        rectBtn->setShortcut(QCoreApplication::translate("PlaniWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        segBtn->setText(QCoreApplication::translate("PlaniWindow", "Segmentation (S)", nullptr));
#if QT_CONFIG(shortcut)
        segBtn->setShortcut(QCoreApplication::translate("PlaniWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        floodBtn->setText(QCoreApplication::translate("PlaniWindow", "Flood Fill (F)", nullptr));
#if QT_CONFIG(shortcut)
        floodBtn->setShortcut(QCoreApplication::translate("PlaniWindow", "F", nullptr));
#endif // QT_CONFIG(shortcut)
        clearBtn->setText(QCoreApplication::translate("PlaniWindow", "Clear Points (C)", nullptr));
#if QT_CONFIG(shortcut)
        clearBtn->setShortcut(QCoreApplication::translate("PlaniWindow", "C", nullptr));
#endif // QT_CONFIG(shortcut)
        helpBtn->setText(QString());
        label_4->setText(QCoreApplication::translate("PlaniWindow", "Threshold: ", nullptr));
        msgLabel->setText(QString());
        label->setText(QCoreApplication::translate("PlaniWindow", "Weight:", nullptr));
        label_8->setText(QCoreApplication::translate("PlaniWindow", "Remaining Images", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("PlaniWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaniWindow: public Ui_PlaniWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANI_H
