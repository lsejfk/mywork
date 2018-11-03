#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include "controler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controler *control,QWidget *parent = 0);
    void show_word_in_mainwindow();
    ~MainWindow();

private slots:
    void on_actionMy_words_triggered();

    void on_actionMy_plan_triggered();

    void on_actionMy_records_triggered();

    void on_mw_btn_next_clicked();

    void on_mw_btn_back_clicked();

    void on_mw_btn_add_clicked();

private:
    Ui::MainWindow *ui;
    QList<QString> fields;
    int word_seq;
    Controler *control;
public:
    QString user_id;
    int num_per_day;
};

#endif // MAINWINDOW_H
