/********************************************************************************
** Form generated from reading UI file 'morpho.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MORPHO_H
#define UI_MORPHO_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MorphoWindow
{
public:
    QAction *actionSave;
    QAction *actionExport;
    QAction *actionDone;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *pl1;
    QListView *pointView1;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBtn1;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *pl2;
    QListView *pointView2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addBtn2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QLabel *pl3;
    QListView *pointView3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *addBtn3;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QLabel *pl4;
    QListView *pointView4;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *addBtn4;
    QVBoxLayout *verticalLayout_2;
    QListView *listView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *delButton;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MorphoWindow)
    {
        if (MorphoWindow->objectName().isEmpty())
            MorphoWindow->setObjectName(QString::fromUtf8("MorphoWindow"));
        MorphoWindow->setWindowModality(Qt::NonModal);
        MorphoWindow->resize(845, 765);
        MorphoWindow->setMinimumSize(QSize(845, 765));
        MorphoWindow->setMaximumSize(QSize(1920, 1080));
        actionSave = new QAction(MorphoWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036176_save_accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionExport = new QAction(MorphoWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462455465_centimeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon1);
        actionDone = new QAction(MorphoWindow);
        actionDone->setObjectName(QString::fromUtf8("actionDone"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDone->setIcon(icon2);
        centralwidget = new QWidget(MorphoWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
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
        addBtn1 = new QPushButton(centralwidget);
        addBtn1->setObjectName(QString::fromUtf8("addBtn1"));
        addBtn1->setMaximumSize(QSize(75, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462036188_Fast-Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        addBtn1->setIcon(icon3);

        horizontalLayout->addWidget(addBtn1);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
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
        addBtn2 = new QPushButton(centralwidget);
        addBtn2->setObjectName(QString::fromUtf8("addBtn2"));
        addBtn2->setMaximumSize(QSize(75, 30));
        addBtn2->setIcon(icon3);

        horizontalLayout_3->addWidget(addBtn2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_6);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
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
        addBtn3 = new QPushButton(centralwidget);
        addBtn3->setObjectName(QString::fromUtf8("addBtn3"));
        addBtn3->setMaximumSize(QSize(75, 30));
        addBtn3->setIcon(icon3);

        horizontalLayout_10->addWidget(addBtn3);


        verticalLayout_8->addLayout(horizontalLayout_10);


        horizontalLayout_9->addLayout(verticalLayout_8);


        verticalLayout_7->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
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
        addBtn4 = new QPushButton(centralwidget);
        addBtn4->setObjectName(QString::fromUtf8("addBtn4"));
        addBtn4->setMaximumSize(QSize(75, 30));
        addBtn4->setIcon(icon3);

        horizontalLayout_13->addWidget(addBtn4);


        verticalLayout_11->addLayout(horizontalLayout_13);


        horizontalLayout_12->addLayout(verticalLayout_11);


        verticalLayout_10->addLayout(horizontalLayout_12);


        horizontalLayout_8->addLayout(verticalLayout_10);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_2->addWidget(listView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setMaximumSize(QSize(75, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1462036195_arrow-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon4);

        horizontalLayout_2->addWidget(upButton);

        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setMaximumSize(QSize(75, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1462036198_arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        downButton->setIcon(icon5);

        horizontalLayout_2->addWidget(downButton);

        delButton = new QPushButton(centralwidget);
        delButton->setObjectName(QString::fromUtf8("delButton"));
        delButton->setMaximumSize(QSize(75, 30));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        delButton->setIcon(icon6);

        horizontalLayout_2->addWidget(delButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 2, 1);

        MorphoWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MorphoWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MorphoWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MorphoWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MorphoWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionDone);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionExport);

        retranslateUi(MorphoWindow);

        QMetaObject::connectSlotsByName(MorphoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MorphoWindow)
    {
        MorphoWindow->setWindowTitle(QCoreApplication::translate("MorphoWindow", "Export Morphometrics Data", nullptr));
        actionSave->setText(QCoreApplication::translate("MorphoWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MorphoWindow", "Save schema", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MorphoWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExport->setText(QCoreApplication::translate("MorphoWindow", "Export", nullptr));
#if QT_CONFIG(tooltip)
        actionExport->setToolTip(QCoreApplication::translate("MorphoWindow", "Export morphometrics data", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionExport->setShortcut(QCoreApplication::translate("MorphoWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDone->setText(QCoreApplication::translate("MorphoWindow", "Done", nullptr));
#if QT_CONFIG(tooltip)
        actionDone->setToolTip(QCoreApplication::translate("MorphoWindow", "Return to main window", nullptr));
#endif // QT_CONFIG(tooltip)
        pl1->setText(QCoreApplication::translate("MorphoWindow", "Camera #1", nullptr));
#if QT_CONFIG(tooltip)
        addBtn1->setToolTip(QCoreApplication::translate("MorphoWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn1->setText(QString());
        pl2->setText(QCoreApplication::translate("MorphoWindow", "Camera #2", nullptr));
#if QT_CONFIG(tooltip)
        addBtn2->setToolTip(QCoreApplication::translate("MorphoWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn2->setText(QString());
        pl3->setText(QCoreApplication::translate("MorphoWindow", "Camera #3", nullptr));
#if QT_CONFIG(tooltip)
        addBtn3->setToolTip(QCoreApplication::translate("MorphoWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn3->setText(QString());
        pl4->setText(QCoreApplication::translate("MorphoWindow", "Camera #4", nullptr));
#if QT_CONFIG(tooltip)
        addBtn4->setToolTip(QCoreApplication::translate("MorphoWindow", "Add point", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn4->setText(QString());
        upButton->setText(QString());
        downButton->setText(QString());
        delButton->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("MorphoWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MorphoWindow: public Ui_MorphoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MORPHO_H
