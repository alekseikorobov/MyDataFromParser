#include "mainwindow.h"
#include "ui_mainwindow.h"
#define stringList QStringList



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    QString path = "/home/alekse/project/qt/fff2.csv";

//    QFile file(path);
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
//        qDebug() << "not4";
//        return;
//    }

//    QTextStream out(&file);
//    out.setCodec("UTF-8");
//    out  <<string("Наименование");
//    file.close();
    ui->pathSave->setText(QString("C:\\data.csv"));

    InitConnectDb();
}

void MainWindow::InitConnectDb(){
    setting = new mySettings("settings.conf");

    ui->tHost->setText(setting->HostName);
    ui->tUser->setText(setting->UserName);
    ui->tPass->setText(setting->Password); //crypt->decryptString(
    ui->tDb->setText(setting->DataBase);
    ui->tPort->setText(QVariant(setting->Port).toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    string tc =  ui->textEdit->toPlainText();
    if(tc == ""){
        QMessageBox::information(this,"Текст","Нет данных");
        return;
    }
    stringList sl;
    if(tc.indexOf("\n") !=-1){
        sl= tc.split("\n");
//        foreach (string s , sl) {
//            qDebug() << s;
//        }
    }
    else{
        sl << tc;
//        qDebug() << tc;
    }


//    setting->ipStart = ui->ipStart->text();
//    setting->ipEnd = ui->ipEnd->text();
//    setting->WriteSettings();

    db = new LibConnect(ui->tHost->text(),
                        ui->tDb->text(),ui->tUser->text(),ui->tPass->text(),
                        QVariant(ui->tPort->text()).toInt());
    if(!db->isConnect){
        if(!db->connect()){
            QMessageBox::information(this,"Подключение","Подключение к базе данных не установлено! "
                                     + db->lastError + ". Дальнейшая работа не возможна. Выполните настройку к базе");

            return;
        }
    }
    movie = new QMovie(":/new/prefix1/default.gif");
    movie->setScaledSize(ui->label_2->size());
    ui->label_2->setMovie(movie);
    movie->start();

    w = new worker();
    this->th = new QThread;
    w->pathSave = ui->pathSave->text();
    w->db = db;
    w->sl = sl;
    //w->Scan();
    w->moveToThread(th);
    connect(th, SIGNAL(started()), w, SLOT(Scan()));
    connect(w, SIGNAL(onComplit()), this, SLOT(Complite()));
    QDateTime now = QDateTime::currentDateTime();

    ui->textEdit_2->append(string("Дата начала - ")+ QVariant(now).toString());

    th->start();
}
void MainWindow::Complite(){
    //qDebug() << "завершено";
    QDateTime now = QDateTime::currentDateTime();

    ui->textEdit_2->append(string("Дата завершения - ")+ QVariant(now).toString());

    movie->stop();
    ui->label_2->clear();
    if(!w->listError.isEmpty()){
        ui->label_9->setText("Результат: не завершено, см Ошибки в дополнительно");
        ui->textEdit_2->append(string("Ошибки:"));
        foreach (string str, w->listError) {
            ui->textEdit_2->append(str);
        }
    }
    if(!w->listNot.isEmpty() && w->listError.isEmpty()){
        ui->label_9->setText("Результат: завершено, см дополнительно");
        int size = w->listNot.size();
        ui->textEdit_2->append(string("Не найденые артикулы ") + QVariant(size).toString() + string(":"));
        foreach (string str, w->listNot) {
            ui->textEdit_2->append(str);
        }
    }
    if(w->listNot.isEmpty() && w->listError.isEmpty()){
        ui->label_9->setText("Результат: завершено успешно");
    }
    //w->
}

void MainWindow::on_pushButton_2_clicked()
{
    LibConnect *db_temp = new LibConnect(ui->tHost->text(),
                                         ui->tDb->text(),
                                        ui->tUser->text(),
                                         ui->tPass->text(),
                                         QVariant(ui->tPort->text()).toInt());
    if(db_temp->connect()){
        QMessageBox::information(this,"Подключение","Подключение успешно установлено.");
        db = db_temp;
    }
    else{
        QMessageBox::information(this,"Подключение","Подключение не установлено! " + db_temp->lastError);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    setting->HostName = ui->tHost->text();
    setting->UserName = ui->tUser->text();
    setting->Password = ui->tPass->text(); //crypt->cryptString(
    setting->DataBase = ui->tDb->text();
    setting->Port = QVariant(ui->tPort->text()).toInt();
    setting->WriteSettings();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(th){
        //w->db->query->
        th->exit();
        movie->stop();
        delete th;
    }

}
