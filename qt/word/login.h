#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "controler.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(Controler *control,QWidget *parent = 0);
    int getFlag();
    ~Login();

private slots:
    void on_btn_login_clicked();

    void on_btn_register_clicked();

private:
    Ui::Login *ui;
    MainWindow *word_wind;
    Controler *control;
    int flag;
};

#endif // LOGIN_H
