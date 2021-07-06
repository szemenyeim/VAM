/********************************************************************************
** Form generated from reading UI file 'autoStillDiag.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTILLDIAG_H
#define UI_AUTOSTILLDIAG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customlabel.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *videoLayout1;
    QLabel *label1;
    CustomLabel *image1;
    QHBoxLayout *horizontalLayout_9;
    QListView *stillList1;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *videoLayout3;
    QLabel *label3;
    CustomLabel *image3;
    QHBoxLayout *horizontalLayout_11;
    QListView *stillList3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *videoLayout2;
    QLabel *label2;
    CustomLabel *image2;
    QHBoxLayout *horizontalLayout_6;
    QListView *stillList2;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *videoLayout4;
    QLabel *label4;
    CustomLabel *image4;
    QHBoxLayout *horizontalLayout_13;
    QListView *stillList4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addElem;
    QPushButton *deleteElem;
    QHBoxLayout *horizontalLayout_4;
    QListView *pairedList;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1040, 1080);
        Dialog->setMinimumSize(QSize(1040, 1080));
        Dialog->setMaximumSize(QSize(1040, 1080));
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 1001, 1041));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        videoLayout1 = new QVBoxLayout();
        videoLayout1->setObjectName(QString::fromUtf8("videoLayout1"));
        label1 = new QLabel(horizontalLayoutWidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setMaximumSize(QSize(16777215, 20));
        label1->setAlignment(Qt::AlignCenter);

        videoLayout1->addWidget(label1);

        image1 = new CustomLabel(horizontalLayoutWidget);
        image1->setObjectName(QString::fromUtf8("image1"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image1->sizePolicy().hasHeightForWidth());
        image1->setSizePolicy(sizePolicy);
        image1->setMinimumSize(QSize(320, 240));

        videoLayout1->addWidget(image1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        stillList1 = new QListView(horizontalLayoutWidget);
        stillList1->setObjectName(QString::fromUtf8("stillList1"));

        horizontalLayout_9->addWidget(stillList1);


        videoLayout1->addLayout(horizontalLayout_9);


        horizontalLayout_7->addLayout(videoLayout1);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        videoLayout3 = new QVBoxLayout();
        videoLayout3->setObjectName(QString::fromUtf8("videoLayout3"));
        label3 = new QLabel(horizontalLayoutWidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setMaximumSize(QSize(16777215, 20));
        label3->setAlignment(Qt::AlignCenter);

        videoLayout3->addWidget(label3);

        image3 = new CustomLabel(horizontalLayoutWidget);
        image3->setObjectName(QString::fromUtf8("image3"));
        sizePolicy.setHeightForWidth(image3->sizePolicy().hasHeightForWidth());
        image3->setSizePolicy(sizePolicy);
        image3->setMinimumSize(QSize(320, 240));

        videoLayout3->addWidget(image3);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        stillList3 = new QListView(horizontalLayoutWidget);
        stillList3->setObjectName(QString::fromUtf8("stillList3"));

        horizontalLayout_11->addWidget(stillList3);


        videoLayout3->addLayout(horizontalLayout_11);


        horizontalLayout_10->addLayout(videoLayout3);


        verticalLayout_5->addLayout(horizontalLayout_10);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        videoLayout2 = new QVBoxLayout();
        videoLayout2->setObjectName(QString::fromUtf8("videoLayout2"));
        label2 = new QLabel(horizontalLayoutWidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setMaximumSize(QSize(16777215, 20));
        label2->setAlignment(Qt::AlignCenter);

        videoLayout2->addWidget(label2);

        image2 = new CustomLabel(horizontalLayoutWidget);
        image2->setObjectName(QString::fromUtf8("image2"));
        sizePolicy.setHeightForWidth(image2->sizePolicy().hasHeightForWidth());
        image2->setSizePolicy(sizePolicy);
        image2->setMinimumSize(QSize(320, 240));

        videoLayout2->addWidget(image2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        stillList2 = new QListView(horizontalLayoutWidget);
        stillList2->setObjectName(QString::fromUtf8("stillList2"));

        horizontalLayout_6->addWidget(stillList2);


        videoLayout2->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(videoLayout2);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        videoLayout4 = new QVBoxLayout();
        videoLayout4->setObjectName(QString::fromUtf8("videoLayout4"));
        label4 = new QLabel(horizontalLayoutWidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setMaximumSize(QSize(16777215, 20));
        label4->setAlignment(Qt::AlignCenter);

        videoLayout4->addWidget(label4);

        image4 = new CustomLabel(horizontalLayoutWidget);
        image4->setObjectName(QString::fromUtf8("image4"));
        sizePolicy.setHeightForWidth(image4->sizePolicy().hasHeightForWidth());
        image4->setSizePolicy(sizePolicy);
        image4->setMinimumSize(QSize(320, 240));

        videoLayout4->addWidget(image4);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        stillList4 = new QListView(horizontalLayoutWidget);
        stillList4->setObjectName(QString::fromUtf8("stillList4"));

        horizontalLayout_13->addWidget(stillList4);


        videoLayout4->addLayout(horizontalLayout_13);


        horizontalLayout_12->addLayout(videoLayout4);


        verticalLayout_6->addLayout(horizontalLayout_12);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addElem = new QPushButton(horizontalLayoutWidget);
        addElem->setObjectName(QString::fromUtf8("addElem"));
        addElem->setMaximumSize(QSize(75, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addElem->setIcon(icon);

        horizontalLayout_2->addWidget(addElem);

        deleteElem = new QPushButton(horizontalLayoutWidget);
        deleteElem->setObjectName(QString::fromUtf8("deleteElem"));
        deleteElem->setMaximumSize(QSize(75, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteElem->setIcon(icon1);

        horizontalLayout_2->addWidget(deleteElem);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pairedList = new QListView(horizontalLayoutWidget);
        pairedList->setObjectName(QString::fromUtf8("pairedList"));

        horizontalLayout_4->addWidget(pairedList);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        saveBtn = new QPushButton(horizontalLayoutWidget);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMaximumSize(QSize(75, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveBtn->setIcon(icon2);

        horizontalLayout_3->addWidget(saveBtn);

        cancelBtn = new QPushButton(horizontalLayoutWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMaximumSize(QSize(75, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelBtn->setIcon(icon3);

        horizontalLayout_3->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label1->setText(QCoreApplication::translate("Dialog", "Video 1", nullptr));
        image1->setProperty("text", QVariant(QString()));
        label3->setText(QCoreApplication::translate("Dialog", "Video 3", nullptr));
        image3->setProperty("text", QVariant(QString()));
        label2->setText(QCoreApplication::translate("Dialog", "Video 2", nullptr));
        image2->setProperty("text", QVariant(QString()));
        label4->setText(QCoreApplication::translate("Dialog", "Video 4", nullptr));
        image4->setProperty("text", QVariant(QString()));
        label_7->setText(QCoreApplication::translate("Dialog", "Paired IDs", nullptr));
#if QT_CONFIG(tooltip)
        addElem->setToolTip(QCoreApplication::translate("Dialog", "Add new video", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        addElem->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        addElem->setText(QString());
#if QT_CONFIG(tooltip)
        deleteElem->setToolTip(QCoreApplication::translate("Dialog", "Remove video", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteElem->setText(QString());
#if QT_CONFIG(tooltip)
        saveBtn->setToolTip(QCoreApplication::translate("Dialog", "Save video list", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        saveBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        saveBtn->setText(QCoreApplication::translate("Dialog", "Save", nullptr));
#if QT_CONFIG(tooltip)
        cancelBtn->setToolTip(QCoreApplication::translate("Dialog", "Return without saving", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelBtn->setText(QCoreApplication::translate("Dialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTILLDIAG_H
