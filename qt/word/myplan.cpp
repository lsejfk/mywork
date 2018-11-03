#include "myplan.h"
#include "ui_myplan.h"
#include <QMessageBox>
MyPlan::MyPlan(Controler *control,int num_per_day,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyPlan)
{
    ui->setupUi(this);
    this->control = control;
    this->ui->le_plan->setPlaceholderText(QString::number(num_per_day));
}

MyPlan::~MyPlan()
{
    delete ui;
}

void MyPlan::on_btn_modify_clicked()
{
    QMessageBox msg;
    int errno_set = this->control->set_my_plan(this->ui->le_plan->text());
    if(errno_set == 0){ //Success
        msg.information(this,tr("Success"),tr("Set Success"),QMessageBox::Ok);
        this->close();
    }else{
        QString info = "Error code" + errno_set;
        msg.critical(this,tr("Error"),info,QMessageBox::Ok);
        this->close();
    }
}
