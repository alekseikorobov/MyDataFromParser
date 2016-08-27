#ifndef WORKER_H
#define WORKER_H


#include <QObject>
#include <QtGui>
#include "libconnect.h"

#define string QString

struct data{

};

class worker : public QObject
{
    Q_OBJECT
    QString myReplaceMask(QString str);
    void init();
    QString myReplace(QString str);
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
signals:

public slots:

    void Scan();
signals:
    void onComplit();
};

#endif // WORKER_H
