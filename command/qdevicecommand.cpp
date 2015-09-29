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
    setSerial(LOCAL("已连接").toUtf8());
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
    QByteArray  alldata;

    QByteArray  head    =   m_sock->read(4);
    byte        type[2] =   {0x00,0x00};

    type[0] = (byte)head[2];
    type[1] = (byte)head[3];

    alldata.append(head);

    if ( type[0] == 0x00 || ( type[0] == 0x40 && type[1] == 0x00) )
    {
        QByteArray datalen = m_sock->read(2);
        char buf[SOCK_BUF] = {0};

        alldata.append(datalen);
        int len = datalen[0] << 8 | datalen[1];
        int rd  = m_sock->read(buf,len);
        while ( rd < len)
        {
            int it = m_sock->read(buf+rd,len - rd);
            rd += it;

        }
        alldata.append(buf,len);
        memset(buf,0,SOCK_BUF);
        rd = m_sock->read(buf,3);
        while ( rd < 3 )
        {
            rd += m_sock->read(buf+rd,3-rd);
        }
        alldata.append( buf,3 );
        //处理接收到的所有数据
        Cmd::Command *cmd = &(cmdFromRawData(alldata.data()));
        int type = QParse::ref().getCmdType(*cmd);

        if( type == QParse::SerialType )
        {
                QString seria = QParse::ref().getSerial(*cmd);

                m_seria = seria;
                qDebug()<<"Device Code:"<<seria;
                setSerial(seria);
        }

    }else
    {

        int pic_offset = 34;
        QByteArray datalen = m_sock->read(4);
        char buf[SOCK_BUF] = {0};
        QFile file("ui/pic.jpg");
        file.open(QIODevice::WriteOnly);

        alldata.append(datalen);
       quint32 len = datalen[0] << 24 | datalen[1] << 16 & 0x00ff0000
                  | datalen[2] <<8  & 0x0000ff00 | datalen[3] & 0x000000ff;
        int rd  = m_sock->read(buf,len);

        alldata.append(buf,rd);
        while ( rd < len)
        {
            m_sock->waitForReadyRead();
            int it = m_sock->read(buf,len - rd);
            rd += it;
            alldata.append(buf,it);
            memset(buf,0,SOCK_BUF);
        }
        file.write(alldata.data() + pic_offset,len - 26);
        file.close();
        memset(buf,0,SOCK_BUF);
        rd = m_sock->read(buf,3);
        if ( rd < 3 )
        {
            rd += m_sock->read(buf+rd,3-rd);
        }
        alldata.append(buf,3);
        QString js = QString("setImg('%1')").arg("pic.jpg");
        JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
    }


/*
    char *data = m_sock->readAll().data();
    Cmd::Command *cmd = &(cmdFromRawData(data));
    int type = QParse::ref().getCmdType(*cmd);

    switch ( type )
    {
        case QParse::SerialType:
        {
            QString seria = QParse::ref().getSerial(*cmd);

            m_seria = seria;
            qDebug()<<"Device Code:"<<seria;
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
    */
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
