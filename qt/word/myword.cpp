#include "myword.h"
#include "ui_myword.h"
#include <QMessageBox>
MyWord::MyWord(Controler *control,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyWord)
{
    ui->setupUi(this);
    this->control = control;
    this->ui->btn_word_delete->hide();
    this->ui->lb_word1->setText("");
    this->ui->lb_word2->setText("");
    this->ui->lb_word3->setText("");
    this->ui->lb_word4->setText("");
    this->ui->lb_word5->setText("");
    this->ui->lb_word_definition->hide();
    int pre_errno;
    pre_errno = this->control->load_my_word_to_file(this->control->control_user_id);
    if(pre_errno == 0){
        pre_errno = this->control->get_data_from_file(this->control->output_file_location);
        if(pre_errno == 0){
            this->myword_start_seq = 0;             //Start at 0
            this->myword_cur_page = 1;              //The first page
            this->show_my_word();
        }
    }
}

void MyWord::show_my_word(){
    int remain = (this->control->my_word_notebook_num - (this->myword_cur_page - 1) * PAGE_SIZE);
    int num;
    if((remain / PAGE_SIZE) > 0){                   //Not at the end page
        num = PAGE_SIZE;
    }else{
        num = remain % PAGE_SIZE;
    }
    this->flush_qlist();                            //Clear the List
    for(int i=this->myword_start_seq,j=0;j < num;i++,j++){
        this->my_word_field = this->control->word_data.at(i).split("\t",QString::SkipEmptyParts);
        this->my_word_id << this->my_word_field.at(0);
        this->my_word << this->my_word_field.at(1);
    }
    this->ui->lb_word1->setText("");
    this->ui->lb_word2->setText("");
    this->ui->lb_word3->setText("");
    this->ui->lb_word4->setText("");
    this->ui->lb_word5->setText("");
    switch(num){
    case 1:
        this->ui->lb_word1->setText(my_word.at(0));
        break;
    case 2:
        this->ui->lb_word1->setText(my_word.at(0));
        this->ui->lb_word2->setText(my_word.at(1));
        break;
    case 3:
        this->ui->lb_word1->setText(my_word.at(0));
        this->ui->lb_word2->setText(my_word.at(1));
        this->ui->lb_word3->setText(my_word.at(2));
        break;
    case 4:
        this->ui->lb_word1->setText(my_word.at(0));
        this->ui->lb_word2->setText(my_word.at(1));
        this->ui->lb_word3->setText(my_word.at(2));
        this->ui->lb_word4->setText(my_word.at(3));
        break;
    case 5:
        this->ui->lb_word1->setText(my_word.at(0));
        this->ui->lb_word2->setText(my_word.at(1));
        this->ui->lb_word3->setText(my_word.at(2));
        this->ui->lb_word4->setText(my_word.at(3));
        this->ui->lb_word5->setText(my_word.at(4));
         break;
    }

}

void MyWord::flush_qlist(){
    this->my_word.clear();
    this->my_word_id.clear();
}

MyWord::~MyWord()
{
    delete ui;
}

void MyWord::on_btn_word_next_clicked()
{
    int total_pages = this->control->my_word_notebook_num / PAGE_SIZE + 1;
    if(this->myword_cur_page < total_pages){
        this->myword_cur_page++;
        this->myword_start_seq += PAGE_SIZE;
        this->ui->lb_word1->setDisabled(false);
        this->ui->lb_word2->setDisabled(false);
        this->ui->lb_word3->setDisabled(false);
        this->ui->lb_word4->setDisabled(false);
        this->ui->lb_word5->setDisabled(false);
        this->show_my_word();
    }else{
        QMessageBox msg;
        msg.warning(this,"Warning","At end",QMessageBox::Ok);
    }

}

void MyWord::on_lb_word1_clicked()
{
    QString wd = this->ui->lb_word1->text();
    if(!wd.isEmpty()){
        QString wd_id = this->my_word_id.at(this->my_word.indexOf(wd));         //get the word id
        QString wd_def = this->control->search_word_def(wd_id);
        this->cur_word_id = wd_id;
        this->cur_label_str = 1;
        this->ui->lb_word_definition->show();
        this->ui->lb_word_definition->setText(wd_def);
        this->ui->btn_word_delete->show();
    }

}

void MyWord::on_lb_word2_clicked()
{
    QString wd = this->ui->lb_word2->text();
    if(!wd.isEmpty()){
        QString wd_id = this->my_word_id.at(this->my_word.indexOf(wd));         //get the word id
        QString wd_def = this->control->search_word_def(wd_id);
        this->cur_word_id = wd_id;
        this->cur_label_str = 2;
        this->ui->lb_word_definition->show();
        this->ui->lb_word_definition->setText(wd_def);
        this->ui->btn_word_delete->show();
    }
}

void MyWord::on_lb_word3_clicked()
{
    QString wd = this->ui->lb_word3->text();
    if(!wd.isEmpty()){
        QString wd_id = this->my_word_id.at(this->my_word.indexOf(wd));         //get the word id
        QString wd_def = this->control->search_word_def(wd_id);
        this->cur_word_id = wd_id;
        this->cur_label_str = 3;
        this->ui->lb_word_definition->show();
        this->ui->lb_word_definition->setText(wd_def);
        this->ui->btn_word_delete->show();
    }
}

void MyWord::on_lb_word4_clicked()
{
    QString wd = this->ui->lb_word4->text();
    if(!wd.isEmpty()){
        QString wd_id = this->my_word_id.at(this->my_word.indexOf(wd));         //get the word id
        QString wd_def = this->control->search_word_def(wd_id);
        this->cur_word_id = wd_id;
        this->cur_label_str = 4;
        this->ui->lb_word_definition->show();
        this->ui->lb_word_definition->setText(wd_def);
        this->ui->btn_word_delete->show();
    }
}

void MyWord::on_lb_word5_clicked()
{
    QString wd = this->ui->lb_word5->text();
    if(!wd.isEmpty()){
        QString wd_id = this->my_word_id.at(this->my_word.indexOf(wd));         //get the word id
        QString wd_def = this->control->search_word_def(wd_id);
        this->cur_word_id = wd_id;
        this->cur_label_str = 5;
        this->ui->lb_word_definition->show();
        this->ui->lb_word_definition->setText(wd_def);
        this->ui->btn_word_delete->show();
    }
}

void MyWord::on_btn_word_delete_clicked()
{
    QMessageBox msg;
    this->control->delete_my_word_from_note(this->cur_word_id);
    if(this->control->my_program_errno == 0){
        msg.information(this,tr("Success"),tr("Delete successfully!"),QMessageBox::Ok);

        switch(this->cur_label_str){
        case 1:
            this->ui->lb_word1->setDisabled(true);
            break;
        case 2:
            this->ui->lb_word2->setDisabled(true);
            break;
        case 3:
            this->ui->lb_word3->setDisabled(true);
            break;
        case 4:
            this->ui->lb_word4->setDisabled(true);
            break;
        case 5:
            this->ui->lb_word5->setDisabled(true);
            break;
        }
     }else{
            QString info = "Error code: ";
            info += this->control->my_program_errno;
            msg.critical(this,"Error",info,QMessageBox::Ok);
     }
}
