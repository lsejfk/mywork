#include "myrecord.h"
#include "ui_myrecord.h"
MyRecord::MyRecord(Controler *control,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyRecord)
{
    ui->setupUi(this);
    this->control = control;
    this->control->set_word_num(this->control->control_user_id);
    this->ui->lb_total->setText(QString::number(this->control->word_rem_total));
    this->ui->lb_remain->setText(QString::number(this->control->word_remain));
    this->ui->calendarWidget->showToday();
}

MyRecord::~MyRecord()
{
    delete ui;
}
