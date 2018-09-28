/********************************************************************************
** Form generated from reading UI file 'plani.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANI_H
#define UI_PLANI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            PlaniWindow->setObjectName(QStringLiteral("PlaniWindow"));
        PlaniWindow->setWindowModality(Qt::ApplicationModal);
        PlaniWindow->resize(1250, 870);
        PlaniWindow->setMinimumSize(QSize(1250, 870));
        PlaniWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(PlaniWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionPrevious_Image = new QAction(PlaniWindow);
        actionPrevious_Image->setObjectName(QStringLiteral("actionPrevious_Image"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/VAM/Icons/1462036195_arrow-left1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious_Image->setIcon(icon1);
        actionNext_image = new QAction(PlaniWindow);
        actionNext_image->setObjectName(QStringLiteral("actionNext_image"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/VAM/Icons/1462036198_arrow-right1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_image->setIcon(icon2);
        actionClear_image = new QAction(PlaniWindow);
        actionClear_image->setObjectName(QStringLiteral("actionClear_image"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/VAM/Icons/1462036280_trashcan-delete2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_image->setIcon(icon3);
        actionDone = new QAction(PlaniWindow);
        actionDone->setObjectName(QStringLiteral("actionDone"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon4);
        actionExport = new QAction(PlaniWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon5);
        centralwidget = new QWidget(PlaniWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imageLabel = new CustomLabel(centralwidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(imageLabel, 5, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        methodBox = new QComboBox(centralwidget);
        methodBox->setObjectName(QStringLiteral("methodBox"));
        methodBox->setMinimumSize(QSize(120, 20));
        methodBox->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(methodBox);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        brushBox = new QSpinBox(centralwidget);
        brushBox->setObjectName(QStringLiteral("brushBox"));
        brushBox->setMinimumSize(QSize(60, 25));
        brushBox->setMaximumSize(QSize(60, 35));
        brushBox->setMinimum(1);
        brushBox->setValue(20);

        horizontalLayout->addWidget(brushBox);

        addremToggle = new QRadioButton(centralwidget);
        addremToggle->setObjectName(QStringLiteral("addremToggle"));
        addremToggle->setMinimumSize(QSize(120, 25));
        addremToggle->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(addremToggle);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(120, 25));
        pushButton->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(pushButton);

        rectBtn = new QPushButton(centralwidget);
        rectBtn->setObjectName(QStringLiteral("rectBtn"));
        rectBtn->setMinimumSize(QSize(120, 25));
        rectBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(rectBtn);

        segBtn = new QPushButton(centralwidget);
        segBtn->setObjectName(QStringLiteral("segBtn"));
        segBtn->setMinimumSize(QSize(120, 25));
        segBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(segBtn);

        floodBtn = new QPushButton(centralwidget);
        floodBtn->setObjectName(QStringLiteral("floodBtn"));
        floodBtn->setMinimumSize(QSize(120, 25));
        floodBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(floodBtn);

        clearBtn = new QPushButton(centralwidget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMinimumSize(QSize(120, 25));
        clearBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout->addWidget(clearBtn);

        helpBtn = new QPushButton(centralwidget);
        helpBtn->setObjectName(QStringLiteral("helpBtn"));
        helpBtn->setMinimumSize(QSize(25, 25));
        helpBtn->setMaximumSize(QSize(35, 35));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/VAM/Icons/1462037714_information2.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpBtn->setIcon(icon6);

        horizontalLayout->addWidget(helpBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(120, 20));
        label_4->setMaximumSize(QSize(120, 20));

        horizontalLayout_6->addWidget(label_4);

        threshSlider = new QSlider(centralwidget);
        threshSlider->setObjectName(QStringLiteral("threshSlider"));
        threshSlider->setMinimumSize(QSize(500, 20));
        threshSlider->setMaximumSize(QSize(16777215, 20));
        threshSlider->setMinimum(1);
        threshSlider->setMaximum(125);
        threshSlider->setValue(10);
        threshSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(threshSlider);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        msgLabel = new QLabel(centralwidget);
        msgLabel->setObjectName(QStringLiteral("msgLabel"));
        msgLabel->setMinimumSize(QSize(300, 40));
        msgLabel->setMaximumSize(QSize(16777215, 60));
        msgLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(msgLabel);


        verticalLayout_2->addLayout(horizontalLayout_5);


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
        scrollAreaWidgetContents->setGeometry(QRect(0, 139, 1159, 364));
        imageScrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(imageScrollArea);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(200, 20));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        weightBox = new QDoubleSpinBox(centralwidget);
        weightBox->setObjectName(QStringLiteral("weightBox"));
        weightBox->setMinimumSize(QSize(100, 25));
        weightBox->setMaximumSize(QSize(100, 25));
        weightBox->setMaximum(1000);

        horizontalLayout_4->addWidget(weightBox);


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

        PlaniWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(PlaniWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PlaniWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(PlaniWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
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
        PlaniWindow->setWindowTitle(QApplication::translate("PlaniWindow", "Planimetrics", Q_NULLPTR));
        actionSave->setText(QApplication::translate("PlaniWindow", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("PlaniWindow", "Save planimetrics", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("PlaniWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPrevious_Image->setText(QApplication::translate("PlaniWindow", "Previous Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPrevious_Image->setToolTip(QApplication::translate("PlaniWindow", "Display the previous image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionPrevious_Image->setShortcut(QApplication::translate("PlaniWindow", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNext_image->setText(QApplication::translate("PlaniWindow", "Next image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNext_image->setToolTip(QApplication::translate("PlaniWindow", "Display the mext image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNext_image->setShortcut(QApplication::translate("PlaniWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClear_image->setText(QApplication::translate("PlaniWindow", "Clear image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClear_image->setToolTip(QApplication::translate("PlaniWindow", "Clear the current segmentation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionClear_image->setShortcut(QApplication::translate("PlaniWindow", "Ctrl+D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDone->setText(QApplication::translate("PlaniWindow", "Done", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDone->setToolTip(QApplication::translate("PlaniWindow", "Return to the main window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionExport->setText(QApplication::translate("PlaniWindow", "Export", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("PlaniWindow", "Export planimetrics data", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        imageLabel->setText(QString());
        label_2->setText(QApplication::translate("PlaniWindow", "Method:", Q_NULLPTR));
        label_3->setText(QApplication::translate("PlaniWindow", "Brush Size:", Q_NULLPTR));
        addremToggle->setText(QApplication::translate("PlaniWindow", "Erase mode (E)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addremToggle->setShortcut(QApplication::translate("PlaniWindow", "E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton->setText(QApplication::translate("PlaniWindow", "Draw Polygon (A)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton->setShortcut(QApplication::translate("PlaniWindow", "A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        rectBtn->setText(QApplication::translate("PlaniWindow", "Set ROI (R)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        rectBtn->setShortcut(QApplication::translate("PlaniWindow", "R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        segBtn->setText(QApplication::translate("PlaniWindow", "Segmentation (S)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        segBtn->setShortcut(QApplication::translate("PlaniWindow", "S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        floodBtn->setText(QApplication::translate("PlaniWindow", "Flood Fill (F)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        floodBtn->setShortcut(QApplication::translate("PlaniWindow", "F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        clearBtn->setText(QApplication::translate("PlaniWindow", "Clear Points (C)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        clearBtn->setShortcut(QApplication::translate("PlaniWindow", "C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        helpBtn->setText(QString());
        label_4->setText(QApplication::translate("PlaniWindow", "Threshold: ", Q_NULLPTR));
        msgLabel->setText(QString());
        label->setText(QApplication::translate("PlaniWindow", "Weight:", Q_NULLPTR));
        label_8->setText(QApplication::translate("PlaniWindow", "Remaining Images", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("PlaniWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlaniWindow: public Ui_PlaniWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANI_H
