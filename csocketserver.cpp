#include "csocketserver.h"
#include "dialog.h"
#include "csocketcmd.h"
#include "csocketdata.h"
CSocketServer::CSocketServer(QObject *parent) : QTcpServer(parent)
{
   m_iType=0;
}


void CSocketServer::incomingConnection(qintptr handle)
{
    QString rSocketAddress;
    quint32 rSocketPort;
    rSocketPort=serverPort();
    rSocketAddress=serverAddress().toString();
    QString strMsg;
    strMsg=QString("客户端连接%1端口").arg(rSocketPort);
    emit(updateServer(strMsg));

    QTcpSocket *pSocket;
    if(m_iType == 0)
    {//命令，第二个连接
        CSocketCmd *pSocketCmd;
        pSocketCmd = new CSocketCmd(this);
        if(m_pDlg->m_aSocketData.size() > 0)
        {
            pSocketCmd->m_pSocketData = (CSocketData *)m_pDlg->m_aSocketData[0];
            m_pDlg->m_aSocketData.removeAt(0);
        }
        pSocket = pSocketCmd;
    }
    else
    {//数据,第一个连接
        pSocket = new CSocketData(this);
        m_pDlg->m_aSocketData.append(pSocket);
    }
    connect(pSocket,SIGNAL(disconnected(int)),this,
            SLOT(slotDisconnected(int)));
    pSocket->setSocketDescriptor(handle);

    m_pDlg->m_aSocketPtr.append(pSocket);

}
void CSocketServer::SetServerType(qint8 iType, Dialog *pDlg)
{
    m_iType=iType;
    m_pDlg=pDlg;
}
void CSocketServer::slotDisconnected(int descriptor)
{
    for(int i=0;i<m_pDlg->m_aSocketPtr.count();i++)
    {
        QTcpSocket *item = m_pDlg->m_aSocketPtr.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            item->deleteLater();
            m_pDlg->m_aSocketPtr.removeAt(i);
            QString strMsg;
            strMsg=QString("客户端断开连接");
            emit(updateServer(strMsg));
            return;
        }
    }
    return;
}
