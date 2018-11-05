#include "tcpclientsocket.h"
#include <QTextCodec>

TcpClientSocket::TcpClientSocket(QObject */*parent*/)
{
    /*QTcpSocket被看做QIODevice,在数据到来时发出readyRead信号*/
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    /*disconnected信号在断开连接时发出*/
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

void TcpClientSocket::dataReceived()
{
    QString msg=nullptr;
    while(bytesAvailable()>0){
        int length=bytesAvailable();
        char buf[1024];
        QTextCodec *tc=QTextCodec::codecForName("GBK");
        read(buf,length);
        qDebug()<<tr("接收到数据")<<buf<<"\n";
        msg=tc->toUnicode(buf);
        emit updateClients(msg,length);          //通知服务器向聊天室内所有成员广播消息
    }
    qDebug()<<tr("接收到数据")<<msg<<"\n";
}

void TcpClientSocket::slotDisconnected()
{
    /*
     * Returns the native socket descriptor of
       the QAbstractSocket object if this is available; otherwise returns -1.
    */
    emit disconnected(this->socketDescriptor());
}

