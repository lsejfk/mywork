#ifndef MYPLAN_H
#define MYPLAN_H

#include <QDialog>
#include "controler.h"
namespace Ui {
class MyPlan;
}

class MyPlan : public QDialog
{
    Q_OBJECT

public:
    explicit MyPlan(Controler *control,int num_per_day,QWidget *parent = 0);
    ~MyPlan();

private slots:
    void on_btn_modify_clicked();

private:
    Ui::MyPlan *ui;
    Controler *control;
};

#endif // MYPLAN_H
