/********************************************************************************
** Form generated from reading UI file 'filter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTER_H
#define UI_FILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Filter
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *open;
    QPushButton *btn_reverse;
    QPushButton *btn_grey;
    QPushButton *btn_cool;
    QPushButton *btn_warm;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_saveas;
    QPushButton *btn_soften;
    QPushButton *btn_old;
    QPushButton *btn_vague;
    QPushButton *btn_sharpen;

    void setupUi(QDialog *Filter)
    {
        if (Filter->objectName().isEmpty())
            Filter->setObjectName(QString::fromUtf8("Filter"));
        Filter->resize(1003, 575);
        Filter->setMinimumSize(QSize(900, 400));
        gridLayout = new QGridLayout(Filter);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(Filter);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        label_2 = new QLabel(Filter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        open = new QPushButton(Filter);
        open->setObjectName(QString::fromUtf8("open"));
        open->setMinimumSize(QSize(80, 60));
        open->setMaximumSize(QSize(80, 60));

        horizontalLayout->addWidget(open);

        btn_reverse = new QPushButton(Filter);
        btn_reverse->setObjectName(QString::fromUtf8("btn_reverse"));
        btn_reverse->setMinimumSize(QSize(80, 60));
        btn_reverse->setMaximumSize(QSize(80, 60));

        horizontalLayout->addWidget(btn_reverse);

        btn_grey = new QPushButton(Filter);
        btn_grey->setObjectName(QString::fromUtf8("btn_grey"));
        btn_grey->setMinimumSize(QSize(80, 60));
        btn_grey->setMaximumSize(QSize(80, 60));

        horizontalLayout->addWidget(btn_grey);

        btn_cool = new QPushButton(Filter);
        btn_cool->setObjectName(QString::fromUtf8("btn_cool"));
        btn_cool->setMinimumSize(QSize(80, 60));
        btn_cool->setMaximumSize(QSize(80, 60));

        horizontalLayout->addWidget(btn_cool);

        btn_warm = new QPushButton(Filter);
        btn_warm->setObjectName(QString::fromUtf8("btn_warm"));
        btn_warm->setMinimumSize(QSize(80, 60));
        btn_warm->setMaximumSize(QSize(80, 60));

        horizontalLayout->addWidget(btn_warm);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_saveas = new QPushButton(Filter);
        btn_saveas->setObjectName(QString::fromUtf8("btn_saveas"));
        btn_saveas->setMinimumSize(QSize(80, 60));
        btn_saveas->setMaximumSize(QSize(80, 60));

        horizontalLayout_2->addWidget(btn_saveas);

        btn_soften = new QPushButton(Filter);
        btn_soften->setObjectName(QString::fromUtf8("btn_soften"));
        btn_soften->setMinimumSize(QSize(80, 60));
        btn_soften->setMaximumSize(QSize(80, 69));

        horizontalLayout_2->addWidget(btn_soften);

        btn_old = new QPushButton(Filter);
        btn_old->setObjectName(QString::fromUtf8("btn_old"));
        btn_old->setMinimumSize(QSize(80, 60));
        btn_old->setMaximumSize(QSize(80, 60));

        horizontalLayout_2->addWidget(btn_old);

        btn_vague = new QPushButton(Filter);
        btn_vague->setObjectName(QString::fromUtf8("btn_vague"));
        btn_vague->setMinimumSize(QSize(80, 60));
        btn_vague->setMaximumSize(QSize(80, 60));

        horizontalLayout_2->addWidget(btn_vague);

        btn_sharpen = new QPushButton(Filter);
        btn_sharpen->setObjectName(QString::fromUtf8("btn_sharpen"));
        btn_sharpen->setMinimumSize(QSize(80, 60));
        btn_sharpen->setMaximumSize(QSize(80, 60));

        horizontalLayout_2->addWidget(btn_sharpen);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(Filter);

        QMetaObject::connectSlotsByName(Filter);
    } // setupUi

    void retranslateUi(QDialog *Filter)
    {
        Filter->setWindowTitle(QCoreApplication::translate("Filter", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        open->setText(QCoreApplication::translate("Filter", "\346\211\223\345\274\200", nullptr));
        btn_reverse->setText(QCoreApplication::translate("Filter", "\345\217\215\350\211\262", nullptr));
        btn_grey->setText(QCoreApplication::translate("Filter", "\347\201\260\345\272\246", nullptr));
        btn_cool->setText(QCoreApplication::translate("Filter", "\345\206\267\350\211\262", nullptr));
        btn_warm->setText(QCoreApplication::translate("Filter", "\346\232\226\350\211\262", nullptr));
        btn_saveas->setText(QCoreApplication::translate("Filter", "\345\217\246\345\255\230\344\270\272", nullptr));
        btn_soften->setText(QCoreApplication::translate("Filter", "\346\237\224\345\214\226", nullptr));
        btn_old->setText(QCoreApplication::translate("Filter", "\350\200\201\347\205\247\347\211\207", nullptr));
        btn_vague->setText(QCoreApplication::translate("Filter", "\346\250\241\347\263\212", nullptr));
        btn_sharpen->setText(QCoreApplication::translate("Filter", "\351\224\220\345\214\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Filter: public Ui_Filter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTER_H
