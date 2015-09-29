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
    setSerial(LOCAL("已连接"));
}

Cmd::Command & QDeviceCommand::cmdFromRawData(const char *buf)
{
    static  Cmd::Command     cmd;
    int     dlen        = 0;
    const   char *p     = buf + 2;
    if ( NULL != cmd.data )
    {
        delete cmd.data;
        cmd.data = NULL;
    }

    cmd.cmd[0] = *(p++);
    cmd.cmd[1] = *(p++);
    cmd.dataLen[0] = *(p++);
    cmd.dataLen[1] = *(p++);
    dlen = cmd.dataLen[0] << 8 | cmd.dataLen[1];

    cmd.data = new byte[dlen];
    memcpy(cmd.data,(byte*)p,dlen);
    p += dlen;
    cmd.cs = *(p++);
    cmd.end[0] = *(p++);
    cmd.end[1] = *p;
    return cmd;
}

void QDeviceCommand::onRead()
{
    char *data = m_sock->readAll().data();
    Cmd::Command *cmd = &(cmdFromRawData(data));
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

Cmd::Command& QDeviceCommand::createCommand(byte cmd[], byte *data, int len)
{
    static Cmd::Command  command;

    command.cmd[0] = cmd[0];
    command.cmd[1] = cmd[1];
    command.dataLen[0] = len >> 8;
    command.dataLen[1] = len & 0x00FF;

    if ( NULL != command.data )
    {
        delete command.data;
        command.data = NULL;
    }
    if ( len > 0 )
    {
        command.data = new byte[len];
        memcpy(command.data,data,len);
    }
    return command;
}

void QDeviceCommand::setSerial(QString s)
{
    QString js = QString("setDevCode('%1')").arg(s);
    JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
}

void QDeviceCommand::copyCmd(char *buf, const Cmd::Command &cmd)
{
    int len = cmd.dataLen[0] << 8 | cmd.dataLen[1];
    if ( NULL == buf )
    {
        return;
    }
    memcpy(buf,cmd.head,2);
    buf += 2;
    memcpy(buf,cmd.cmd,2);
    buf += 2;
    memcpy(buf,cmd.dataLen,2);
    buf += 2;
    memcpy(buf,cmd.data,len);
    buf += len;
    *(buf++) = cmd.cs;
    memcpy(buf,cmd.end,2);
}

void QDeviceCommand::sendCmd(const Cmd::Command &cmd)
{
    char buf[BUFFER_LEN] = {0};
    copyCmd(buf,cmd);
    m_sock->write(buf,cmd.dataLen[0] << 8 | cmd.dataLen[1]);
}
