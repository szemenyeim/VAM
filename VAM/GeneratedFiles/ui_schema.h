/********************************************************************************
** Form generated from reading UI file 'schema.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEMA_H
#define UI_SCHEMA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomLabel.h"

QT_BEGIN_NAMESPACE

class Ui_SchemaWindow
{
public:
    QAction *actionOpen_Images;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionSet_Correction_Measurement;
    QAction *actionDone;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *il1;
    CustomLabel *imageLabel1;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *pl1;
    QListView *pointView1;
    QHBoxLayout *horizontalLayout;
    QPushButton *newPointButton1;
    QPushButton *renamePointButton1;
    QPushButton *removePointButton1;
    QVBoxLayout *verticalLayout_2;
    QLabel *ml1;
    QListView *measView1;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *newMeasButton1;
    QPushButton *renameMeasButton1;
    QPushButton *removeMeasButton1;
    QVBoxLayout *verticalLayout_6;
    QLabel *il2;
    CustomLabel *imageLabel2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *pl2;
    QListView *pointView2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *newPointButton2;
    QPushButton *renamePointButton2;
    QPushButton *removePointButton2;
    QVBoxLayout *verticalLayout_4;
    QLabel *ml2;
    QListView *measView2;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *newMeasButton2;
    QPushButton *renameMeasButton2;
    QPushButton *removeMeasButton2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QLabel *il3;
    CustomLabel *imageLabel3;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QLabel *pl3;
    QListView *pointView3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *newPointButton3;
    QPushButton *renamePointButton3;
    QPushButton *removePointButton3;
    QVBoxLayout *verticalLayout_9;
    QLabel *ml3;
    QListView *measView3;
    QHBoxLayout *horizontalLayout_11;
    QToolButton *newMeasButton3;
    QPushButton *renameMeasButton3;
    QPushButton *removeMeasButton3;
    QVBoxLayout *verticalLayout_10;
    QLabel *il4;
    CustomLabel *imageLabel4;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QLabel *pl4;
    QListView *pointView4;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *newPointButton4;
    QPushButton *renamePointButton4;
    QPushButton *removePointButton4;
    QVBoxLayout *verticalLayout_12;
    QLabel *ml4;
    QListView *measView4;
    QHBoxLayout *horizontalLayout_14;
    QToolButton *newMeasButton4;
    QPushButton *renameMeasButton4;
    QPushButton *removeMeasButton4;
    QLabel *infoLabel;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SchemaWindow)
    {
        if (SchemaWindow->objectName().isEmpty())
            SchemaWindow->setObjectName(QString::fromUtf8("SchemaWindow"));
        SchemaWindow->resize(845, 765);
        SchemaWindow->setMinimumSize(QSize(845, 765));
        SchemaWindow->setMaximumSize(QSize(1920, 1080));
        actionOpen_Images = new QAction(SchemaWindow);
        actionOpen_Images->setObjectName(QString::fromUtf8("actionOpen_Images"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462024271_New_image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Images->setIcon(icon);
        actionSave = new QAction(SchemaWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave_as = new QAction(SchemaWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1462036242_save_add2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon2);
        actionSet_Correction_Measurement = new QAction(SchemaWindow);
        actionSet_Correction_Measurement->setObjectName(QString::fromUtf8("actionSet_Correction_Measurement"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Correction_Measurement->setIcon(icon3);
        actionDone = new QAction(SchemaWindow);
        actionDone->setObjectName(QString::fromUtf8("actionDone"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon4);
        centralwidget = new QWidget(SchemaWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        il1 = new QLabel(centralwidget);
        il1->setObjectName(QString::fromUtf8("il1"));
        il1->setMaximumSize(QSize(16777215, 20));
        il1->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(il1);

        imageLabel1 = new CustomLabel(centralwidget);
        imageLabel1->setObjectName(QString::fromUtf8("imageLabel1"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageLabel1->sizePolicy().hasHeightForWidth());
        imageLabel1->setSizePolicy(sizePolicy);
        imageLabel1->setMinimumSize(QSize(400, 180));
        imageLabel1->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(imageLabel1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pl1 = new QLabel(centralwidget);
        pl1->setObjectName(QString::fromUtf8("pl1"));
        pl1->setMaximumSize(QSize(16777215, 20));
        pl1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(pl1);

        pointView1 = new QListView(centralwidget);
        pointView1->setObjectName(QString::fromUtf8("pointView1"));
        pointView1->setMaximumSize(QSize(16777215, 250));
        pointView1->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(pointView1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        newPointButton1 = new QPushButton(centralwidget);
        newPointButton1->setObjectName(QString::fromUtf8("newPointButton1"));
        newPointButton1->setMaximumSize(QSize(75, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        newPointButton1->setIcon(icon5);

        horizontalLayout->addWidget(newPointButton1);

        renamePointButton1 = new QPushButton(centralwidget);
        renamePointButton1->setObjectName(QString::fromUtf8("renamePointButton1"));
        renamePointButton1->setMaximumSize(QSize(75, 30));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VAM/Icons/1462036358_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        renamePointButton1->setIcon(icon6);

        horizontalLayout->addWidget(renamePointButton1);

        removePointButton1 = new QPushButton(centralwidget);
        removePointButton1->setObjectName(QString::fromUtf8("removePointButton1"));
        removePointButton1->setMaximumSize(QSize(75, 30));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        removePointButton1->setIcon(icon7);

        horizontalLayout->addWidget(removePointButton1);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ml1 = new QLabel(centralwidget);
        ml1->setObjectName(QString::fromUtf8("ml1"));
        ml1->setMaximumSize(QSize(16777215, 20));
        ml1->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(ml1);

        measView1 = new QListView(centralwidget);
        measView1->setObjectName(QString::fromUtf8("measView1"));
        measView1->setMaximumSize(QSize(16777215, 250));
        measView1->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_2->addWidget(measView1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        newMeasButton1 = new QToolButton(centralwidget);
        newMeasButton1->setObjectName(QString::fromUtf8("newMeasButton1"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(newMeasButton1->sizePolicy().hasHeightForWidth());
        newMeasButton1->setSizePolicy(sizePolicy1);
        newMeasButton1->setMaximumSize(QSize(75, 30));
        newMeasButton1->setIcon(icon5);

        horizontalLayout_2->addWidget(newMeasButton1);

        renameMeasButton1 = new QPushButton(centralwidget);
        renameMeasButton1->setObjectName(QString::fromUtf8("renameMeasButton1"));
        renameMeasButton1->setMaximumSize(QSize(75, 30));
        renameMeasButton1->setIcon(icon6);

        horizontalLayout_2->addWidget(renameMeasButton1);

        removeMeasButton1 = new QPushButton(centralwidget);
        removeMeasButton1->setObjectName(QString::fromUtf8("removeMeasButton1"));
        removeMeasButton1->setMaximumSize(QSize(75, 30));
        removeMeasButton1->setAcceptDrops(false);
        removeMeasButton1->setIcon(icon7);

        horizontalLayout_2->addWidget(removeMeasButton1);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        il2 = new QLabel(centralwidget);
        il2->setObjectName(QString::fromUtf8("il2"));
        il2->setMaximumSize(QSize(16777215, 20));
        il2->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(il2);

        imageLabel2 = new CustomLabel(centralwidget);
        imageLabel2->setObjectName(QString::fromUtf8("imageLabel2"));
        sizePolicy.setHeightForWidth(imageLabel2->sizePolicy().hasHeightForWidth());
        imageLabel2->setSizePolicy(sizePolicy);
        imageLabel2->setMinimumSize(QSize(400, 180));
        imageLabel2->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(imageLabel2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pl2 = new QLabel(centralwidget);
        pl2->setObjectName(QString::fromUtf8("pl2"));
        pl2->setMaximumSize(QSize(16777215, 20));
        pl2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(pl2);

        pointView2 = new QListView(centralwidget);
        pointView2->setObjectName(QString::fromUtf8("pointView2"));
        pointView2->setMaximumSize(QSize(16777215, 250));
        pointView2->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(pointView2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        newPointButton2 = new QPushButton(centralwidget);
        newPointButton2->setObjectName(QString::fromUtf8("newPointButton2"));
        newPointButton2->setMaximumSize(QSize(75, 30));
        newPointButton2->setIcon(icon5);

        horizontalLayout_3->addWidget(newPointButton2);

        renamePointButton2 = new QPushButton(centralwidget);
        renamePointButton2->setObjectName(QString::fromUtf8("renamePointButton2"));
        renamePointButton2->setMaximumSize(QSize(75, 30));
        renamePointButton2->setIcon(icon6);

        horizontalLayout_3->addWidget(renamePointButton2);

        removePointButton2 = new QPushButton(centralwidget);
        removePointButton2->setObjectName(QString::fromUtf8("removePointButton2"));
        removePointButton2->setMaximumSize(QSize(75, 30));
        removePointButton2->setIcon(icon7);

        horizontalLayout_3->addWidget(removePointButton2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ml2 = new QLabel(centralwidget);
        ml2->setObjectName(QString::fromUtf8("ml2"));
        ml2->setMaximumSize(QSize(16777215, 20));
        ml2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(ml2);

        measView2 = new QListView(centralwidget);
        measView2->setObjectName(QString::fromUtf8("measView2"));
        measView2->setMaximumSize(QSize(16777215, 250));
        measView2->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_4->addWidget(measView2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        newMeasButton2 = new QToolButton(centralwidget);
        newMeasButton2->setObjectName(QString::fromUtf8("newMeasButton2"));
        sizePolicy1.setHeightForWidth(newMeasButton2->sizePolicy().hasHeightForWidth());
        newMeasButton2->setSizePolicy(sizePolicy1);
        newMeasButton2->setMaximumSize(QSize(75, 30));
        newMeasButton2->setIcon(icon5);

        horizontalLayout_4->addWidget(newMeasButton2);

        renameMeasButton2 = new QPushButton(centralwidget);
        renameMeasButton2->setObjectName(QString::fromUtf8("renameMeasButton2"));
        renameMeasButton2->setMaximumSize(QSize(75, 30));
        renameMeasButton2->setIcon(icon6);

        horizontalLayout_4->addWidget(renameMeasButton2);

        removeMeasButton2 = new QPushButton(centralwidget);
        removeMeasButton2->setObjectName(QString::fromUtf8("removeMeasButton2"));
        removeMeasButton2->setMaximumSize(QSize(75, 30));
        removeMeasButton2->setIcon(icon7);

        horizontalLayout_4->addWidget(removeMeasButton2);


        verticalLayout_4->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_6);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        il3 = new QLabel(centralwidget);
        il3->setObjectName(QString::fromUtf8("il3"));
        il3->setMaximumSize(QSize(16777215, 20));
        il3->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(il3);

        imageLabel3 = new CustomLabel(centralwidget);
        imageLabel3->setObjectName(QString::fromUtf8("imageLabel3"));
        sizePolicy.setHeightForWidth(imageLabel3->sizePolicy().hasHeightForWidth());
        imageLabel3->setSizePolicy(sizePolicy);
        imageLabel3->setMinimumSize(QSize(400, 180));
        imageLabel3->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(imageLabel3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pl3 = new QLabel(centralwidget);
        pl3->setObjectName(QString::fromUtf8("pl3"));
        pl3->setMaximumSize(QSize(16777215, 20));
        pl3->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(pl3);

        pointView3 = new QListView(centralwidget);
        pointView3->setObjectName(QString::fromUtf8("pointView3"));
        pointView3->setMaximumSize(QSize(16777215, 250));
        pointView3->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_8->addWidget(pointView3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        newPointButton3 = new QPushButton(centralwidget);
        newPointButton3->setObjectName(QString::fromUtf8("newPointButton3"));
        newPointButton3->setMaximumSize(QSize(75, 30));
        newPointButton3->setIcon(icon5);

        horizontalLayout_10->addWidget(newPointButton3);

        renamePointButton3 = new QPushButton(centralwidget);
        renamePointButton3->setObjectName(QString::fromUtf8("renamePointButton3"));
        renamePointButton3->setMaximumSize(QSize(75, 30));
        renamePointButton3->setIcon(icon6);

        horizontalLayout_10->addWidget(renamePointButton3);

        removePointButton3 = new QPushButton(centralwidget);
        removePointButton3->setObjectName(QString::fromUtf8("removePointButton3"));
        removePointButton3->setMaximumSize(QSize(75, 30));
        removePointButton3->setIcon(icon7);

        horizontalLayout_10->addWidget(removePointButton3);


        verticalLayout_8->addLayout(horizontalLayout_10);


        horizontalLayout_9->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        ml3 = new QLabel(centralwidget);
        ml3->setObjectName(QString::fromUtf8("ml3"));
        ml3->setMaximumSize(QSize(16777215, 20));
        ml3->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(ml3);

        measView3 = new QListView(centralwidget);
        measView3->setObjectName(QString::fromUtf8("measView3"));
        measView3->setMaximumSize(QSize(16777215, 250));
        measView3->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_9->addWidget(measView3);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        newMeasButton3 = new QToolButton(centralwidget);
        newMeasButton3->setObjectName(QString::fromUtf8("newMeasButton3"));
        sizePolicy1.setHeightForWidth(newMeasButton3->sizePolicy().hasHeightForWidth());
        newMeasButton3->setSizePolicy(sizePolicy1);
        newMeasButton3->setMaximumSize(QSize(75, 30));
        newMeasButton3->setIcon(icon5);

        horizontalLayout_11->addWidget(newMeasButton3);

        renameMeasButton3 = new QPushButton(centralwidget);
        renameMeasButton3->setObjectName(QString::fromUtf8("renameMeasButton3"));
        renameMeasButton3->setMaximumSize(QSize(75, 30));
        renameMeasButton3->setIcon(icon6);

        horizontalLayout_11->addWidget(renameMeasButton3);

        removeMeasButton3 = new QPushButton(centralwidget);
        removeMeasButton3->setObjectName(QString::fromUtf8("removeMeasButton3"));
        removeMeasButton3->setMaximumSize(QSize(75, 30));
        removeMeasButton3->setAcceptDrops(false);
        removeMeasButton3->setIcon(icon7);

        horizontalLayout_11->addWidget(removeMeasButton3);


        verticalLayout_9->addLayout(horizontalLayout_11);


        horizontalLayout_9->addLayout(verticalLayout_9);


        verticalLayout_7->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        il4 = new QLabel(centralwidget);
        il4->setObjectName(QString::fromUtf8("il4"));
        il4->setMaximumSize(QSize(16777215, 20));
        il4->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(il4);

        imageLabel4 = new CustomLabel(centralwidget);
        imageLabel4->setObjectName(QString::fromUtf8("imageLabel4"));
        sizePolicy.setHeightForWidth(imageLabel4->sizePolicy().hasHeightForWidth());
        imageLabel4->setSizePolicy(sizePolicy);
        imageLabel4->setMinimumSize(QSize(400, 180));
        imageLabel4->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(imageLabel4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        pl4 = new QLabel(centralwidget);
        pl4->setObjectName(QString::fromUtf8("pl4"));
        pl4->setMaximumSize(QSize(16777215, 20));
        pl4->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(pl4);

        pointView4 = new QListView(centralwidget);
        pointView4->setObjectName(QString::fromUtf8("pointView4"));
        pointView4->setMaximumSize(QSize(16777215, 250));
        pointView4->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_11->addWidget(pointView4);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        newPointButton4 = new QPushButton(centralwidget);
        newPointButton4->setObjectName(QString::fromUtf8("newPointButton4"));
        newPointButton4->setMaximumSize(QSize(75, 30));
        newPointButton4->setIcon(icon5);

        horizontalLayout_13->addWidget(newPointButton4);

        renamePointButton4 = new QPushButton(centralwidget);
        renamePointButton4->setObjectName(QString::fromUtf8("renamePointButton4"));
        renamePointButton4->setMaximumSize(QSize(75, 30));
        renamePointButton4->setIcon(icon6);

        horizontalLayout_13->addWidget(renamePointButton4);

        removePointButton4 = new QPushButton(centralwidget);
        removePointButton4->setObjectName(QString::fromUtf8("removePointButton4"));
        removePointButton4->setMaximumSize(QSize(75, 30));
        removePointButton4->setIcon(icon7);

        horizontalLayout_13->addWidget(removePointButton4);


        verticalLayout_11->addLayout(horizontalLayout_13);


        horizontalLayout_12->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        ml4 = new QLabel(centralwidget);
        ml4->setObjectName(QString::fromUtf8("ml4"));
        ml4->setMaximumSize(QSize(16777215, 20));
        ml4->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(ml4);

        measView4 = new QListView(centralwidget);
        measView4->setObjectName(QString::fromUtf8("measView4"));
        measView4->setMaximumSize(QSize(16777215, 250));
        measView4->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_12->addWidget(measView4);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        newMeasButton4 = new QToolButton(centralwidget);
        newMeasButton4->setObjectName(QString::fromUtf8("newMeasButton4"));
        sizePolicy1.setHeightForWidth(newMeasButton4->sizePolicy().hasHeightForWidth());
        newMeasButton4->setSizePolicy(sizePolicy1);
        newMeasButton4->setMaximumSize(QSize(75, 30));
        newMeasButton4->setIcon(icon5);

        horizontalLayout_14->addWidget(newMeasButton4);

        renameMeasButton4 = new QPushButton(centralwidget);
        renameMeasButton4->setObjectName(QString::fromUtf8("renameMeasButton4"));
        renameMeasButton4->setMaximumSize(QSize(75, 30));
        renameMeasButton4->setIcon(icon6);

        horizontalLayout_14->addWidget(renameMeasButton4);

        removeMeasButton4 = new QPushButton(centralwidget);
        removeMeasButton4->setObjectName(QString::fromUtf8("removeMeasButton4"));
        removeMeasButton4->setMaximumSize(QSize(75, 30));
        removeMeasButton4->setIcon(icon7);

        horizontalLayout_14->addWidget(removeMeasButton4);


        verticalLayout_12->addLayout(horizontalLayout_14);


        horizontalLayout_12->addLayout(verticalLayout_12);


        verticalLayout_10->addLayout(horizontalLayout_12);


        horizontalLayout_8->addLayout(verticalLayout_10);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(infoLabel, 2, 0, 1, 1);

        SchemaWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SchemaWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SchemaWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(SchemaWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        SchemaWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar->addAction(actionOpen_Images);
        toolBar->addAction(actionSet_Correction_Measurement);

        retranslateUi(SchemaWindow);

        QMetaObject::connectSlotsByName(SchemaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SchemaWindow)
    {
        SchemaWindow->setWindowTitle(QCoreApplication::translate("SchemaWindow", "Manage shemas", nullptr));
        actionOpen_Images->setText(QCoreApplication::translate("SchemaWindow", "Open Images", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen_Images->setToolTip(QCoreApplication::translate("SchemaWindow", "Open Images to aid schema creation", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen_Images->setShortcut(QCoreApplication::translate("SchemaWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("SchemaWindow", "save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("SchemaWindow", "Save schema", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("SchemaWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("SchemaWindow", "Save as...", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as->setToolTip(QCoreApplication::translate("SchemaWindow", "Save schema", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("SchemaWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSet_Correction_Measurement->setText(QCoreApplication::translate("SchemaWindow", "Set Correction Measurement", nullptr));
#if QT_CONFIG(tooltip)
        actionSet_Correction_Measurement->setToolTip(QCoreApplication::translate("SchemaWindow", "Select a distance from the side measurements that best describes the height of the animal. (This will be used for automatic correction)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSet_Correction_Measurement->setShortcut(QCoreApplication::translate("SchemaWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDone->setText(QCoreApplication::translate("SchemaWindow", "Done", nullptr));
#if QT_CONFIG(tooltip)
        actionDone->setToolTip(QCoreApplication::translate("SchemaWindow", "Return to main window", nullptr));
#endif // QT_CONFIG(tooltip)
        il1->setText(QCoreApplication::translate("SchemaWindow", "Image #1", nullptr));
        imageLabel1->setText(QString());
        pl1->setText(QCoreApplication::translate("SchemaWindow", "Points", nullptr));
#if QT_CONFIG(tooltip)
        newPointButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        newPointButton1->setText(QString());
#if QT_CONFIG(tooltip)
        renamePointButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename point", nullptr));
#endif // QT_CONFIG(tooltip)
        renamePointButton1->setText(QString());
#if QT_CONFIG(tooltip)
        removePointButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove point", nullptr));
#endif // QT_CONFIG(tooltip)
        removePointButton1->setText(QString());
        ml1->setText(QCoreApplication::translate("SchemaWindow", "Measurements", nullptr));
#if QT_CONFIG(tooltip)
        newMeasButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Add measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        newMeasButton1->setText(QString());
#if QT_CONFIG(tooltip)
        renameMeasButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        renameMeasButton1->setText(QString());
#if QT_CONFIG(tooltip)
        removeMeasButton1->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        removeMeasButton1->setText(QString());
        il2->setText(QCoreApplication::translate("SchemaWindow", "Image #2", nullptr));
        imageLabel2->setText(QString());
        pl2->setText(QCoreApplication::translate("SchemaWindow", "Points", nullptr));
#if QT_CONFIG(tooltip)
        newPointButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        newPointButton2->setText(QString());
#if QT_CONFIG(tooltip)
        renamePointButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename point", nullptr));
#endif // QT_CONFIG(tooltip)
        renamePointButton2->setText(QString());
#if QT_CONFIG(tooltip)
        removePointButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove point", nullptr));
#endif // QT_CONFIG(tooltip)
        removePointButton2->setText(QString());
        ml2->setText(QCoreApplication::translate("SchemaWindow", "Measurements", nullptr));
#if QT_CONFIG(tooltip)
        newMeasButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Add measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        newMeasButton2->setText(QString());
#if QT_CONFIG(tooltip)
        renameMeasButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        renameMeasButton2->setText(QString());
#if QT_CONFIG(tooltip)
        removeMeasButton2->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        removeMeasButton2->setText(QString());
        il3->setText(QCoreApplication::translate("SchemaWindow", "Image #3", nullptr));
        imageLabel3->setText(QString());
        pl3->setText(QCoreApplication::translate("SchemaWindow", "Points", nullptr));
#if QT_CONFIG(tooltip)
        newPointButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        newPointButton3->setText(QString());
#if QT_CONFIG(tooltip)
        renamePointButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename point", nullptr));
#endif // QT_CONFIG(tooltip)
        renamePointButton3->setText(QString());
#if QT_CONFIG(tooltip)
        removePointButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove point", nullptr));
#endif // QT_CONFIG(tooltip)
        removePointButton3->setText(QString());
        ml3->setText(QCoreApplication::translate("SchemaWindow", "Measurements", nullptr));
#if QT_CONFIG(tooltip)
        newMeasButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Add measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        newMeasButton3->setText(QString());
#if QT_CONFIG(tooltip)
        renameMeasButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        renameMeasButton3->setText(QString());
#if QT_CONFIG(tooltip)
        removeMeasButton3->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        removeMeasButton3->setText(QString());
        il4->setText(QCoreApplication::translate("SchemaWindow", "Image #4", nullptr));
        imageLabel4->setText(QString());
        pl4->setText(QCoreApplication::translate("SchemaWindow", "Points", nullptr));
#if QT_CONFIG(tooltip)
        newPointButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        newPointButton4->setText(QString());
#if QT_CONFIG(tooltip)
        renamePointButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename point", nullptr));
#endif // QT_CONFIG(tooltip)
        renamePointButton4->setText(QString());
#if QT_CONFIG(tooltip)
        removePointButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove point", nullptr));
#endif // QT_CONFIG(tooltip)
        removePointButton4->setText(QString());
        ml4->setText(QCoreApplication::translate("SchemaWindow", "Measurements", nullptr));
#if QT_CONFIG(tooltip)
        newMeasButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Add measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        newMeasButton4->setText(QString());
#if QT_CONFIG(tooltip)
        renameMeasButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Rename measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        renameMeasButton4->setText(QString());
#if QT_CONFIG(tooltip)
        removeMeasButton4->setToolTip(QCoreApplication::translate("SchemaWindow", "Remove measurement", nullptr));
#endif // QT_CONFIG(tooltip)
        removeMeasButton4->setText(QString());
        infoLabel->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("SchemaWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SchemaWindow: public Ui_SchemaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEMA_H
