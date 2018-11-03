/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *le_account;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *le_password;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_login;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btn_register;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(450, 500);
        Login->setMinimumSize(QSize(450, 500));
        Login->setMaximumSize(QSize(450, 500));
        verticalLayout_4 = new QVBoxLayout(Login);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label = new QLabel(Login);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans CJK SC Medium"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        verticalLayout_4->addWidget(label);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        le_account = new QLineEdit(Login);
        le_account->setObjectName(QStringLiteral("le_account"));

        horizontalLayout->addWidget(le_account);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 7);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        le_password = new QLineEdit(Login);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(le_password);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 7);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btn_login = new QPushButton(Login);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setStyleSheet(QStringLiteral("background-color: rgb(245, 121, 0);"));

        horizontalLayout_3->addWidget(btn_login);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 10);
        horizontalLayout_3->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        btn_register = new QPushButton(Login);
        btn_register->setObjectName(QStringLiteral("btn_register"));
        btn_register->setStyleSheet(QStringLiteral("background-color: rgb(138, 226, 52);"));

        horizontalLayout_4->addWidget(btn_register);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 10);
        horizontalLayout_4->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 3);
        verticalLayout_2->setStretch(2, 2);

        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 2);
        verticalLayout_3->setStretch(2, 3);

        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 2);
        verticalLayout_4->setStretch(2, 6);
        verticalLayout_4->setStretch(3, 1);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", nullptr));
        label->setText(QApplication::translate("Login", "LOGIN", nullptr));
        label_2->setText(QApplication::translate("Login", "Account:", nullptr));
        le_account->setText(QString());
        le_account->setPlaceholderText(QApplication::translate("Login", "please input your account", nullptr));
        label_3->setText(QApplication::translate("Login", "Password:", nullptr));
        le_password->setPlaceholderText(QApplication::translate("Login", "please input your password", nullptr));
        btn_login->setText(QApplication::translate("Login", "Login", nullptr));
        btn_register->setText(QApplication::translate("Login", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
