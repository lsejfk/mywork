#include "controler.h"
#include "clogin_register.h"
#include "QMessageBox"
#include <QString>
#include "login.h"
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QDebug>
Controler::Controler()
{
    if((this->my_program_errno = connectMysql())){
        this->connect_status = MYSQL_CONNECT_STATUS_OFF;
    }else{
        this->connect_status = MYSQL_CONNECT_STATUS_ON;
    }
    this->login_status = LOGIN_STATUS_OFF;
    this->start_id = 501;

}

Controler::~Controler(){
    this->connect_status = MYSQL_CONNECT_STATUS_OFF;
    disconnectMysql();
}

//Check Login
int Controler::check_login(char *account,char *password){
    if(this->connect_status == 0){          //Mysql server connected
        return isAccountValid(account,password);
    }else{
        return LOGIN_ERROR;
    }
}

//Do the login option
int Controler::login(const char *account){
    return setLoginStatus(account,1);
}

//Do register option
int Controler::register_option(const char *account,const char *password,const char *nickname,char sex){
    return c_register(account,password,nickname,sex);
}

//Do the layout option
int Controler::layout(char *account){
    return setLoginStatus(account,0);
}

//Get number per day
int Controler::get_number_per_day(QString accout_user_id){
    char error[64];
    char *user;
    QByteArray qba_user_id = accout_user_id.toLatin1();
    user = qba_user_id.data();
    int num = get_num_per_day(user,error);
    this->my_program_error = QString(QLatin1String(error));
    if(num != 0){
        this->my_program_errno = num;
    }
    return num;
}
//Load data from database to file
int Controler::load_data_to_file(QString qs_user_id,int int_num){
    char output_file[64];
    char error[64];
    QString qs_num = QString::number(int_num);
    QByteArray qba_num = qs_num.toLatin1();
    QByteArray qba_user_id = qs_user_id.toLatin1();
    char *str_num = qba_num.data();
    char *str_user_id = qba_user_id.data();
    int load_errno = memorize_word_data_input(str_user_id,str_num,output_file,error);
    this->my_program_errno = load_errno;
    this->output_file_location = QString(QLatin1String(output_file));
    this->my_program_error = QString(QLatin1String(error));
    return load_errno;
}

//Load data from database to file
int Controler::load_my_word_to_file(QString user_id){
    char output_file[64];
    QByteArray qba_user_id = user_id.toLatin1();
    char *str_user_id = qba_user_id.data();
    int number;
    this->my_program_errno = c_select_word_notebook(str_user_id,&number,output_file);
    if(this->my_program_errno == 0){
        this->output_file_location = QString(QLatin1String(output_file));
        this->my_word_notebook_num = number;
    }else{
        this->my_program_error = "Error code: ";
        this->my_program_error += QString::number(this->my_program_errno);
    }
    return this->my_program_errno;
}

//Get data from file,return 0 if succeed
int Controler::get_data_from_file(QString filepath){
    QFile data_file(filepath);
    if(!data_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return 1;
    }
    QTextStream in(&data_file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      this->word_data << line;
    }
    data_file.flush();
    data_file.close();
    data_file.remove();
    return 0;
}

int Controler::record_personal_footstep(QString user_id,int num_per_day){
    QByteArray qba_user_id = user_id.toLatin1();
    char *str_user_id = qba_user_id.data();
    char str_err[64];
    this->my_program_errno = record_footstep(str_user_id,num_per_day,str_err);
    return this->my_program_errno;
}

int Controler::set_my_plan(QString str_num){
    int num_per_day_int = str_num.toInt();
    QByteArray qba_account = this->control_user_id.toLatin1();
    char *str_account = qba_account.data();
    this->my_program_errno = c_set_plan(str_account,num_per_day_int);
    return this->my_program_errno;
}

int Controler::set_word_num(QString user_id){
    QByteArray qba_user_id = user_id.toLatin1();
    char *str_user_id = qba_user_id.data();
    int total,remain;
    total = 0;
    remain = 0;
    this->my_program_errno = c_get_record(str_user_id,&total,&remain);
    this->word_rem_total = total;
    this->word_remain = remain;
    return this->my_program_errno;
}

//Add word to my notebook
void Controler::add_to_my_word(QString user_id, QString word_id, QString str_word){
    QByteArray qba_user_id = user_id.toLatin1();
    QByteArray qba_str_word = str_word.toLatin1();
    QByteArray qba_word_id = word_id.toLatin1();
    char *str_user_id = qba_user_id.data();
    char *strword = qba_str_word.data();
    char *str_word_id = qba_word_id.data();
    this->my_program_errno = c_add_my_word(str_user_id,str_word_id,strword);
}

//Get word definition
QString Controler::search_word_def(QString wd_id){
    QByteArray qba_wd_id = wd_id.toLatin1();
    char *str_wd_id = qba_wd_id.data();
    char def[100];
    this->my_program_errno = c_get_word_def(str_wd_id,def);
    if(this->my_program_errno == 0){
        return QString::fromUtf8(def);
    }else{
        this->my_program_error = "Error code:";
        this->my_program_error += this->my_program_errno;
        return NULL;
    }
}

//Delete word in notebook
void Controler::delete_my_word_from_note(QString word_id){
    QByteArray qba_word_id = word_id.toLatin1();
    char *str_word_id = qba_word_id.data();
    this->my_program_errno = c_delete_my_word_from_note(str_word_id);
}


