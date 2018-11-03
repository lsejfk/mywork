#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T20:58:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = word
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#QMAKE_LFLAGS += -ldl

SOURCES += \
        main.cpp \
        login.cpp \
    mainwindow.cpp \
    myword.cpp \
    myplan.cpp \
    myrecord.cpp \
    controler.cpp \
    register.cpp
LIBS += ~/learnfile/qt/word/c_module/libc_program_source.so
#LIBS += /usr/local/include/mysql/lib/libmysqlclient.so
HEADERS += \
        login.h \
    mainwindow.h \
    myword.h \
    myplan.h \
    myrecord.h \
    controler.h \
    clogin_register.h \
    register.h

FORMS += \
        login.ui \
    mainwindow.ui \
    myword.ui \
    myplan.ui \
    myrecord.ui \
    register.ui

