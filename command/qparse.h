#ifndef QPARSE_H
#define QPARSE_H

#include "qdevicecommand.h"
#include <QObject>

class QParse : public QObject
{
    Q_OBJECT
public:

    ~QParse() {}
    enum        CmdType { SerialType, BaseAngleType,NegAngleType,
                          PicAcq,PicData,UnKnown};
    QString     getSerial( const Cmd::Command & cmd);
    int         getCmdType( const Cmd::Command &cmd);

    static QParse& ref()
    {
        static QParse p;
        return p;
    }

signals:

public slots:

private:
    explicit QParse(QObject *parent = 0);
};

#endif // QPARSE_H
