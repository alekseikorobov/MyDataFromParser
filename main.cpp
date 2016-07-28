#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
int main(int argc, char *argv[])
{
    qDebug() << QSqlDatabase::drivers();
    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    //QTextCodec::setCodecForTr(codec);
    //QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
