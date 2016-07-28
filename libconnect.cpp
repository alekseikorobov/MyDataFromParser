#include "libconnect.h"

LibConnect::LibConnect()
{
//    db.setHostName("localhost");
//    //db.setDatabaseName("");
//    db.setUserName("root");
//    db.setPassword("123456");
//    db.setPort(3306);
}

LibConnect::LibConnect(QString HostName,QString Database, QString UserName, QString Password,int Port)
{
    this->HostName = HostName;
    this->Password = Password;
    this->UserName = UserName;
    this->Database = Database;
    this->Port = Port;
}

bool LibConnect::connect()
{
    lastError = "";
    this->db = QSqlDatabase::addDatabase("QMYSQL","mydb");
    if(this->HostName.isNull() || this->HostName.isEmpty() ){
        throw "Host не указан";
    }
    if(this->UserName.isNull() || this->UserName.isEmpty() ){
        throw "Пользователь не указан";
    }
    db.setHostName(this->HostName);
    db.setDatabaseName(this->Database);
    db.setUserName(this->UserName);
    db.setPassword(this->Password);
    db.setPort(this->Port);

    isConnect = db.open();
    if(!isConnect){
        QSqlError er = db.lastError();
        lastError = er.text();
    }
    else{
       this->query = new QSqlQuery(db);
    }
    return isConnect;
}

bool LibConnect::SQl_Script_From_File(const QString &path,QString &out_result)
{
    try{
        QFile file(path);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            out_result = "не удалось открыть файл для чтения";
            return false;
        }
        QString sql = "";
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            sql +=line + "\r\n";
        }
        if(!this->query){
            out_result = "Не удалось выполнить скрипт, подключение не выполенно!";
            return false;
        }
        bool isOk = this->query->exec(sql);
        if(!isOk){
            QSqlError er = this->db.lastError();
            out_result = "Не удалось выполнить скрипт, причина: - "+ er.text();
            this->addLog(out_result);
        }
        return isOk;
    }
    catch(...){
        qDebug()<<"3";
        out_result = "Не предвиденная ошибка";
        return false;
    }
}

bool LibConnect::exec(const QString &sql)
{
//    if(!this->query) qDebug() << "NULL";
//    if(!this->query->isActive()) qDebug() << "!Active";
//    if(!this->query->isForwardOnly()) qDebug() << "!ForwardOnly";
//    //if(!this->query->isNull()) qDebug() << "!Null";
//    if(!this->query->isSelect()) qDebug() << "!Select";
//    if(!this->query->isValid()) qDebug() << "!Valid";

    if(!this->query){
        this->lastError = "Не удалось выполнить запрос, подключение не выполенно!";
        return false;
    }
    bool isOk = this->query->exec(sql);
    if(!isOk){
        QSqlError er = this->db.lastError();
        this->addLog(er.text());
        this->lastError = er.text();
    }
    return isOk;
}
int LibConnect::Exists(const QString &tableName,const QString &pole,const QString &valu){
    ///0 - нет
    ///1 - есть
    ///2 - ошибка

    //this->query->value(0).
    try{
        QString s = QString("SELECT 1 FROM information_schema.tables WHERE table_name = '%1'").arg(
                    tableName);
        if(!this->exec(s)){
            return 2;
        }

        bool isOk = this->query->next() ;
        //qDebug() << this->query->value(0);
        if(!isOk){
            this->lastError = "таблица не существует";
            return 2;
        }
        QString sql = QString("select %2 from %1 where %2 = %3").arg(tableName,pole,valu);

        if(!this->exec(sql)){
            return 2;
        }
        isOk = this->query->next();
        return (int)isOk;
    }catch(...){
        QSqlError er = this->db.lastError();
        this->lastError = er.text();
        return 2;
    }
}

bool LibConnect::InsertLine(const QString &tableName,const QString &poles,const QString &valus){

    QString sql = QString("insert into %1(%2) values(%3);").arg(tableName,poles,valus);
    bool isOk = this->query->exec(sql);
    if(!isOk){
        QSqlError er = this->db.lastError();
        this->addLog(er.text());
        this->lastError = er.text();
    }
    return isOk;
}

void LibConnect::addLog(const QString &text)
{
    qDebug()<<text;
}
