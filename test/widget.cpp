#include "widget.h"
#include "ui_widget.h"

#include <QTcpSocket>
#include <QDebug>
#include <QFile>

#include <Windows.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::LocalHost,1234);
    connect(m_server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onNewConnection()
{
    qDebug()<<"New Connection";
    QTcpSocket *tcp = m_server->nextPendingConnection();
    int  size = 1024 *1024; //1M
    quint8 *buf = new quint8[size];
    QFile file("1.jpg");
    if ( !file.exists() )
    {
        qDebug()<<"No File";
        delete [] buf;
        return;
    }
    file.open(QIODevice::ReadOnly);
    qint32 sz = file.size() + 26;
    memset(buf,0,size);
    buf[0] = 0x7F;
    buf[1] = 0x55;
    buf[2] = 0x40;
    buf[3] = 0x01;
    //数据长度
    buf[4] = sz >> 24 & 0x000000ff;
    buf[5] = sz >> 16 & 0x000000ff;
    buf[6] = sz >> 8  & 0x000000ff;
    buf[7] = sz & 0x000000ff;
    //设备序列号未给
    buf[19] = 0x01;
    //图片数据
    memcpy(buf+34,file.readAll().data(),sz);
    file.close();
    //协议尾部
    buf[ sz + 8 ] = 0x00;
    buf[ sz + 9 ] = 0xBE;
    buf[ sz + 10 ] = 0xEF;
    //一次性向客户端写入一张73K图片的数据
    tcp->write((char*)buf,sz + 8);
    tcp->waitForBytesWritten();
    delete [] buf;

}
