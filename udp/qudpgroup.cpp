#include "qudpgroup.h"

#define     UnImplement

#define     ToDo(x) UnImplement

QUDPGroup::QUDPGroup(QObject *parent) : QObject(parent)
{
    m_udp = new QUdpSocket(this);

    m_udp->bind(UDP_PORT),QUdpSocket::ShareAddress;
    m_udp->joinMulticastGroup(QHostAddress(Group_Address));
    connect(m_udp,SIGNAL(readyRead()),this,SLOT(diagramReady()));
}

void QUDPGroup::diagramReady()
{
    QByteArray   data;
    QHostAddress host;
    quint16      port;

    data.resize( m_udp->pendingDatagramSize());
    //接受设备返回的信息
    m_udp->readDatagram(data.data(),data.size(),&host,&port);

    qDebug()<<"Recv:"<<data;
    ToDo( getDeviceInfo(data) );
}
