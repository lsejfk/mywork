/********************************************************************************
** Form generated from reading UI file 'myplan.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPLAN_H
#define UI_MYPLAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyPlan
{
public:
    QPushButton *btn_modify;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *le_plan;

    void setupUi(QDialog *MyPlan)
    {
        if (MyPlan->objectName().isEmpty())
            MyPlan->setObjectName(QStringLiteral("MyPlan"));
        MyPlan->resize(370, 220);
        MyPlan->setMinimumSize(QSize(370, 220));
        MyPlan->setMaximumSize(QSize(370, 220));
        btn_modify = new QPushButton(MyPlan);
        btn_modify->setObjectName(QStringLiteral("btn_modify"));
        btn_modify->setGeometry(QRect(260, 180, 89, 25));
        layoutWidget = new QWidget(MyPlan);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 50, 311, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        le_plan = new QLineEdit(layoutWidget);
        le_plan->setObjectName(QStringLiteral("le_plan"));

        verticalLayout->addWidget(le_plan);


        retranslateUi(MyPlan);

        QMetaObject::connectSlotsByName(MyPlan);
    } // setupUi

    void retranslateUi(QDialog *MyPlan)
    {
        MyPlan->setWindowTitle(QApplication::translate("MyPlan", "My plan", nullptr));
        btn_modify->setText(QApplication::translate("MyPlan", "Modify", nullptr));
        label->setText(QApplication::translate("MyPlan", "Plan to memorize number of word per day:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyPlan: public Ui_MyPlan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPLAN_H
