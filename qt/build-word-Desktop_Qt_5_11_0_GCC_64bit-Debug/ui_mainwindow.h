/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMy_words;
    QAction *actionMy_plan;
    QAction *actionMy_records;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *gb_word;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lb_phonetic_2;
    QLabel *lb_definition;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *lb_ex_en;
    QLabel *lb_ex_zh;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *mw_btn_back;
    QSpacerItem *horizontalSpacer;
    QPushButton *mw_btn_add;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *mw_btn_next;
    QMenuBar *menubar;
    QMenu *menuMemorize;
    QMenu *menuHome;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(750, 650);
        MainWindow->setMinimumSize(QSize(750, 649));
        MainWindow->setMaximumSize(QSize(100000, 100000));
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionMy_words = new QAction(MainWindow);
        actionMy_words->setObjectName(QStringLiteral("actionMy_words"));
        actionMy_plan = new QAction(MainWindow);
        actionMy_plan->setObjectName(QStringLiteral("actionMy_plan"));
        actionMy_records = new QAction(MainWindow);
        actionMy_records->setObjectName(QStringLiteral("actionMy_records"));
        actionMy_records->setCheckable(false);
        actionMy_records->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gb_word = new QGroupBox(centralwidget);
        gb_word->setObjectName(QStringLiteral("gb_word"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gb_word->sizePolicy().hasHeightForWidth());
        gb_word->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        gb_word->setFont(font);
        gb_word->setStyleSheet(QLatin1String("border-color: rgb(206, 92, 0);\n"
"background-color: rgb(186, 189, 182);"));
        layoutWidget = new QWidget(gb_word);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 641, 121));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lb_phonetic_2 = new QLabel(layoutWidget);
        lb_phonetic_2->setObjectName(QStringLiteral("lb_phonetic_2"));
        QFont font1;
        font1.setPointSize(14);
        lb_phonetic_2->setFont(font1);
        lb_phonetic_2->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(lb_phonetic_2);

        lb_definition = new QLabel(layoutWidget);
        lb_definition->setObjectName(QStringLiteral("lb_definition"));
        lb_definition->setFont(font1);

        verticalLayout_2->addWidget(lb_definition);

        layoutWidget1 = new QWidget(gb_word);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 220, 641, 201));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        QFont font2;
        font2.setPointSize(16);
        label->setFont(font2);
        label->setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207);"));

        verticalLayout->addWidget(label);

        lb_ex_en = new QLabel(layoutWidget1);
        lb_ex_en->setObjectName(QStringLiteral("lb_ex_en"));
        QFont font3;
        font3.setPointSize(13);
        lb_ex_en->setFont(font3);
        lb_ex_en->setStyleSheet(QLatin1String("border-color: rgb(46, 52, 54);\n"
"background-color: rgb(250, 216, 216);"));

        verticalLayout->addWidget(lb_ex_en);

        lb_ex_zh = new QLabel(layoutWidget1);
        lb_ex_zh->setObjectName(QStringLiteral("lb_ex_zh"));
        lb_ex_zh->setFont(font3);
        lb_ex_zh->setStyleSheet(QStringLiteral("background-color: rgb(192, 182, 240);"));

        verticalLayout->addWidget(lb_ex_zh);


        verticalLayout_3->addWidget(gb_word);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        mw_btn_back = new QPushButton(centralwidget);
        mw_btn_back->setObjectName(QStringLiteral("mw_btn_back"));
        mw_btn_back->setStyleSheet(QStringLiteral("background-color: rgb(252, 175, 62);"));

        horizontalLayout->addWidget(mw_btn_back);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mw_btn_add = new QPushButton(centralwidget);
        mw_btn_add->setObjectName(QStringLiteral("mw_btn_add"));
        mw_btn_add->setStyleSheet(QStringLiteral("background-color: rgb(252, 233, 79);"));

        horizontalLayout->addWidget(mw_btn_add);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        mw_btn_next = new QPushButton(centralwidget);
        mw_btn_next->setObjectName(QStringLiteral("mw_btn_next"));
        mw_btn_next->setStyleSheet(QStringLiteral("background-color: rgb(138, 226, 52);"));

        horizontalLayout->addWidget(mw_btn_next);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 3);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 3);

        verticalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 22));
        menuMemorize = new QMenu(menubar);
        menuMemorize->setObjectName(QStringLiteral("menuMemorize"));
        menuHome = new QMenu(menubar);
        menuHome->setObjectName(QStringLiteral("menuHome"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMemorize->menuAction());
        menubar->addAction(menuHome->menuAction());
        menuHome->addAction(actionMy_words);
        menuHome->addAction(actionMy_plan);
        menuHome->addAction(actionMy_records);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionMy_words->setText(QApplication::translate("MainWindow", "My words", nullptr));
        actionMy_plan->setText(QApplication::translate("MainWindow", "My plan", nullptr));
        actionMy_records->setText(QApplication::translate("MainWindow", "My records", nullptr));
        gb_word->setTitle(QApplication::translate("MainWindow", "Word", nullptr));
        lb_phonetic_2->setText(QApplication::translate("MainWindow", "Phonetic", nullptr));
        lb_definition->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QApplication::translate("MainWindow", "Example", nullptr));
        lb_ex_en->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lb_ex_zh->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        mw_btn_back->setText(QApplication::translate("MainWindow", "Back", nullptr));
        mw_btn_add->setText(QApplication::translate("MainWindow", "Add", nullptr));
        mw_btn_next->setText(QApplication::translate("MainWindow", "Next", nullptr));
        menuMemorize->setTitle(QApplication::translate("MainWindow", "Memorize", nullptr));
        menuHome->setTitle(QApplication::translate("MainWindow", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
