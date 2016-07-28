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
    QStringList sl;
    QStringList listNot;
    QStringList listError;
    QString pathSave;
signals:

public slots:

    void Scan();
signals:
    void onComplit();
};

#endif // WORKER_H
