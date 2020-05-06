#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include "csocketcmd.h"
#include "csocketdata.h"
#include "csocketserver.h"
#include <QList>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void onUpadateEdit(QString strMsg);
protected:
    Ui::Dialog *ui;
    CSocketServer m_ServerCmd; //监听主框命令服务
    CSocketServer m_ServerData;//监听主框数据服务
public:
    QList<QTcpSocket*> m_aSocketPtr;//连接指针数组,包括SocketData、SocketCmd
    QList<QTcpSocket*> m_aSocketData;//记录连接的数据Socket,与指令Socket配对后删除

};

#endif // DIALOG_H
