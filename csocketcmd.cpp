#include "csocketcmd.h"
#include <QDebug>
#pragma execution_character_set("utf-8")
CSocketCmd::CSocketCmd(QObject *parent) : QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));        //(a)
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected())); //(b)

}


//qint64 CSocketCmd::readData(char *data, qint64 maxlen)
//{
//   QString str=data;

//   qDebug()<< QString::fromUtf8(str.toLatin1().data());
//   qDebug()<<str;
//   return  maxlen;
//}

void CSocketCmd::close()
{
    qDebug()<<"close";
}
void CSocketCmd::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
void CSocketCmd::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);
        QString msg=buf;
        qDebug()<< QString::fromUtf8(buf,length);
    }
}
