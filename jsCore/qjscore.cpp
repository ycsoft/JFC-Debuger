#include "qjscore.h"
#include "command/qdevicecommand.h"

#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QProcess>

QJSCore::QJSCore(QObject *parent) : QObject(parent)
{
    m_dev = new QDeviceCommand(this);
}


QString QJSCore::readFromFile(const QString &fn)
{
    QString result;
    QFile file(fn);

    qDebug()<<fn;
    if ( !file.exists() )
    {
        qDebug()<<"No This File";
        return result;
    }
    file.open(QIODevice::ReadOnly);
    result = QString::fromUtf8(file.readAll());
    qDebug()<<result;
    file.close();
    return result;
}

void QJSCore::msgBox(const QString &title,const QString &txt)
{
    qDebug()<<"MsgBox";
    QMessageBox::information(NULL,title,txt,0);
}

void QJSCore::open(const QString &path)
{

    QFile file(path);
    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path);
        proc->waitForStarted(5000);
    }else
    {
        qDebug()<<"No File:"<<path;
    }
}
void QJSCore::open(const QString &path, const QStringList &arglist)
{
    QFile file(path);
    for ( int i = 0 ; i < arglist.count(); ++i)
    {
        qDebug()<<arglist.at(i);
    }

    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path,arglist);
        proc->waitForStarted(5000);

    }else
    {
        qDebug()<<"No File:"<<path;
    }
}

void QJSCore::exit()
{
    qApp->exit(0);
}

void QJSCore::connectDev(QString host, int port)
{
    qDebug()<<LOCAL("连接设备。。。")<<"IP:"<<host<<" port:"<<port;

    m_dev->connectDev(host, port);
}

void QJSCore::BaseAngle(QString angle)
{
    qDebug()<<LOCAL("调整基准角。。。。。。")<<angle;
    byte head[2] = BASE_TYPE;
    Cmd::Command  cmd = m_dev->createCommand(head,(byte*)angle.toLocal8Bit().data());
    m_dev->sendCmd(cmd);
}
void QJSCore::NegAngle(QString angle)
{
    qDebug()<<LOCAL("调整NECK角。。。。。。")<<angle;
    byte head[2] = NEG_TYPE;
    Cmd::Command  cmd = m_dev->createCommand(head,(byte*)angle.toLocal8Bit().data());
    m_dev->sendCmd(cmd);
}

void QJSCore::PicAcq()
{
    qDebug()<<LOCAL("采集图像。。。。。。");
    byte head[2] = PIC_ACQ;
    Cmd::Command cmd = m_dev->createCommand(head,NULL);
    m_dev->sendCmd(cmd);
}
