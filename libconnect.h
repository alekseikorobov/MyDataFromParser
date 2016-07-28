#ifndef LIBCONNECT_H
#define LIBCONNECT_H

//#include "libconnect_global.h"
#include <QDebug>
#include <QtSql>

class  LibConnect //LIBCONNECTSHARED_EXPORT
{

public:
    LibConnect();    
    LibConnect(QString HostName,QString Database,QString UserName,QString Password,int Port);//конструктор с указанием подключения

    bool connect(); // подключение к базе, и инициализация переменной query для запросов
    bool isConnect;
    bool SQl_Script_From_File(const QString &path,QString &out_result);    //установка базы данных их указанного файла sql запроса (так же для удаления базы данных)

    //запросы

    //существует ли запись по данному запросу
    bool Any(const QString &sql);
    //выполнение без возврата результата
    bool exec(const QString &sql);

    void addLog(const QString &text);
    QString lastError;
    bool InsertLine(const QString &tableName, const QString &poles, const QString &valus);
    int Exists(const QString &tableName, const QString &pole, const QString &valu);

    QSqlQuery *query;                               //перменная для запросов

private:
    QSqlDatabase db;                                //подключение к базе данных

    QString HostName,UserName,Password,Database;     //подлючение
    int Port;                                       //порт
};

#endif // LIBCONNECT_H
