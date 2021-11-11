/********************************************************************************
** Form generated from reading UI file 'recorddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDDIALOG_H
#define UI_RECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RecordDialog
{
public:
    QPushButton *startBt;
    QPushButton *stopBt;

    void setupUi(QDialog *RecordDialog)
    {
        if (RecordDialog->objectName().isEmpty())
            RecordDialog->setObjectName(QString::fromUtf8("RecordDialog"));
        RecordDialog->resize(80, 160);
        RecordDialog->setMinimumSize(QSize(80, 160));
        RecordDialog->setMaximumSize(QSize(80, 160));
        startBt = new QPushButton(RecordDialog);
        startBt->setObjectName(QString::fromUtf8("startBt"));
        startBt->setGeometry(QRect(0, 10, 80, 60));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startBt->sizePolicy().hasHeightForWidth());
        startBt->setSizePolicy(sizePolicy);
        startBt->setMinimumSize(QSize(80, 60));
        startBt->setMaximumSize(QSize(80, 60));
        QFont font;
        font.setPointSize(17);
        startBt->setFont(font);
        stopBt = new QPushButton(RecordDialog);
        stopBt->setObjectName(QString::fromUtf8("stopBt"));
        stopBt->setGeometry(QRect(0, 90, 80, 60));
        stopBt->setMinimumSize(QSize(80, 60));
        stopBt->setMaximumSize(QSize(80, 60));
        stopBt->setFont(font);

        retranslateUi(RecordDialog);

        QMetaObject::connectSlotsByName(RecordDialog);
    } // setupUi

    void retranslateUi(QDialog *RecordDialog)
    {
        RecordDialog->setWindowTitle(QCoreApplication::translate("RecordDialog", "Dialog", nullptr));
        startBt->setText(QCoreApplication::translate("RecordDialog", "\345\274\200\345\247\213", nullptr));
        stopBt->setText(QCoreApplication::translate("RecordDialog", "\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordDialog: public Ui_RecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDDIALOG_H
