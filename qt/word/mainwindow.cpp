#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myword.h"
#include "myplan.h"
#include "myrecord.h"
#include "controler.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(Controler *control, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->word_seq = 0;
    this->control = control;
    this->user_id = this->control->control_user_id;
    int pre_errno;
    this->num_per_day = this->control->get_number_per_day(this->user_id);
    pre_errno = this->control->load_data_to_file(this->user_id,this->num_per_day);
    if(pre_errno == 0){
        pre_errno = this->control->get_data_from_file(this->control->output_file_location);
        if(pre_errno == 0){
            this->show_word_in_mainwindow();
            this->word_seq++;
        }
    }
}


MainWindow::~MainWindow()
{
    QByteArray qba_user_id = this->user_id.toLatin1();
    char *userid = qba_user_id.data();
    this->control->layout(userid);
    delete ui;
}

void MainWindow::on_actionMy_words_triggered()
{
    MyWord dlg_word(this->control);
    dlg_word.exec();
}

void MainWindow::on_actionMy_plan_triggered()
{
    MyPlan dlg_plan(this->control,this->num_per_day);
    dlg_plan.exec();
}

void MainWindow::on_actionMy_records_triggered()
{
    MyRecord dlg_record(this->control);
    dlg_record.exec();
}

//Show word in MainWindow
void MainWindow::show_word_in_mainwindow(){
    this->fields = this->control->word_data.at(this->word_seq).split("\t",QString::SkipEmptyParts);
    //id,word,phonetic,definition,example_en,example_zh
    this->ui->gb_word->setTitle(this->fields.at(1));
    this->ui->lb_phonetic_2->setText(this->fields.at(2));
    this->ui->lb_definition->setText(this->fields.at(3));
    this->ui->lb_ex_en->setWordWrap(true);              //Set line wrap
    this->ui->lb_ex_zh ->setWordWrap(true);
    this->ui->lb_ex_en->setText((this->fields.at(4)));
    this->ui->lb_ex_zh->setText((this->fields.at(5)));
}


void MainWindow::on_mw_btn_next_clicked()
{
    QMessageBox msg;
    if(this->word_seq < this->control->word_data.size()){
        this->show_word_in_mainwindow();
        this->word_seq++;
    }else{
        this->control->record_personal_footstep(this->user_id,this->num_per_day);
        msg.warning(this,tr("Notice:"),
                     tr("At End!\nYou can change you plan at you plan page."),QMessageBox::Ok);
    }
}

void MainWindow::on_mw_btn_back_clicked()
{
    QMessageBox msg;
    if(this->word_seq > 0){
        this->word_seq--;
        this->show_word_in_mainwindow();
    }else{
        msg.warning(this,tr("Notice:"),
                     tr("At First!\n"),QMessageBox::Ok);
    }
}

void MainWindow::on_mw_btn_add_clicked()
{
    this->control->add_to_my_word(this->user_id,this->fields.at(0),this->fields.at(1));
    QMessageBox msg;
    if(this->control->my_program_errno == 0){
        msg.information(this,"Success","Success adding",QMessageBox::Ok);
    }else{
        QString err_info = "Failed in adding,error code:";
        err_info += QString::number(this->control->my_program_errno);
        msg.information(this,"Error",err_info,QMessageBox::Ok);
    }
}
