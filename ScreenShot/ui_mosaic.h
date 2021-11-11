/********************************************************************************
** Form generated from reading UI file 'mosaic.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOSAIC_H
#define UI_MOSAIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mosaic
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Mosaic)
    {
        if (Mosaic->objectName().isEmpty())
            Mosaic->setObjectName(QString::fromUtf8("Mosaic"));
        Mosaic->resize(823, 562);
        gridLayout = new QGridLayout(Mosaic);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(Mosaic);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 711, 514));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        label = new QLabel(Mosaic);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(0, 1);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_3 = new QPushButton(Mosaic);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(80, 60));

        verticalLayout_2->addWidget(pushButton_3);

        pushButton = new QPushButton(Mosaic);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(80, 60));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(Mosaic);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 60));

        verticalLayout_2->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Mosaic);

        QMetaObject::connectSlotsByName(Mosaic);
    } // setupUi

    void retranslateUi(QDialog *Mosaic)
    {
        Mosaic->setWindowTitle(QCoreApplication::translate("Mosaic", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Mosaic", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Mosaic", "\346\211\223\345\274\200", nullptr));
        pushButton->setText(QCoreApplication::translate("Mosaic", "\351\207\215\347\275\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Mosaic", "\345\217\246\345\255\230\344\270\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mosaic: public Ui_Mosaic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOSAIC_H
