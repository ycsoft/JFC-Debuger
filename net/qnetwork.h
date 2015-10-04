#ifndef QNETWORK_H
#define QNETWORK_H

#include <QObject>
#include <QTcpSocket>

class QNetWork : public QObject
{
    Q_OBJECT
public:
    explicit QNetWork(QObject *parent = 0,QTcpSocket *sock = 0);
    ~QNetWork() {}

    QByteArray readHead();
    QByteArray readDataLen();
    QByteArray readDataContent();
    QByteArray readEnd();

    bool       isComplete()
    {
        return bComplete;
    }

    QByteArray  &getPacket()
    {
        return m_pack;
    }

signals:

public slots:

private:
    QTcpSocket      *m_sock;
    QByteArray      m_pack;
    int             m_type;
    quint32             m_dataLen;
    quint32         m_filelen;
    bool            bhead;      //头部已读
    bool            bdatalen;   //数据长度已读
    bool            bdataContent; //数据内容已读
    bool            bended;

    bool            bComplete;

};

#endif // QNETWORK_H
