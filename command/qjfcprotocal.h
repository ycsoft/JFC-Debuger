#ifndef QJFCPROTOCAL_H
#define QJFCPROTOCAL_H

#include <QObject>

class QJFCProtocal : public QObject
{
    Q_OBJECT
public:
    explicit QJFCProtocal(QObject *parent = 0);
    ~QJFCProtocal() {}

    static int             typeOfCmd(void *);

    virtual void    processPacket( QByteArray &pack) = 0;
signals:

public slots:

private:
};

#endif // QJFCPROTOCAL_H
