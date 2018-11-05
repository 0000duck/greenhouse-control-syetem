#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QList>
#include "server.h"
#include "historydatadisplay.h"

/*extern QList<double> carbonData;
extern QList<double> illuminationData;
extern QList<double> temperatureData;
extern QList<double> humidityData;*/

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    virtual ~TcpServer();
    void CreateServer();
   // void updateTable(QString tableName);
//signals:
 //   void dataReceived();
public slots:  
    void updateServer(QString,int);
private:
    int port;
    Server *server;
    QSqlTableModel *model;
    const int rowCountMax=100;
    HistoryDataDisplay *historyDataDisplay;
};

#endif // TCPSERVER_H
