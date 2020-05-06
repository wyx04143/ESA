#ifndef CSOCKETSERVER_H
#define CSOCKETSERVER_H


#include <QObject>
#include <QTcpServer>
class Dialog;
class CSocketServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CSocketServer(QObject *parent = nullptr);

signals:
    void updateServer(QString);
public slots:
    void slotDisconnected(int);
    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
    qint8 m_iType;
    Dialog *m_pDlg;
public:
    void SetServerType(qint8 iType, Dialog *pDlg);


};

#endif // CSOCKETSERVER_H
