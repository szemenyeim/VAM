/********************************************************************************
** Form generated from reading UI file 'videoDiag.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODIAG_H
#define UI_VIDEODIAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            VideoDialog->setObjectName(QStringLiteral("VideoDialog"));
        VideoDialog->setWindowModality(Qt::ApplicationModal);
        VideoDialog->resize(300, 400);
        VideoDialog->setMinimumSize(QSize(300, 400));
        VideoDialog->setMaximumSize(QSize(300, 400));
        horizontalLayoutWidget = new QWidget(VideoDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 9, 281, 381));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        camDistBox = new QDoubleSpinBox(horizontalLayoutWidget);
        camDistBox->setObjectName(QStringLiteral("camDistBox"));

        horizontalLayout_4->addWidget(camDistBox);


        verticalLayout->addLayout(horizontalLayout_4);

        dbListView = new QListView(horizontalLayoutWidget);
        dbListView->setObjectName(QStringLiteral("dbListView"));
        dbListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(dbListView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        addVid = new QPushButton(horizontalLayoutWidget);
        addVid->setObjectName(QStringLiteral("addVid"));
        addVid->setMaximumSize(QSize(75, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/VAM/Icons/1462036180_list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addVid->setIcon(icon);

        horizontalLayout_2->addWidget(addVid);

        deleteVid = new QPushButton(horizontalLayoutWidget);
        deleteVid->setObjectName(QStringLiteral("deleteVid"));
        deleteVid->setMaximumSize(QSize(75, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/VAM/Icons/1462036183_document-delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteVid->setIcon(icon1);

        horizontalLayout_2->addWidget(deleteVid);

        vidUp = new QPushButton(horizontalLayoutWidget);
        vidUp->setObjectName(QStringLiteral("vidUp"));
        vidUp->setMaximumSize(QSize(75, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/VAM/Icons/1462036195_arrow-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        vidUp->setIcon(icon2);

        horizontalLayout_2->addWidget(vidUp);

        vidDown = new QPushButton(horizontalLayoutWidget);
        vidDown->setObjectName(QStringLiteral("vidDown"));
        vidDown->setMinimumSize(QSize(0, 0));
        vidDown->setMaximumSize(QSize(75, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/VAM/Icons/1462036198_arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        vidDown->setIcon(icon3);

        horizontalLayout_2->addWidget(vidDown);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        saveBtn = new QPushButton(horizontalLayoutWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setMaximumSize(QSize(75, 30));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/VAM/Icons/1466084211_Accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveBtn->setIcon(icon4);

        horizontalLayout_3->addWidget(saveBtn);

        cancelBtn = new QPushButton(horizontalLayoutWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMaximumSize(QSize(75, 30));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/VAM/Icons/1466084143_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelBtn->setIcon(icon5);

        horizontalLayout_3->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(VideoDialog);

        QMetaObject::connectSlotsByName(VideoDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoDialog)
    {
        VideoDialog->setWindowTitle(QApplication::translate("VideoDialog", "Video Management", Q_NULLPTR));
        label_7->setText(QApplication::translate("VideoDialog", "Videos", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("VideoDialog", "Use this to set the distance of the camera from the reference point, where the etalon is.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("VideoDialog", "Camera Distance:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        camDistBox->setToolTip(QApplication::translate("VideoDialog", "Use this to set the distance of the camera from the reference point, where the etalon is.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        addVid->setToolTip(QApplication::translate("VideoDialog", "Add new video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        addVid->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        addVid->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteVid->setToolTip(QApplication::translate("VideoDialog", "Remove video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteVid->setText(QString());
#ifndef QT_NO_TOOLTIP
        vidUp->setToolTip(QApplication::translate("VideoDialog", "Move video up", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        vidUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        vidDown->setToolTip(QApplication::translate("VideoDialog", "Move video down", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        vidDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        saveBtn->setToolTip(QApplication::translate("VideoDialog", "Save video list", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        saveBtn->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        saveBtn->setText(QApplication::translate("VideoDialog", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cancelBtn->setToolTip(QApplication::translate("VideoDialog", "Return without saving", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cancelBtn->setText(QApplication::translate("VideoDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoDialog: public Ui_VideoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODIAG_H
