#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>

#include "libconnect.h"
#include "worker.h"
#include "mysettings.h"

#define string QString
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void Complite();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    //void on_pushButton_8_clicked();

    void on_pB_OpenFile_clicked();

private:
    Ui::MainWindow *ui;

    LibConnect *db;
    QMovie *movie; //экземпляр объекта для анимации ожидания
    QThread *th;
    mySettings *setting; //хранение настроек
    worker *w;
    void InitConnectDb();

    bool initData(); //инициализация данных
};

#endif // MAINWINDOW_H
