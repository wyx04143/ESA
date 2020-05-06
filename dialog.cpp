#include "dialog.h"
#include "ui_dialog.h"
#include <QtNetwork>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(600,400);
    setLayout(ui->verticalLayout_2);
    m_ServerCmd.SetServerType(0,this);
    if (!m_ServerCmd.listen(QHostAddress::LocalHost, 5000)) {
        qDebug() << m_ServerCmd.errorString();
        close();
        return;
    }
    m_ServerData.SetServerType(1,this);
    if (!m_ServerData.listen(QHostAddress::LocalHost, 5001)) {
        qDebug() << m_ServerData.errorString();
        close();
        return;
    }
   connect(&m_ServerCmd,&CSocketServer::updateServer,this,&Dialog::onUpadateEdit);
   connect(&m_ServerData,&CSocketServer::updateServer,this,&Dialog::onUpadateEdit);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    ui->textEdit->clear();
}
void Dialog::onUpadateEdit(QString strMsg)
{
    QString str=ui->textEdit->toPlainText();
    if(!str.isEmpty())
       str+="\n";
    str+=strMsg;
    ui->textEdit->setPlainText(str);
}
