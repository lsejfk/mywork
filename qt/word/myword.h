#ifndef MYWORD_H
#define MYWORD_H
#define PAGE_SIZE 5
#include <QDialog>
#include <QList>
#include <QString>
#include "controler.h"
namespace Ui {
class MyWord;
}

class MyWord : public QDialog
{
    Q_OBJECT

public:
    explicit MyWord(Controler *control,QWidget *parent = 0);
    void show_my_word();
    void flush_qlist();
    QList<QString> my_word_field;
    ~MyWord();

private slots:
    void on_btn_word_next_clicked();

    void on_lb_word1_clicked();

    void on_lb_word2_clicked();

    void on_lb_word3_clicked();

    void on_lb_word4_clicked();

    void on_lb_word5_clicked();

    void on_btn_word_delete_clicked();

private:
    Ui::MyWord *ui;
    Controler *control;
    QList<QString> my_word_id;
    QList<QString> my_word;
    QString cur_word_id;
    int cur_label_str;
    int myword_start_seq;           //Start sequence
    int myword_cur_page;        //Current page
};

#endif // MYWORD_H
