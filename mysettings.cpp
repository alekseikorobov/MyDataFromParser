#include "mysettings.h"
#include <QMetaProperty>
#include <QMetaMethod>
#include <QMetaClassInfo>
#include <QDebug>

mySettings::mySettings(QObject *param):QObject(param)
{
}

mySettings::mySettings(const QString &path)
{
    this->path = path;
    ReadSettings();
}

void mySettings::ReadSettings()
{
    QSettings *settings = new QSettings(path,QSettings::IniFormat);

//    ipStart = settings->value("IpScan/ipStart").toString();
//    ipEnd = settings->value("IpScan/ipEnd").toString();


    HostName = settings->value("db/HostName").toString();
    Port = settings->value("db/Port").toInt();
    DataBase = settings->value("db/DataBase").toString();
    UserName = settings->value("db/UserName").toString();
    Password = settings->value("db/Password").toString();

//    NetworkOS = settings->value("AllConf/NetworkOS").toString();
}

void mySettings::WriteSettings()
{
    QSettings *settings = new QSettings(path,QSettings::IniFormat);

//    settings->setValue("IpScan/ipStart", ipStart);
//    settings->setValue("IpScan/ipEnd", ipEnd);

    settings->setValue("db/HostName", HostName);
    settings->setValue("db/Port", Port);
    settings->setValue("db/DataBase", DataBase);
    settings->setValue("db/UserName", UserName);
    settings->setValue("db/Password", Password);

//    settings->setValue("AllConf/NetworkOS",NetworkOS);

    settings->sync();
}
