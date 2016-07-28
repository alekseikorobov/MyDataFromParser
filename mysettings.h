#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QMetaObject>

class mySettings: public QObject
{
    Q_OBJECT
public:
    explicit mySettings(QObject *param=0);
    explicit mySettings(const QString &path);
    void ReadSettings();
    void WriteSettings();
    QString path;

    QString ipStart,ipEnd;

    //настройки базы данных
    QString HostName,UserName, Password,DataBase;
    int Port;

    //общие настройки
    QString NetworkOS;
};

#endif // MYSETTINGS_H
