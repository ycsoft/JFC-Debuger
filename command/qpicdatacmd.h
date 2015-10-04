#ifndef QPICDATACMD_H
#define QPICDATACMD_H

#include "qjfcprotocal.h"

#include <QObject>

class QPicDataCmd : public QJFCProtocal
{
    Q_OBJECT
public:
    explicit QPicDataCmd(QObject *parent = 0);
    ~QPicDataCmd() {}

    void processPacket( QByteArray &data);

signals:

public slots:
};

#endif // QPICDATACMD_H
