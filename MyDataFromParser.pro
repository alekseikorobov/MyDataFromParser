#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T08:10:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDataFromParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        worker.cpp \
        libconnect.cpp \
        mysettings.cpp

HEADERS  += mainwindow.h \
            worker.h \
            libconnect.h \
            mysettings.h

FORMS    += mainwindow.ui

RESOURCES += \
    res/res.qrc
