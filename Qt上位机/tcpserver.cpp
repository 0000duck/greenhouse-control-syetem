#include "tcpserver.h"
#include <QTime>
#include <QDebug>

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{

    port=8080;
    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //realDataDisplay=new RealDataDisplay();
    //historyDataDisplay=new HistoryDataDisplay();
    //(this,SIGNAL(dataReceived()),realDataDisplay,SLOT(updateData()));
    //connect(this,SIGNAL(dataReceived()),historyDataDisplay,SLOT(updateData()));
}
TcpServer::~TcpServer()
{
        delete server;
}
/*创建一个TCP服务器*/
void TcpServer::CreateServer()
{
    server=new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
}


/*更新服务器上的信息显示*/
void TcpServer::updateServer(QString msg, int length)
{
    bool ok=false;
    int hour = 0;
    static int lastHour = 0;
    int minute = 0;
    static int lastMinute = 0;
    int second = 0;
    static int lastsecond = 0;
    QString time;
    hour=QTime::currentTime().hour();
    minute=QTime::currentTime().minute();
    second= QTime::currentTime().second();
    if((hour >=lastHour)&&(minute>=lastMinute)&&second>=lastsecond){
    time = QString::number(hour ,10) +QString::number(minute,10) +QString::number(second,10);
    msg=msg.left(length);
    QChar ch=msg.at(0);
    //qDebug()<<"第一个字符为："<<ch<<endl;

    msg=msg.remove(0, 1);

    if(ch==QChar('T'))
    {
        double data=msg.toFloat(&ok);
        qDebug()<<tr("温度:%1摄氏度").arg(data)<<endl;
       // historyDataDisplay->getData(1,data);
        model->setTable("temperature");
        model->select();

        QSqlRecord record1=model->record();
        record1.setValue("time",time);
        record1.setValue("temperature",msg.toFloat(&ok));
        model->insertRecord(-1,record1);
        //this->updateTable("temperature");
        //qDebug()<<"进入循环:"<<endl;
    }
    else if(ch==QChar('H'))
    {
        double data=msg.toFloat(&ok);
        qDebug()<<tr("湿度:%1 %RH").arg(data)<<endl;
        //historyDataDisplay->getData(2 ,data);
        model->setTable("humidity");
        model->select();
        QSqlRecord record1=model->record();
        record1.setValue("time",time);
        record1.setValue("humidity",msg.toFloat(&ok));
        model->insertRecord(-1,record1);
        //this->updateTable("humidity");
    }
    else if(ch==QChar('C'))
     {
        double data=msg.toInt(&ok);
        qDebug()<<tr("二氧化碳:%1 PPM").arg(data)<<endl;
        //historyDataDisplay->getData("carbon",data);

        model->setTable("carbon");
        model->select();
        QSqlRecord record1=model->record();
        record1.setValue("time",time);
        record1.setValue("carbon",msg.toInt(&ok));
        model->insertRecord(-1,record1);
        //this->updateTable("carbon");
      }
    else if(ch==QChar('I'))
     {
        double data=msg.toInt(&ok);
        qDebug()<<tr("光照强度:%1 LX").arg(data)<<endl;
        //historyDataDisplay->getData("illumilation",data);

        model->setTable("illumination");
        model->select();
        QSqlRecord record1=model->record();
        record1.setValue("time",time);
        record1.setValue("illumination",msg.toInt(&ok));
        model->insertRecord(-1,record1);
        //this->updateTable("illumination");
    }
    else
    {
//        model->setTable("temperature");
//        model->select();
//        QSqlRecord record1=model->record();
//        record1.setValue("hour",hour);
//        record1.setValue("temperature",msg.toFloat(&ok));
//        model->insertRecord(-1,record1);
     }
    qDebug()<<"插入数据成功！"<<endl;
    //判断数据是否上传数据库成功

    if(model->submitAll())
    {
        qDebug()<<"数据上传成功！"<<ch<<endl;
       // emit dataReceived();
    }
    //上传不成功
    else
  {
    qDebug()<<"数据上传不成功！"<<endl;
  }


    }
    lastHour =hour;
    lastMinute = minute;
    lastsecond = second;
}
/*
void TcpServer::updateTable(QString tableName)
{
    int m_rowCount;
   // model->setTable(tableName);
    //model->select();
    m_rowCount=model->rowCount();

    if(m_rowCount>rowCountMax)
    {
        for(int i=0;i<rowCountMax;i++)
        {
            model->removeRow(i);
        }
       // model->submitAll();
    }*/

 /*   QSqlRecord record1=model->record();
    record1.setValue("hour",hour);
    record1.setValue("temperature",msg.toFloat(&ok));
    model->insertRecord(-1,record1);

            bool ok;
            QSqlRecord record=model->record(i);
            QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
            //判断信息是否为空,非空就把信息插入表格模型中
             if((record.value(0)!="")&&(record.value(1)!=""))
            {
                 for (int k = 0; k < dataVec->size(); k++)
                 {
                    if (k % 2 == 0)
                         dataVec->replace(k,record.value(0).toReal(&ok) );
                     else
                         dataVec->replace(k,record.value(1).toReal(&ok));
                 }
                 m_data.append(dataVec);
            }


}*/
