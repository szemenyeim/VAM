/********************************************************************************
** Form generated from reading UI file 'vam.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VAM_H
#define UI_VAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VAMClass
{
public:
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionSave_As;
    QAction *actionNew_Project;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionSelect_Language;
    QAction *actionEnable_Logging;
    QAction *actionSet_Project_Directory;
    QAction *actionOrder_Images_by_Animal_ID;
    QAction *actionPlanimetrics_export;
    QAction *actionMorphometrics_export;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *projNameLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *videoLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *vidLabel1;
    QPushButton *vidEdit1;
    QPushButton *calibBtn1;
    QListView *vidList1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *vidLabel2;
    QPushButton *vidEdit2;
    QPushButton *calibBtn2;
    QListView *vidList2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *vidLabel3;
    QPushButton *vidEdit3;
    QPushButton *calibBtn3;
    QListView *vidList3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *vidLabel4;
    QPushButton *vidEdit4;
    QPushButton *calibBtn4;
    QListView *vidList4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *stillLabel;
    QLabel *label_8;
    QPushButton *stillCreate;
    QPushButton *stillDelete;
    QPushButton *resetDB;
    QLabel *stillCntLabel;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *img1;
    QLabel *img3;
    QVBoxLayout *verticalLayout_8;
    QLabel *img2;
    QLabel *img4;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *schemaLabel;
    QLabel *label_4;
    QComboBox *schemaCombo;
    QPushButton *schemaAdd;
    QPushButton *schemaOpen;
    QPushButton *schemaEdit;
    QPushButton *schemaRemove;
    QHBoxLayout *horizontalLayout_6;
    QLabel *measLabel;
    QLabel *label_7;
    QComboBox *measCombo;
    QPushButton *measAdd;
    QPushButton *measOpen;
    QPushButton *measEdit;
    QPushButton *measRemove;
    QHBoxLayout *horizontalLayout_3;
    QLabel *outLabel;
    QLabel *label_6;
    QComboBox *formatCombo;
    QPushButton *generateOutput;
    QProgressBar *progressBar;
    QLabel *outNameLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen_Recent;
    QMenu *menuSettings;
    QMenu *menuAdvanced;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VAMClass)
    {
        if (VAMClass->objectName().isEmpty())
            VAMClass->setObjectName(QStringLiteral("VAMClass"));
        VAMClass->resize(750, 750);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VAMClass->sizePolicy().hasHeightForWidth());
        VAMClass->setSizePolicy(sizePolicy);
        VAMClass->setMinimumSize(QSize(750, 750));
        VAMClass->setMaximumSize(QSize(1920, 1080));
        actionOpen_Project = new QAction(VAMClass);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/VAM/Icons/1462036211_folder-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Project->setIcon(icon);
        actionSave_Project = new QAction(VAMClass);
        actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/VAM/Icons/1462036171_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project->setIcon(icon1);
        actionSave_As = new QAction(VAMClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_As->setIcon(icon2);
        actionNew_Project = new QAction(VAMClass);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Project->setIcon(icon3);
        actionExit = new QAction(VAMClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/VAM/Icons/1462037720_bullet-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionAbout = new QAction(VAMClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/VAM/Icons/1462037714_information2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionSelect_Language = new QAction(VAMClass);
        actionSelect_Language->setObjectName(QStringLiteral("actionSelect_Language"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/VAM/Icons/1462037723_user_male_info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_Language->setIcon(icon6);
        actionEnable_Logging = new QAction(VAMClass);
        actionEnable_Logging->setObjectName(QStringLiteral("actionEnable_Logging"));
        actionEnable_Logging->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/VAM/Icons/1462790393_comment2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QStringLiteral(":/VAM/Icons/1462790420_comment2-delete2.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QStringLiteral("Icons/1462790393_comment2.png"), QSize(), QIcon::Active, QIcon::Off);
        icon7.addFile(QStringLiteral("Icons/1462790393_comment2.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon7.addFile(QStringLiteral("Icons/1462790420_comment2-delete2.png"), QSize(), QIcon::Selected, QIcon::On);
        actionEnable_Logging->setIcon(icon7);
        actionSet_Project_Directory = new QAction(VAMClass);
        actionSet_Project_Directory->setObjectName(QStringLiteral("actionSet_Project_Directory"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/VAM/Icons/1462364448_folder_open-edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Project_Directory->setIcon(icon8);
        actionOrder_Images_by_Animal_ID = new QAction(VAMClass);
        actionOrder_Images_by_Animal_ID->setObjectName(QStringLiteral("actionOrder_Images_by_Animal_ID"));
        actionOrder_Images_by_Animal_ID->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/VAM/Icons/1466084143_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QStringLiteral(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::On);
        actionOrder_Images_by_Animal_ID->setIcon(icon9);
        actionPlanimetrics_export = new QAction(VAMClass);
        actionPlanimetrics_export->setObjectName(QStringLiteral("actionPlanimetrics_export"));
        actionMorphometrics_export = new QAction(VAMClass);
        actionMorphometrics_export->setObjectName(QStringLiteral("actionMorphometrics_export"));
        centralWidget = new QWidget(VAMClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        projNameLabel = new QLabel(centralWidget);
        projNameLabel->setObjectName(QStringLiteral("projNameLabel"));
        projNameLabel->setMaximumSize(QSize(16777215, 30));
        projNameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(projNameLabel);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        videoLabel = new QLabel(centralWidget);
        videoLabel->setObjectName(QStringLiteral("videoLabel"));
        videoLabel->setMaximumSize(QSize(40, 40));
        videoLabel->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png")));

        horizontalLayout_4->addWidget(videoLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        vidLabel1 = new QLabel(centralWidget);
        vidLabel1->setObjectName(QStringLiteral("vidLabel1"));
        vidLabel1->setMaximumSize(QSize(16777215, 20));
        vidLabel1->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(vidLabel1);

        vidEdit1 = new QPushButton(centralWidget);
        vidEdit1->setObjectName(QStringLiteral("vidEdit1"));
        vidEdit1->setMaximumSize(QSize(30, 30));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        vidEdit1->setIcon(icon10);

        horizontalLayout_8->addWidget(vidEdit1);

        calibBtn1 = new QPushButton(centralWidget);
        calibBtn1->setObjectName(QStringLiteral("calibBtn1"));
        calibBtn1->setMinimumSize(QSize(30, 30));
        calibBtn1->setMaximumSize(QSize(30, 30));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        calibBtn1->setIcon(icon11);

        horizontalLayout_8->addWidget(calibBtn1);


        verticalLayout->addLayout(horizontalLayout_8);

        vidList1 = new QListView(centralWidget);
        vidList1->setObjectName(QStringLiteral("vidList1"));
        vidList1->setMaximumSize(QSize(400, 100));

        verticalLayout->addWidget(vidList1);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        vidLabel2 = new QLabel(centralWidget);
        vidLabel2->setObjectName(QStringLiteral("vidLabel2"));
        vidLabel2->setMaximumSize(QSize(16777215, 20));
        vidLabel2->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(vidLabel2);

        vidEdit2 = new QPushButton(centralWidget);
        vidEdit2->setObjectName(QStringLiteral("vidEdit2"));
        vidEdit2->setMaximumSize(QSize(30, 30));
        vidEdit2->setIcon(icon10);

        horizontalLayout_9->addWidget(vidEdit2);

        calibBtn2 = new QPushButton(centralWidget);
        calibBtn2->setObjectName(QStringLiteral("calibBtn2"));
        calibBtn2->setMinimumSize(QSize(30, 30));
        calibBtn2->setMaximumSize(QSize(30, 30));
        calibBtn2->setIcon(icon11);

        horizontalLayout_9->addWidget(calibBtn2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        vidList2 = new QListView(centralWidget);
        vidList2->setObjectName(QStringLiteral("vidList2"));
        vidList2->setMaximumSize(QSize(400, 100));

        verticalLayout_3->addWidget(vidList2);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        vidLabel3 = new QLabel(centralWidget);
        vidLabel3->setObjectName(QStringLiteral("vidLabel3"));
        vidLabel3->setMaximumSize(QSize(16777215, 20));
        vidLabel3->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(vidLabel3);

        vidEdit3 = new QPushButton(centralWidget);
        vidEdit3->setObjectName(QStringLiteral("vidEdit3"));
        vidEdit3->setMaximumSize(QSize(30, 30));
        vidEdit3->setIcon(icon10);

        horizontalLayout_10->addWidget(vidEdit3);

        calibBtn3 = new QPushButton(centralWidget);
        calibBtn3->setObjectName(QStringLiteral("calibBtn3"));
        calibBtn3->setMinimumSize(QSize(30, 30));
        calibBtn3->setMaximumSize(QSize(30, 30));
        calibBtn3->setIcon(icon11);

        horizontalLayout_10->addWidget(calibBtn3);


        verticalLayout_4->addLayout(horizontalLayout_10);

        vidList3 = new QListView(centralWidget);
        vidList3->setObjectName(QStringLiteral("vidList3"));
        vidList3->setMaximumSize(QSize(400, 100));

        verticalLayout_4->addWidget(vidList3);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        vidLabel4 = new QLabel(centralWidget);
        vidLabel4->setObjectName(QStringLiteral("vidLabel4"));
        vidLabel4->setMaximumSize(QSize(16777215, 20));
        vidLabel4->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(vidLabel4);

        vidEdit4 = new QPushButton(centralWidget);
        vidEdit4->setObjectName(QStringLiteral("vidEdit4"));
        vidEdit4->setMaximumSize(QSize(30, 30));
        vidEdit4->setIcon(icon10);

        horizontalLayout_11->addWidget(vidEdit4);

        calibBtn4 = new QPushButton(centralWidget);
        calibBtn4->setObjectName(QStringLiteral("calibBtn4"));
        calibBtn4->setMinimumSize(QSize(30, 30));
        calibBtn4->setMaximumSize(QSize(30, 30));
        calibBtn4->setIcon(icon11);

        horizontalLayout_11->addWidget(calibBtn4);


        verticalLayout_6->addLayout(horizontalLayout_11);

        vidList4 = new QListView(centralWidget);
        vidList4->setObjectName(QStringLiteral("vidList4"));
        vidList4->setMaximumSize(QSize(400, 100));

        verticalLayout_6->addWidget(vidList4);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        stillLabel = new QLabel(centralWidget);
        stillLabel->setObjectName(QStringLiteral("stillLabel"));
        stillLabel->setMinimumSize(QSize(0, 0));
        stillLabel->setMaximumSize(QSize(40, 40));
        stillLabel->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png")));

        horizontalLayout_2->addWidget(stillLabel);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(16777215, 40));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_8);

        stillCreate = new QPushButton(centralWidget);
        stillCreate->setObjectName(QStringLiteral("stillCreate"));
        stillCreate->setMaximumSize(QSize(150, 25));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/VAM/Icons/1462024260_Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        stillCreate->setIcon(icon12);

        horizontalLayout_2->addWidget(stillCreate);

        stillDelete = new QPushButton(centralWidget);
        stillDelete->setObjectName(QStringLiteral("stillDelete"));
        stillDelete->setMaximumSize(QSize(150, 25));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        stillDelete->setIcon(icon13);

        horizontalLayout_2->addWidget(stillDelete);

        resetDB = new QPushButton(centralWidget);
        resetDB->setObjectName(QStringLiteral("resetDB"));
        resetDB->setMaximumSize(QSize(150, 25));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/VAM/Icons/1462036280_trashcan-delete2.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetDB->setIcon(icon14);

        horizontalLayout_2->addWidget(resetDB);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stillCntLabel = new QLabel(centralWidget);
        stillCntLabel->setObjectName(QStringLiteral("stillCntLabel"));
        stillCntLabel->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(stillCntLabel);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        img1 = new QLabel(centralWidget);
        img1->setObjectName(QStringLiteral("img1"));
        img1->setMinimumSize(QSize(180, 120));
        img1->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(img1);

        img3 = new QLabel(centralWidget);
        img3->setObjectName(QStringLiteral("img3"));
        img3->setMinimumSize(QSize(180, 120));
        img3->setMaximumSize(QSize(16777215, 16777215));
        img3->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(img3);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        img2 = new QLabel(centralWidget);
        img2->setObjectName(QStringLiteral("img2"));
        img2->setMinimumSize(QSize(180, 120));
        img2->setMaximumSize(QSize(16777215, 16777215));
        img2->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(img2);

        img4 = new QLabel(centralWidget);
        img4->setObjectName(QStringLiteral("img4"));
        img4->setMinimumSize(QSize(180, 120));
        img4->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(img4);


        horizontalLayout_7->addLayout(verticalLayout_8);


        verticalLayout_2->addLayout(horizontalLayout_7);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

        verticalLayout_2->addLayout(gridLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        schemaLabel = new QLabel(centralWidget);
        schemaLabel->setObjectName(QStringLiteral("schemaLabel"));
        schemaLabel->setMaximumSize(QSize(40, 40));
        schemaLabel->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png")));

        horizontalLayout_5->addWidget(schemaLabel);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_4);

        schemaCombo = new QComboBox(centralWidget);
        schemaCombo->setObjectName(QStringLiteral("schemaCombo"));
        schemaCombo->setMaximumSize(QSize(150, 25));

        horizontalLayout_5->addWidget(schemaCombo);

        schemaAdd = new QPushButton(centralWidget);
        schemaAdd->setObjectName(QStringLiteral("schemaAdd"));
        schemaAdd->setMaximumSize(QSize(150, 25));
        schemaAdd->setIcon(icon3);

        horizontalLayout_5->addWidget(schemaAdd);

        schemaOpen = new QPushButton(centralWidget);
        schemaOpen->setObjectName(QStringLiteral("schemaOpen"));
        schemaOpen->setMaximumSize(QSize(150, 25));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/VAM/Icons/1462367694_folder_open-add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        schemaOpen->setIcon(icon15);

        horizontalLayout_5->addWidget(schemaOpen);

        schemaEdit = new QPushButton(centralWidget);
        schemaEdit->setObjectName(QStringLiteral("schemaEdit"));
        schemaEdit->setMaximumSize(QSize(150, 25));
        schemaEdit->setIcon(icon10);

        horizontalLayout_5->addWidget(schemaEdit);

        schemaRemove = new QPushButton(centralWidget);
        schemaRemove->setObjectName(QStringLiteral("schemaRemove"));
        schemaRemove->setMaximumSize(QSize(150, 25));
        schemaRemove->setIcon(icon13);

        horizontalLayout_5->addWidget(schemaRemove);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        measLabel = new QLabel(centralWidget);
        measLabel->setObjectName(QStringLiteral("measLabel"));
        measLabel->setMaximumSize(QSize(40, 40));
        measLabel->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png")));

        horizontalLayout_6->addWidget(measLabel);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_7);

        measCombo = new QComboBox(centralWidget);
        measCombo->setObjectName(QStringLiteral("measCombo"));
        measCombo->setMaximumSize(QSize(150, 25));

        horizontalLayout_6->addWidget(measCombo);

        measAdd = new QPushButton(centralWidget);
        measAdd->setObjectName(QStringLiteral("measAdd"));
        measAdd->setMaximumSize(QSize(150, 25));
        measAdd->setIcon(icon3);

        horizontalLayout_6->addWidget(measAdd);

        measOpen = new QPushButton(centralWidget);
        measOpen->setObjectName(QStringLiteral("measOpen"));
        measOpen->setMaximumSize(QSize(150, 25));
        measOpen->setIcon(icon15);

        horizontalLayout_6->addWidget(measOpen);

        measEdit = new QPushButton(centralWidget);
        measEdit->setObjectName(QStringLiteral("measEdit"));
        measEdit->setMaximumSize(QSize(150, 25));
        measEdit->setIcon(icon10);

        horizontalLayout_6->addWidget(measEdit);

        measRemove = new QPushButton(centralWidget);
        measRemove->setObjectName(QStringLiteral("measRemove"));
        measRemove->setMaximumSize(QSize(150, 25));
        measRemove->setIcon(icon13);

        horizontalLayout_6->addWidget(measRemove);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        outLabel = new QLabel(centralWidget);
        outLabel->setObjectName(QStringLiteral("outLabel"));
        outLabel->setMaximumSize(QSize(40, 40));
        outLabel->setPixmap(QPixmap(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png")));

        horizontalLayout_3->addWidget(outLabel);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(16777215, 30));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_6);

        formatCombo = new QComboBox(centralWidget);
        formatCombo->setObjectName(QStringLiteral("formatCombo"));
        formatCombo->setMaximumSize(QSize(75, 25));

        horizontalLayout_3->addWidget(formatCombo);

        generateOutput = new QPushButton(centralWidget);
        generateOutput->setObjectName(QStringLiteral("generateOutput"));
        generateOutput->setMaximumSize(QSize(150, 25));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        generateOutput->setIcon(icon16);

        horizontalLayout_3->addWidget(generateOutput);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximumSize(QSize(300, 25));
        progressBar->setValue(0);

        horizontalLayout_3->addWidget(progressBar);


        verticalLayout_2->addLayout(horizontalLayout_3);

        outNameLabel = new QLabel(centralWidget);
        outNameLabel->setObjectName(QStringLiteral("outNameLabel"));
        outNameLabel->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(outNameLabel);


        verticalLayout_5->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        VAMClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VAMClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOpen_Recent = new QMenu(menuFile);
        menuOpen_Recent->setObjectName(QStringLiteral("menuOpen_Recent"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAdvanced = new QMenu(menuBar);
        menuAdvanced->setObjectName(QStringLiteral("menuAdvanced"));
        VAMClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VAMClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        VAMClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VAMClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VAMClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuAdvanced->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(menuOpen_Recent->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOpen_Recent->addSeparator();
        menuSettings->addAction(actionAbout);
        menuSettings->addSeparator();
        menuSettings->addAction(actionSelect_Language);
        menuSettings->addAction(actionEnable_Logging);
        menuSettings->addAction(actionSet_Project_Directory);
        menuSettings->addAction(actionOrder_Images_by_Animal_ID);
        menuAdvanced->addAction(actionPlanimetrics_export);
        menuAdvanced->addAction(actionMorphometrics_export);
        mainToolBar->addAction(actionNew_Project);
        mainToolBar->addAction(actionOpen_Project);
        mainToolBar->addAction(actionSave_Project);
        mainToolBar->addAction(actionSave_As);
        mainToolBar->addSeparator();

        retranslateUi(VAMClass);

        QMetaObject::connectSlotsByName(VAMClass);
    } // setupUi

    void retranslateUi(QMainWindow *VAMClass)
    {
        VAMClass->setWindowTitle(QApplication::translate("VAMClass", "VAM (Video Assisted Measurement)", Q_NULLPTR));
        actionOpen_Project->setText(QApplication::translate("VAMClass", "Open Project", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen_Project->setShortcut(QApplication::translate("VAMClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_Project->setText(QApplication::translate("VAMClass", "Save Project", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave_Project->setShortcut(QApplication::translate("VAMClass", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_As->setText(QApplication::translate("VAMClass", "Save As...", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave_As->setShortcut(QApplication::translate("VAMClass", "Ctrl+Shift+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNew_Project->setText(QApplication::translate("VAMClass", "New Project", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNew_Project->setShortcut(QApplication::translate("VAMClass", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("VAMClass", "Exit", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("VAMClass", "About", Q_NULLPTR));
        actionSelect_Language->setText(QApplication::translate("VAMClass", "Select Language", Q_NULLPTR));
        actionEnable_Logging->setText(QApplication::translate("VAMClass", "Enable Logging", Q_NULLPTR));
        actionSet_Project_Directory->setText(QApplication::translate("VAMClass", "Set Project Directory", Q_NULLPTR));
        actionOrder_Images_by_Animal_ID->setText(QApplication::translate("VAMClass", "Order Images by Animal ID", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOrder_Images_by_Animal_ID->setToolTip(QApplication::translate("VAMClass", "<html><head/><body><p>When marking images, the images are ordered by animal ID.</p><p>If turned off, all side images are marked first, then upper images.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionPlanimetrics_export->setText(QApplication::translate("VAMClass", "Planimetrics export", Q_NULLPTR));
        actionMorphometrics_export->setText(QApplication::translate("VAMClass", "Morphometrics export", Q_NULLPTR));
        projNameLabel->setText(QString());
        videoLabel->setText(QString());
        vidLabel1->setText(QApplication::translate("VAMClass", "Videos #1", Q_NULLPTR));
        vidEdit1->setText(QString());
        calibBtn1->setText(QString());
        vidLabel2->setText(QApplication::translate("VAMClass", "Videos #2", Q_NULLPTR));
        vidEdit2->setText(QString());
        calibBtn2->setText(QString());
        vidLabel3->setText(QApplication::translate("VAMClass", "Videos #3", Q_NULLPTR));
        vidEdit3->setText(QString());
        calibBtn3->setText(QString());
        vidLabel4->setText(QApplication::translate("VAMClass", "Videos #4", Q_NULLPTR));
        vidEdit4->setText(QString());
        calibBtn4->setText(QString());
        stillLabel->setText(QString());
        label_8->setText(QApplication::translate("VAMClass", "Still Image Creation", Q_NULLPTR));
        stillCreate->setText(QApplication::translate("VAMClass", "Create Stills", Q_NULLPTR));
        stillDelete->setText(QApplication::translate("VAMClass", "Clear Stills", Q_NULLPTR));
        resetDB->setText(QApplication::translate("VAMClass", "Reset Database", Q_NULLPTR));
        stillCntLabel->setText(QString());
        img1->setText(QString());
        img3->setText(QString());
        img2->setText(QString());
        img4->setText(QString());
        schemaLabel->setText(QString());
        label_4->setText(QApplication::translate("VAMClass", "Schemas", Q_NULLPTR));
        schemaAdd->setText(QApplication::translate("VAMClass", "New", Q_NULLPTR));
        schemaOpen->setText(QApplication::translate("VAMClass", "Import", Q_NULLPTR));
        schemaEdit->setText(QApplication::translate("VAMClass", "Edit", Q_NULLPTR));
        schemaRemove->setText(QApplication::translate("VAMClass", "Remove", Q_NULLPTR));
        measLabel->setText(QString());
        label_7->setText(QApplication::translate("VAMClass", "Events", Q_NULLPTR));
        measAdd->setText(QApplication::translate("VAMClass", "New", Q_NULLPTR));
        measOpen->setText(QApplication::translate("VAMClass", "Import", Q_NULLPTR));
        measEdit->setText(QApplication::translate("VAMClass", "Edit", Q_NULLPTR));
        measRemove->setText(QApplication::translate("VAMClass", "Remove", Q_NULLPTR));
        outLabel->setText(QString());
        label_6->setText(QApplication::translate("VAMClass", "Output file format", Q_NULLPTR));
        formatCombo->clear();
        formatCombo->insertItems(0, QStringList()
         << QApplication::translate("VAMClass", "XLSX", Q_NULLPTR)
         << QApplication::translate("VAMClass", "HTML", Q_NULLPTR)
         << QApplication::translate("VAMClass", "CSV", Q_NULLPTR)
        );
        formatCombo->setCurrentText(QApplication::translate("VAMClass", "XLSX", Q_NULLPTR));
        generateOutput->setText(QApplication::translate("VAMClass", "Generate Output", Q_NULLPTR));
        outNameLabel->setText(QString());
        menuFile->setTitle(QApplication::translate("VAMClass", "File", Q_NULLPTR));
        menuOpen_Recent->setTitle(QApplication::translate("VAMClass", "Open Recent", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("VAMClass", "Settings", Q_NULLPTR));
        menuAdvanced->setTitle(QApplication::translate("VAMClass", "Advanced", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VAMClass: public Ui_VAMClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VAM_H
