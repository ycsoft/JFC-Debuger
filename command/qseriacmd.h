#ifndef QSERIACMD_H
#define QSERIACMD_H

#include "qjfcprotocal.h"
#include <QObject>

class QSeriaCmd : public QJFCProtocal
{
    Q_OBJECT
public:
    explicit QSeriaCmd(QObject *parent = 0);

    ~QSeriaCmd() {}
    void processPacket(QByteArray &pack);
signals:

public slots:
};

#endif // QSERIACMD_H
