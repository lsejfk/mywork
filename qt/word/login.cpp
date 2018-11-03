#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "clogin_register.h"
#include "controler.h"
#include <QByteArray>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "register.h"
#include "controler.h"

Login::Login(Controler *control, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->flag = 0;         //There is no option
    this->word_wind = NULL;
    this->control = control;
}

Login::~Login()
{
    delete ui;
}

int Login::getFlag(){
    return this->flag;
}

void Login::on_btn_login_clicked()
{
    int login_flag;
    char *str_account,*strpassword;
    QByteArray be_account,be_password;

    //Transform Qstring to char *
    QString le_account = this->ui->le_account->text();
    QString le_password = this->ui->le_password->text();
    be_account = le_account.toLatin1();
    be_password = le_password.toLatin1();
    str_account = be_account.data();
    strpassword = be_password.data();

    //Check login
    login_flag = this->control->check_login(str_account,strpassword);
    QMessageBox msg;
    switch(login_flag){
        case LOGIN_ERROR:
        msg.critical(this,tr("Failed in login"),
                     tr("Account or password Error"),QMessageBox::Ok);
        break;
    case LOGIN_INVALID:
        msg.warning(this,tr("Failed in login"),
                    tr("Account is invalid"),QMessageBox::Ok);
        break;
    case LOGIN_SUCCESS:
        this->control->my_program_errno = this->control->login(str_account);
        if(this->control->my_program_errno == 0){         //login success
            this->control->login_status = LOGIN_STATUS_ON;
            this->control->control_user_id = le_account;
            this->word_wind = new MainWindow(this->control);
            this->word_wind->show();
            this->close();
        }else{
            QString error_str = "Error Code:" + this->control->my_program_errno;
            msg.critical(this,tr("Failed in login"),
                         error_str,QMessageBox::Ok);
        }
        break;
    }
}

void Login::on_btn_register_clicked()
{
    Register reg(this->control);
    reg.exec();
    this->close();
}
