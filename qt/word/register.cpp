#include "register.h"
#include "ui_register.h"
#include "controler.h"
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QAbstractButton>
#include <QButtonGroup>
#include <iostream>
#include <string>
#include <mainwindow.h>
#include <QDebug>
Register::Register(Controler *control,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->control = control;
    this->re_win = NULL;
    this->qbtng_radio_sex = new QButtonGroup(this);
    this->qbtng_radio_sex->addButton(this->ui->radio_male,0);
    this->qbtng_radio_sex->addButton(this->ui->radio_female,1);
    this->qbtng_radio_sex->setExclusive(true);                //Set exclusive property
    this->qbtng_radio_sex->button(0)->setChecked(true);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    QString qs_account = this->ui->re_account->text();
    QString qs_nickname = this->ui->re_nickName->text();
    QString qs_password = this->ui->re_password->text();
    QString qs_sex = this->qbtng_radio_sex->checkedButton()->text();
    qDebug() << "hello";
    QMessageBox message;
    int length_account = qs_account.length();
    int length_password = qs_password.length();
    int length_nickname = qs_nickname.length();
    QString notice = "";
    if(length_account != 11){
         notice = "Notice:The length of account must be 11!\n";
    }
    if(length_password < 6 || length_password > 22){
        notice += "Notice:The length of password must between 6 and 22\n";
    }
    if(length_nickname <= 0 || length_nickname > 16){
        notice += "Notice:The length of nickname must between 0 to 16\n";
    }
    if(notice.length() != 0){               //There are some error in information the user input
        message.warning(this,tr("Notice"),notice,QMessageBox::Ok);
    }else{
        QString info = "Please confirm the follow information:\n";
        info += "Account:" + qs_account + "\n" + "password:" + qs_password + "\n"
                + "Nickname: " + qs_nickname + "\n" + "Sex:" + qs_sex;
        int ret = message.information(this,tr("Confirm"),info,QMessageBox::Cancel | QMessageBox::Ok);
        std::string str_account = qs_account.toStdString();
        std::string str_password = qs_password.toStdString();
        std::string str_nickname = qs_nickname.toStdString();
        const char *c_str_account = str_account.c_str();
        const char *c_str_password = str_password.c_str();
        const char *c_str_nickname = str_nickname.c_str();
        char sex;
        switch(ret){
        case 0x00000400:                    //Clicked Ok
            //QByteArray byte_account = qs_account.toLatin1();
            //QByteArray byte_password = qs_password.toLatin1();
            //char *str_account = byte_account.data();
            //char *str_password = byte_password.data();

            if(qs_sex == "male"){
                sex = 'm';
            }else{
                sex = 'f';
            }
            this->control->my_program_errno = this->control->register_option(c_str_account,c_str_password,c_str_nickname,sex);
            if(this->control->my_program_errno == 0){          //Success
                this->close();
                this->control->login_status = LOGIN_STATUS_ON;
                this->re_win = new MainWindow(this->control);
                this->re_win->user_id = qs_account;
                this->re_win->show();                   //Pop-up main window
            }
            break;
        case 0x00400000:                    //Clicked Cancel
            break;
        }
    }
}
