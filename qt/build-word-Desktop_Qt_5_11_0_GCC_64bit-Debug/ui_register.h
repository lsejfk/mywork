/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *re_account;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *re_password;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *re_nickName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QRadioButton *radio_male;
    QRadioButton *radio_female;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QStringLiteral("Register"));
        Register->resize(376, 269);
        pushButton = new QPushButton(Register);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 240, 111, 21));
        widget = new QWidget(Register);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 13, 351, 211));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        re_account = new QLineEdit(widget);
        re_account->setObjectName(QStringLiteral("re_account"));

        horizontalLayout->addWidget(re_account);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        re_password = new QLineEdit(widget);
        re_password->setObjectName(QStringLiteral("re_password"));
        re_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(re_password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        re_nickName = new QLineEdit(widget);
        re_nickName->setObjectName(QStringLiteral("re_nickName"));

        horizontalLayout_4->addWidget(re_nickName);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        radio_male = new QRadioButton(widget);
        radio_male->setObjectName(QStringLiteral("radio_male"));

        horizontalLayout_3->addWidget(radio_male);

        radio_female = new QRadioButton(widget);
        radio_female->setObjectName(QStringLiteral("radio_female"));

        horizontalLayout_3->addWidget(radio_female);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QApplication::translate("Register", "Register", nullptr));
        pushButton->setText(QApplication::translate("Register", "Register", nullptr));
        label_3->setText(QApplication::translate("Register", "Account:", nullptr));
        label_2->setText(QApplication::translate("Register", "Password:", nullptr));
        label_4->setText(QApplication::translate("Register", "Nick name:", nullptr));
        label->setText(QApplication::translate("Register", "Sex:", nullptr));
        radio_male->setText(QApplication::translate("Register", "male", nullptr));
        radio_female->setText(QApplication::translate("Register", "female", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
