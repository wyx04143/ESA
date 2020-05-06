#include "csocketdata.h"

CSocketData::CSocketData(QObject *parent) : QTcpSocket(parent)
{
  connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected())); //(b)
}
void CSocketData::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
