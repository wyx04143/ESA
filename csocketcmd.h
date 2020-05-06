#ifndef CSOCKETCMD_H
#define CSOCKETCMD_H

#include <QObject>
#include <QTcpSocket>
#include "csocketdata.h"
class CSocketCmd : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CSocketCmd(QObject *parent = nullptr);

signals:
    void disconnected(int);
public slots:
    void dataReceived();
    void slotDisconnected();
public:
    CSocketData *m_pSocketData;

    // QIODevice interface
protected:
   // qint64 readData(char *data, qint64 maxlen);

    // QIODevice interface
public:
    void close();
};

#endif // CSOCKETCMD_H
