#include "login.h"
#include <QApplication>
#include "mainwindow.h"
#include "controler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controler control;
    Login w(&control);
    w.show();
//    if(w.getFlag() == 1){    //Login option
//        w.close();
//        MainWindow menu;
//        menu.show();
//    }else if(w.getFlag() == 0){
//        w.show();
//    }else if(w.getFlag() == 2){      //Register option
//        w.close();
//        //.....
//    }


    return a.exec();
}
