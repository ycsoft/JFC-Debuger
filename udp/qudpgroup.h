#ifndef QUDPGROUP_H
#define QUDPGROUP_H

#include <QObject>
#include <QUdpSocket>

#define     UDP_PORT        9229
#define     Group_Address   "233.137.7.7"

class QUDPGroup : public QObject
{
    Q_OBJECT
public:
    explicit QUDPGroup(QObject *parent = 0);
    ~QUDPGroup (){}

signals:


public slots:

    void    diagramReady();

private:
    QUdpSocket      *m_udp;
};

#endif // QUDPGROUP_H
