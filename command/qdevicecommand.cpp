#include "qdevicecommand.h"
#include "qparse.h"
#include "jfcwindow.h"
#include "net/qnetwork.h"
#include "core/qhfwebview.h"
#include "qjfcprotocal.h"
#include "qseriacmd.h"
#include "qpicdatacmd.h"

#include <QFile>


#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebFrame>

#else

#include <QWebFrame>

#endif

#include <QMessageBox>
#include <QDebug>

QDeviceCommand::QDeviceCommand(QObject *parent) : QObject(parent)
{
    m_sock = new QTcpSocket(this);

    m_net = new QNetWork(this,m_sock);
    connect(m_sock,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_sock,SIGNAL(readyRead()),this,SLOT(onRead()));

}

void QDeviceCommand::connectDev(QString host, int port)
{
    m_sock->connectToHost(host,port);
}

void QDeviceCommand::connected()
{
    setSerial(LOCAL("已连接").toUtf8());
    QString js = tr("showDeg()");
    JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
    //QMessageBox::information(0,LOCAL("JFC"),LOCAL("设备连接成功"),0);

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
    QJFCProtocal *jfcprot = NULL;

    m_mutex.lock();
    m_net->readHead();
    m_net->readDataLen();
    m_net->readDataContent();
    m_net->readEnd();

    if (! m_net->isComplete() )
    {
        m_mutex.unlock();
        return;
    }

    QByteArray &pack = m_net->getPacket();
    int type = QJFCProtocal::typeOfCmd(pack.data());

    switch ( type) {
    case QParse::SerialType:
    {
        jfcprot = new QSeriaCmd(this);
        jfcprot->processPacket(pack);
        break;
    }
    case QParse::PicData:
    {
        jfcprot = new QPicDataCmd(this);
        jfcprot->processPacket(pack);
    }
    default:
        break;
    }


    m_mutex.unlock();
}

Cmd::Command& QDeviceCommand::createCommand(byte cmd[], byte *data, int len)
{
    static Cmd::Command  command;

    command.cmd[0] = cmd[0];
    command.cmd[1] = cmd[1];
    command.dataLen[0] = (len+ SERIAL_LEN) >> 8;
    command.dataLen[1] = (len+ SERIAL_LEN) & 0x00FF;

    if ( NULL != command.data )
    {
        delete [] command.data;
        command.data = NULL;
    }
    if ( len >= 0 )
    {
        command.data = new byte[len + SERIAL_LEN];
        memset(command.data,0,len+SERIAL_LEN);
        memcpy(command.data,m_seria.toLocal8Bit().data(),SERIAL_LEN);
        if ( len > 0)
        {
            memcpy(command.data+SERIAL_LEN,data,len);
        }

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
    m_sock->write(buf,CmdLen(&cmd));
}

void QDeviceCommand::closeDev()
{
    if ( m_sock->isOpen())
    {
        m_sock->close();
    }
}
