#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextCodec>
#include "Logindialog.h"
#include <QMovie>
#include "devicesManage.h"
#include "QSqlError"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    QMovie *move = new QMovie(":/images/splash.gif");
    QLabel *label = new QLabel("",0);
    label->setGeometry(510,300,450,100);
    label->setMovie(move);
    move->start();
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->show();
    QTime t;
    t.start();
    while(t.elapsed() < 2000)
    {
        a.processEvents();
    }

    //连接mysql数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("960104");
    //db.setUserName("RJJ");
    //db.setPassword("RJJ1996");
    db.setDatabaseName("data");
    label->close();
    if(db.open())
    {
        db.exec("SET NAMES 'Latin1'");
        QSqlQuery query(db);
        query.exec("use data;");
        query.exec("delete from carbon;");
        query.exec("delete from temperature;");
        query.exec("delete from illumination;");
        query.exec("delete from humidity;");

        LoginDialog w;
        w.show();
        return a.exec();
    }
    else
    {
        qDebug()<<db.lastError();
        QMessageBox::information(NULL,"提示","系统载入数据库失败，无法运行",QMessageBox::Yes);
    }

//    DevicesManage *deviceManage=new DevicesManage();
//    deviceManage->show();
//    return a.exec();
    return 0;
}
