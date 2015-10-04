#ifndef QPARSE_H
#define QPARSE_H

#include "qdevicecommand.h"
#include <QObject>

namespace  QParse {

    enum        CmdType { SerialType, BaseAngleType,NegAngleType,
                      PicAcq,PicData,UnKnown };
}

//class QParse : public QObject
//{
//    Q_OBJECT
//public:

//    ~QParse() {}
//    enum        CmdType { SerialType, BaseAngleType,NegAngleType,
//                          PicAcq,PicData,UnKnown};
//signals:

//public slots:

//private:
//    explicit QParse(QObject *parent = 0);
//};

#endif // QPARSE_H
