/********************************************************************************
** Form generated from reading UI file 'myword.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWORD_H
#define UI_MYWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWord
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *lb_word1;
    QCommandLinkButton *lb_word2;
    QCommandLinkButton *lb_word3;
    QCommandLinkButton *lb_word4;
    QCommandLinkButton *lb_word5;
    QLabel *lb_word_definition;
    QPushButton *btn_word_next;
    QPushButton *btn_word_delete;

    void setupUi(QDialog *MyWord)
    {
        if (MyWord->objectName().isEmpty())
            MyWord->setObjectName(QStringLiteral("MyWord"));
        MyWord->resize(517, 384);
        MyWord->setMinimumSize(QSize(0, 0));
        MyWord->setMaximumSize(QSize(1000, 600));
        MyWord->setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207);"));
        groupBox = new QGroupBox(MyWord);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 231, 271));
        QFont font;
        font.setPointSize(16);
        groupBox->setFont(font);
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 30, 246, 241));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lb_word1 = new QCommandLinkButton(widget);
        lb_word1->setObjectName(QStringLiteral("lb_word1"));
        QFont font1;
        font1.setPointSize(14);
        lb_word1->setFont(font1);
        lb_word1->setStyleSheet(QStringLiteral("background-color: rgb(192, 182, 240);"));

        verticalLayout->addWidget(lb_word1);

        lb_word2 = new QCommandLinkButton(widget);
        lb_word2->setObjectName(QStringLiteral("lb_word2"));
        lb_word2->setFont(font1);
        lb_word2->setStyleSheet(QStringLiteral("selection-background-color: rgb(192, 182, 240);"));

        verticalLayout->addWidget(lb_word2);

        lb_word3 = new QCommandLinkButton(widget);
        lb_word3->setObjectName(QStringLiteral("lb_word3"));
        lb_word3->setFont(font1);
        lb_word3->setStyleSheet(QStringLiteral("selection-background-color: rgb(119, 163, 93);"));

        verticalLayout->addWidget(lb_word3);

        lb_word4 = new QCommandLinkButton(widget);
        lb_word4->setObjectName(QStringLiteral("lb_word4"));
        lb_word4->setFont(font1);
        lb_word4->setStyleSheet(QStringLiteral("selection-background-color: rgb(229, 191, 191);"));

        verticalLayout->addWidget(lb_word4);

        lb_word5 = new QCommandLinkButton(widget);
        lb_word5->setObjectName(QStringLiteral("lb_word5"));
        lb_word5->setFont(font1);
        lb_word5->setStyleSheet(QStringLiteral("selection-background-color: rgb(250, 216, 216);"));

        verticalLayout->addWidget(lb_word5);

        lb_word_definition = new QLabel(MyWord);
        lb_word_definition->setObjectName(QStringLiteral("lb_word_definition"));
        lb_word_definition->setGeometry(QRect(300, 100, 161, 81));
        QFont font2;
        font2.setPointSize(13);
        lb_word_definition->setFont(font2);
        lb_word_definition->setStyleSheet(QStringLiteral("background-color: rgb(136, 138, 133);"));
        lb_word_definition->setWordWrap(true);
        btn_word_next = new QPushButton(MyWord);
        btn_word_next->setObjectName(QStringLiteral("btn_word_next"));
        btn_word_next->setGeometry(QRect(390, 330, 89, 25));
        btn_word_next->setStyleSheet(QStringLiteral("background-color: rgb(138, 226, 52);"));
        btn_word_delete = new QPushButton(MyWord);
        btn_word_delete->setObjectName(QStringLiteral("btn_word_delete"));
        btn_word_delete->setEnabled(true);
        btn_word_delete->setGeometry(QRect(390, 260, 89, 25));
        btn_word_delete->setStyleSheet(QStringLiteral("background-color: rgb(245, 121, 0);"));

        retranslateUi(MyWord);

        QMetaObject::connectSlotsByName(MyWord);
    } // setupUi

    void retranslateUi(QDialog *MyWord)
    {
        MyWord->setWindowTitle(QApplication::translate("MyWord", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("MyWord", "My word", nullptr));
        lb_word1->setText(QApplication::translate("MyWord", "hello", nullptr));
        lb_word2->setText(QApplication::translate("MyWord", "CommandLinkButton", nullptr));
        lb_word3->setText(QApplication::translate("MyWord", "CommandLinkButton", nullptr));
        lb_word4->setText(QApplication::translate("MyWord", "CommandLinkButton", nullptr));
        lb_word5->setText(QApplication::translate("MyWord", "CommandLinkButton", nullptr));
        lb_word_definition->setText(QApplication::translate("MyWord", "TextLabel", nullptr));
        btn_word_next->setText(QApplication::translate("MyWord", "Next", nullptr));
        btn_word_delete->setText(QApplication::translate("MyWord", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWord: public Ui_MyWord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWORD_H
