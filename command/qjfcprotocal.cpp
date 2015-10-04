#include "qjfcprotocal.h"
#include "qparse.h"

QJFCProtocal::QJFCProtocal(QObject *parent) : QObject(parent)
{

}

int QJFCProtocal::typeOfCmd(void *data)
{
    if ( NULL == data )
    {
        return QParse::UnKnown;
    }
    char type[2] = {0};

    memcpy(type,(quint8*)data+2,2);
    if ( type[0] == 0x00 )
    {
        switch ( type[1])
        {
        case 0x00:
             return QParse::BaseAngleType;
        case 0x01:
            return QParse::NegAngleType;
        case 0x02:
            return QParse::PicAcq;
        default:
            return QParse::UnKnown;
        }
    }else if ( type[0] == 0x40 )
    {
        switch ( type[1])
        {
        case 0x00:
             return QParse::SerialType;
        case 0x01:
            return QParse::PicData;
        default:
            return QParse::UnKnown;
        }

    }else
    {
        return QParse::UnKnown;
    }
}
