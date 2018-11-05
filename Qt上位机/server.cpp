#include "server.h"

QList<TcpClientSocket *> tcpClientSocketList;

Server::Server(QObject *parent,int port) :QTcpServer(parent)
{
  //AT+CIPSTART="TCP","222.194.57.113",8080
   //QHostAddress address=QHostAddress("222.194.57.113");
   // QHostAddress address=QHostAddress("192.168.253.1");
    QHostAddress address=QHostAddress("192.168.191.1");
   listen(address,port);
}

Server::~Server()
{

}

void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocketList.append(tcpClientSocket);
}
/*************/
/*slotDisconnected函数将列表中断开连接的TcpClientSocket对象删除*/
/*************/
void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++){
       QTcpSocket *item=tcpClientSocketList.at(i);
       if(item->socketDescriptor()==descriptor){}
       tcpClientSocketList.removeAt(i);
       return ;
    }
    return ;
}


/*************/
/*updateClients函数将任意客户端发来的消息进行广播,保证聊天室的所有客户均能看到其他人的发言*/
/*************/
void Server::updateClients(QString msg, int length)
{
    emit updateServer(msg,length);

}
