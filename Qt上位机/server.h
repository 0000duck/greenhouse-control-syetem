#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "tcpclientsocket.h"

extern QList<TcpClientSocket *> tcpClientSocketList;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=8080);
    virtual ~Server();
    /*保存每个客户端连接的TcpclientSocket*/    

signals:
    void updateServer(QString,int);
public slots:
    void slotDisconnected(int);
    void updateClients(QString,int);
protected:
    void incomingConnection(int socketDescriptor);



};
#endif // SERVER_H
