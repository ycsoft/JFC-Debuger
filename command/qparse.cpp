#include "qparse.h"

#include "qdevicecommand.h"

QParse::QParse(QObject *parent) : QObject(parent)
{

}

QString QParse::getSerial(const Cmd::Command & cmd)
{
    char data[13] = {0};
    strncpy(data,reinterpret_cast<char*>(cmd.data),SERIAL_LEN);

    return tr(data);
}

int QParse::getCmdType(const Cmd::Command &cmd)
{
    const byte *type = cmd.cmd;
    if ( type[0] == 0x00 )
    {
        switch ( type[1])
        {
        case 0x00:
             return BaseAngleType;
        case 0x01:
            return NegAngleType;
        case 0x02:
            return PicAcq;
        default:
            return UnKnown;
        }
    }else if ( type[0] == 0x40 )
    {
        if ( type[1] == 0x00)
        {
            return SerialType;
        }else if ( type[1] == 0x01)
        {
            return PicData;
        }else
            return UnKnown;
    }else
    {
        return UnKnown;
    }
}
