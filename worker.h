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
signals:

public slots:

    void Scan();
signals:
    void onComplit();
};

#endif // WORKER_H
