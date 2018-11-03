#ifndef MYRECORD_H
#define MYRECORD_H

#include <QDialog>
#include "controler.h"
namespace Ui {
class MyRecord;
}

class MyRecord : public QDialog
{
    Q_OBJECT

public:
    explicit MyRecord(Controler *control,QWidget *parent = 0);
    ~MyRecord();

private:
    Ui::MyRecord *ui;
    Controler *control;
};

#endif // MYRECORD_H
