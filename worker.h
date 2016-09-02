#ifndef WORKER_H
#define WORKER_H


#include <QObject>
#include <QtGui>
#include "libconnect.h"

#define string QString

class data{
public:
    data(QString key,QString val){
        this->key = key;
        this->val = val;
    }
    QString key;
    QString val;
};

class worker : public QObject
{
    Q_OBJECT
    QString myReplaceMask(QString str);
    void init();
    QString myReplace(QString str);
    int findHar(QString str);
    QString getStringJoinVal();
    QString getStringJoinKey();
    QString getKey(QString str);
    QString getCratHaract();
    bool appendHaract();
    bool append_Full_Haract();
public:
    explicit worker(QObject *parent = 0);
    LibConnect *db;
    QString seporator;
    QStringList sl;
    QStringList listNot;
    QStringList listNotHaract;
    QStringList listError;
    QString pathSave;
    bool DeleteEmptyCat();

    QMap<QString,QString> q;
    QList<data> har;
    QStringList fullhar;
signals:

public slots:

    void Scan();
signals:
    void onComplit();
};

#endif // WORKER_H
