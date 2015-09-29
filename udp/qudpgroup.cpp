#include "qudpgroup.h"

#define     UnImplement

#define     ToDo(x) UnImplement

QUDPGroup::QUDPGroup(QObject *parent) : QObject(parent)
{
    m_udp = new QUdpSocket(this);

    m_udp->bind(UDP_PORT);

//    m_udp->setSocketOption(QAbstractSocket::MulticastTtlOption);
    m_udp->joinMulticastGroup(QHostAddress(Group_Address));

//    m_udp->writeDatagram("Hello JFC",QHostAddress(Group_Address),UDP_PORT);
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
