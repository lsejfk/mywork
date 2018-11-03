/********************************************************************************
** Form generated from reading UI file 'myrecord.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYRECORD_H
#define UI_MYRECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyRecord
{
public:
    QCalendarWidget *calendarWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lb_total;
    QLabel *label_2;
    QLabel *lb_remain;

    void setupUi(QDialog *MyRecord)
    {
        if (MyRecord->objectName().isEmpty())
            MyRecord->setObjectName(QStringLiteral("MyRecord"));
        MyRecord->resize(645, 340);
        MyRecord->setMinimumSize(QSize(645, 340));
        MyRecord->setMaximumSize(QSize(645, 340));
        calendarWidget = new QCalendarWidget(MyRecord);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(100, 30, 456, 171));
        layoutWidget = new QWidget(MyRecord);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 270, 471, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(252, 175, 62);"));

        horizontalLayout->addWidget(label);

        lb_total = new QLabel(layoutWidget);
        lb_total->setObjectName(QStringLiteral("lb_total"));
        lb_total->setFont(font);
        lb_total->setStyleSheet(QStringLiteral("color: rgb(243, 125, 125);"));

        horizontalLayout->addWidget(lb_total);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: rgb(115, 210, 22);"));

        horizontalLayout->addWidget(label_2);

        lb_remain = new QLabel(layoutWidget);
        lb_remain->setObjectName(QStringLiteral("lb_remain"));
        lb_remain->setFont(font);
        lb_remain->setStyleSheet(QStringLiteral("color: rgb(119, 163, 93);"));

        horizontalLayout->addWidget(lb_remain);


        retranslateUi(MyRecord);

        QMetaObject::connectSlotsByName(MyRecord);
    } // setupUi

    void retranslateUi(QDialog *MyRecord)
    {
        MyRecord->setWindowTitle(QApplication::translate("MyRecord", "Dialog", nullptr));
        label->setText(QApplication::translate("MyRecord", "Total:", nullptr));
        lb_total->setText(QApplication::translate("MyRecord", "50", nullptr));
        label_2->setText(QApplication::translate("MyRecord", "Remain:", nullptr));
        lb_remain->setText(QApplication::translate("MyRecord", "1000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyRecord: public Ui_MyRecord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYRECORD_H
