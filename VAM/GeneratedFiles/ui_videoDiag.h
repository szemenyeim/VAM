/********************************************************************************
** Form generated from reading UI file 'videoDiag.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODIAG_H
#define UI_VIDEODIAG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *camDistBox;
    QListView *dbListView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addVid;
    QPushButton *deleteVid;
    QPushButton *vidUp;
    QPushButton *vidDown;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *VideoDialog)
    {
        if (VideoDialog->objectName().isEmpty())
            VideoDialog->setObjectName(QString::fromUtf8("VideoDialog"));
        VideoDialog->setWindowModality(Qt::ApplicationModal);
        VideoDialog->resize(300, 400);
        VideoDialog->setMinimumSize(QSize(300, 400));
        VideoDialog->setMaximumSize(QSize(300, 400));
        horizontalLayoutWidget = new QWidget(VideoDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 9, 281, 381));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        camDistBox = new QDoubleSpinBox(horizontalLayoutWidget);
        camDistBox->setObjectName(QString::fromUtf8("camDistBox"));

        horizontalLayout_4->addWidget(camDistBox);


        verticalLayout->addLayout(horizontalLayout_4);

        dbListView = new QListView(horizontalLayoutWidget);
        dbListView->setObjectName(QString::fromUtf8("dbListView"));
        dbListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(dbListView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addVid = new QPushButton(horizontalLayoutWidget);
        addVid->setObjectName(QString::fromUtf8("addVid"));
        addVid->setMaximumSize(QSize(75, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addVid->setIcon(icon);

        horizontalLayout_2->addWidget(addVid);

        deleteVid = new QPushButton(horizontalLayoutWidget);
        deleteVid->setObjectName(QString::fromUtf8("deleteVid"));
        deleteVid->setMaximumSize(QSize(75, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteVid->setIcon(icon1);

        horizontalLayout_2->addWidget(deleteVid);

        vidUp = new QPushButton(horizontalLayoutWidget);
        vidUp->setObjectName(QString::fromUtf8("vidUp"));
        vidUp->setMaximumSize(QSize(75, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VAM/Icons/1462036195_arrow-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        vidUp->setIcon(icon2);

        horizontalLayout_2->addWidget(vidUp);

        vidDown = new QPushButton(horizontalLayoutWidget);
        vidDown->setObjectName(QString::fromUtf8("vidDown"));
        vidDown->setMinimumSize(QSize(0, 0));
        vidDown->setMaximumSize(QSize(75, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VAM/Icons/1462036198_arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        vidDown->setIcon(icon3);

        horizontalLayout_2->addWidget(vidDown);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        saveBtn = new QPushButton(horizontalLayoutWidget);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMaximumSize(QSize(75, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveBtn->setIcon(icon4);

        horizontalLayout_3->addWidget(saveBtn);

        cancelBtn = new QPushButton(horizontalLayoutWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMaximumSize(QSize(75, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VAM/Icons/1466084143_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelBtn->setIcon(icon5);

        horizontalLayout_3->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(VideoDialog);

        QMetaObject::connectSlotsByName(VideoDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoDialog)
    {
        VideoDialog->setWindowTitle(QCoreApplication::translate("VideoDialog", "Video Management", nullptr));
        label_7->setText(QCoreApplication::translate("VideoDialog", "Videos", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("VideoDialog", "Use this to set the distance of the camera from the reference point, where the etalon is.", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("VideoDialog", "Camera Distance:", nullptr));
#if QT_CONFIG(tooltip)
        camDistBox->setToolTip(QCoreApplication::translate("VideoDialog", "Use this to set the distance of the camera from the reference point, where the etalon is.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        addVid->setToolTip(QCoreApplication::translate("VideoDialog", "Add new video", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        addVid->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        addVid->setText(QString());
#if QT_CONFIG(tooltip)
        deleteVid->setToolTip(QCoreApplication::translate("VideoDialog", "Remove video", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteVid->setText(QString());
#if QT_CONFIG(tooltip)
        vidUp->setToolTip(QCoreApplication::translate("VideoDialog", "Move video up", nullptr));
#endif // QT_CONFIG(tooltip)
        vidUp->setText(QString());
#if QT_CONFIG(tooltip)
        vidDown->setToolTip(QCoreApplication::translate("VideoDialog", "Move video down", nullptr));
#endif // QT_CONFIG(tooltip)
        vidDown->setText(QString());
#if QT_CONFIG(tooltip)
        saveBtn->setToolTip(QCoreApplication::translate("VideoDialog", "Save video list", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        saveBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        saveBtn->setText(QCoreApplication::translate("VideoDialog", "Save", nullptr));
#if QT_CONFIG(tooltip)
        cancelBtn->setToolTip(QCoreApplication::translate("VideoDialog", "Return without saving", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelBtn->setText(QCoreApplication::translate("VideoDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoDialog: public Ui_VideoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODIAG_H
