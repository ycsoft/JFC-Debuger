#ifndef QDEVICECOMMAND_H
#define QDEVICECOMMAND_H

#include <QObject>
#include <QTcpSocket>

class QDeviceCommand : public QObject
{
    Q_OBJECT
public:
    explicit QDeviceCommand(QObject *parent = 0);

signals:

public slots:
private:
    QTcpSocket          *m_sock;
};

#endif // QDEVICECOMMAND_H
