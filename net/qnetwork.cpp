#include "qnetwork.h"
#include "command/qparse.h"
#include "jfcwindow.h"
#include "core/qhfwebview.h"

#include <QDebug>
#include <QFile>


#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebView>

#else

#include <QWebView>
#include <QWebFrame>

#endif

QNetWork::QNetWork(QObject *parent,QTcpSocket *sock) : QObject(parent),m_sock(sock)
{
    bhead = false;
    bdatalen  = false;
    bdataContent = false;
    bended = false;
    bComplete = false;
}

QByteArray QNetWork::readHead()
{
    QByteArray ret;
    bComplete = false;

    if ( bhead )
    {
        return ret;
    }

    ret = m_sock->read(4);
    quint8  cmd[2] =  {0x00,0x00};
    cmd[0] = ret[2];
    cmd[1] = ret[3];
    if ( cmd[0] == 0x00 )
    {
        if ( cmd[1] == 0x00 )
        {
            m_type = QParse::BaseAngleType;
        }else if ( cmd[1] == 0x01)
        {
            m_type = QParse::NegAngleType;
        }else if ( cmd[1] == 0x02)
        {
            m_type = QParse::PicAcq;
        }
    }else
    {
        if ( cmd[1] == 0x00)
        {
            m_type = QParse::SerialType;
        }else
        {
            m_type = QParse::PicData;
        }
    }
    bhead = true;
    m_pack.append(ret);
    return ret;
}
QByteArray QNetWork::readDataLen()
{
    QByteArray ret;

    if ( bdatalen )
    {
        return ret;
    }
    if ( m_type != QParse::PicData )
    {
        ret = m_sock->read(2);
        m_dataLen = ret[0] << 8 | ret[1] & 0x00ff;
    }else
    {
        ret = m_sock->read(4);
        m_dataLen = ret[0] <<24 | ret[1] << 16 & 0x00ff0000 | ret[2] <<8 & 0x0000ff00 | ret[3] &0x000000ff;
    }
    bdatalen = true;
    m_filelen = m_dataLen - 26;
    m_pack.append(ret);
    return ret;
}
QByteArray QNetWork::readDataContent()
{
    QByteArray ret;

    if (bdataContent)
    {
        return ret;
    }
    int available = m_sock->bytesAvailable();
    if ( available < m_dataLen )
    {
        bdataContent = false;
        ret.append( m_sock->read(available));
        m_dataLen -= available;

    }else
    {
        bdataContent = true;
        ret.append(m_sock->read(m_dataLen));
    }
    m_pack.append(ret);
    return ret;
}
QByteArray QNetWork::readEnd()
{
    QByteArray ret;
    if ( bended  || !bdataContent)
    {
        return ret;
    }

    ret = m_sock->read(3);
    m_pack.append(ret);
    //此时，可以开始准备读取下一个数据包
    bhead = false;
    bdatalen = false;
    bdataContent = false;
    bended = false;
    bComplete = true;
//    //保存图片
//    if ( m_type == QParse::PicData )
//    {
//        QFile file("ui/pic.jpg");
//        file.open(QIODevice::WriteOnly);
//        file.write(m_pack.data()+34,m_filelen);
//        file.close();

//        m_pack.clear();
//        QString js = QString("setImg('%1')").arg("pic.jpg");

//        JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
//    }
//    //设置序列号
//    else if ( m_type == QParse::SerialType )
//    {
//        char seria[SERIAL_LEN + 1] = {0};
//        memcpy(seria,m_pack.data() + 6,SERIAL_LEN);
//        m_pack.clear();
//        QString js = QString("setDevCode('%1')").arg(seria);
//        JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
//    }

    return ret;
}
