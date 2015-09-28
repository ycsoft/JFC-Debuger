#include "qdevicecommand.h"
#include "qparse.h"
#include "jfcwindow.h"
#include "core/qhfwebview.h"

#include <QFile>
#include <QWebFrame>
#include <QMessageBox>
#include <QDebug>

QDeviceCommand::QDeviceCommand(QObject *parent) : QObject(parent)
{
    m_sock = new QTcpSocket(this);

    connect(m_sock,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_sock,SIGNAL(readyRead()),this,SLOT(onRead()));
}

void QDeviceCommand::connectDev(QString host, int port)
{
    m_sock->connectToHost(host,port);
}

void QDeviceCommand::connected()
{
    QMessageBox::information(0,LOCAL("JFC"),LOCAL("设备连接成功"),0);
}

void QDeviceCommand::onRead()
{
    char* data = m_sock->readAll().data();
    Cmd::Command *cmd = reinterpret_cast<Cmd::Command*>(data);
    int type = QParse::ref().getCmdType(*cmd);

    switch ( type )
    {
        case QParse::SerialType:
        {
            QString seria = QParse::ref().getSerial(*cmd);
            setSerial(seria);
            break;
        }

        case QParse::PicData:
        {
            char p[4] = {0};
            int  len = 0;
            memcpy(p,data + 4,4);

            len = ( p[0] << 24 ) | (p[1] <<16) | (p[2] <<8) | (p[3] & 0x000000ff);

            QFile file("ui/pic.jpg");
            file.write(data+8,len);
            file.close();
            QString js = QString("setImg('%1')").arg("pic.jpg");
            JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
            break;
        }
    }
}

Cmd::Command& QDeviceCommand::createCommand(byte cmd[], byte *data)
{
    static Cmd::Command  command;
    quint16 len = 0 ;
    if ( data == NULL )
    {
        len = 0;
    }else
    {
        len = strlen(reinterpret_cast<char*>(data));
    }

    command.cmd[0] = cmd[0];
    command.cmd[1] = cmd[1];
    command.dataLen[0] = len >> 8;
    command.dataLen[1] = len & 0x00FF;
    //注意，发送成功前保证data内存数据有效
    command.data = data;

    return command;
}

void QDeviceCommand::setSerial(QString s)
{
    QString js = QString("setDevCode('%s')").arg(s);
    JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
}

void QDeviceCommand::sendCmd(const Cmd::Command &cmd)
{
    char buf[BUFFER_LEN] = {0};
    int  len =  CmdLen(&cmd);
    memcpy(buf,&cmd, len);
    m_sock->write(buf,len);
}
