#ifndef CONTROLER_H
#define CONTROLER_H
//-----------define mysql server connect status-------------
#define MYSQL_CONNECT_STATUS_ON 0
#define MYSQL_CONNECT_STATUS_OFF 1
//-----------define login status--------------------------
#define LOGIN_STATUS_ON 1
#define LOGIN_STATUS_OFF 0

//-----------define isAccountValid() return value----------
#define LOGIN_ERROR -1
#define LOGIN_INVALID 0
#define LOGIN_SUCCESS 1

//----------define setLoginStatus() return value-----------
#define SET_LOGIN_STATUS_SUCCESS 0
#define SET_LOGIN_STATUS_FAILED 1

//----------define memorizing word struct------------------
/*
typedef struct _word{
    int word_id;
    char word[32];
    char phonetic[32];
    char definition[64];
    char example_en[320];
    char example_zh[320];
}StructWord;
*/
#include <QTextStream>
#include <QList>

class Controler
{
public:
    Controler();
    ~Controler();
    int check_login(char *account,char *password);
    int login(const char *account);
    int layout(char *account);
    int register_option(const char *account,const char *password,const char *nickname,char sex);
    int get_data_from_file(QString filepath);
    int get_number_per_day(QString user_id);
    int load_data_to_file(QString user_id,int num);
    int load_my_word_to_file(QString user_id);
    int record_personal_footstep(QString user_id,int num_per_day);
    int set_my_plan(QString str_num);
    int set_word_num(QString user_id);
    void add_to_my_word(QString id,QString word_id,QString word);
    QString search_word_def(QString wd_id);
    void delete_my_word_from_note(QString word_id);
public:
    int connect_status;
    int login_status;
    QString control_user_id;
    int my_program_errno;
    QString output_file_location;
    int my_word_notebook_num;
    QString my_program_error;
    QList<QString> word_data;
    int word_rem_total;
    int word_remain;
private:
    int start_id;
};

#endif // CONTROLER_H
