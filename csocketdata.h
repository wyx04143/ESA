#ifndef CSOCKETDATA_H
#define CSOCKETDATA_H

#include <QObject>
#include <QTcpSocket>
class CSocketData : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CSocketData(QObject *parent = nullptr);

signals:
    void disconnected(int);
public slots:
    void slotDisconnected();
};

#endif // CSOCKETDATA_H
