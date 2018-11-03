#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QButtonGroup>
#include "mainwindow.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(Controler *control,QWidget *parent = 0);
    QButtonGroup *qbtng_radio_sex;
    ~Register();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    MainWindow *re_win;
    Controler *control;
};

#endif // REGISTER_H
