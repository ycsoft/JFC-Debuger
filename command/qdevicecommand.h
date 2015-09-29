#ifndef QDEVICECOMMAND_H
#define QDEVICECOMMAND_H

#include <QObject>
#include <QTcpSocket>

#define LOCAL(x)  QString::fromLocal8Bit(x)

#define  SERIAL_LEN    12
#define  STABLE_LEN     9
#define  BUFFER_LEN    128

#define  CmdLen( cmd )      ( \
                                STABLE_LEN + \
                                ((cmd)->dataLen[0] << 8  | \
                                (cmd)->dataLen[1]) \
                            )


#define         BASE_TYPE   {0x00,0x00}
#define         NEG_TYPE    {0x00,0x01}
#define         PIC_ACQ     {0x00,0x02}

#define         SERIA_TYPE  {0x40,0x00}
#define         PIC_DATA    {0x40,0x01}


#pragma pack(1)

typedef unsigned char byte;

namespace Cmd {

///
/// \brief The Command struct
///通信协议的通用表示
///
struct Command
{
    byte head[2];
    byte cmd[2];
    byte dataLen[2];
    byte *data;
    byte cs;
    byte end[2];
    Command()
    {
        head[0] = 0x7F;
        head[1] = 0x55;
        cs      = 0x00;
        data    = NULL;
        end[0]  = 0xBE;
        end[1]  = 0xEF;
    }
    ~Command()
    {
        if ( NULL != data )
        {
            delete [] data;
            data = NULL;
        }
    }
};
/*
struct BaseAngle:public Command
{
    BaseAngle()
    {
        cmd[0] = 0x00;
        cmd[1] = 0x00;
    }
};
struct NegAngle: public Command
{
    NegAngle()
    {
        cmd[0] = 0x00;
        cmd[1] = 0x01;
    }
};
*/
}

///
/// \brief The QDeviceCommand class
/// 提供连接设备、发送命令、接收响应等与设备通信功能
///
class QDeviceCommand : public QObject
{
    Q_OBJECT
public:
    explicit        QDeviceCommand(QObject *parent = 0);

    Cmd::Command    &cmdFromRawData( const char *buf );

    void            closeDev();
    ~QDeviceCommand() {}
    ///
    /// \brief createCommand
    /// \param cmd : 命令类型
    /// \param data: 协议中的数据内容
    /// \return
    ///
    Cmd::Command &  createCommand(byte cmd[2],byte *data, int len = 0);

    ///
    /// \brief connectDev
    ///连接设备
    /// \param host
    /// \param port
    ///
    void            connectDev(QString host, int port);
    ///
    /// \brief sendCmd
    /// \param cmd
    ///
    void            sendCmd(const Cmd::Command &cmd);
    void            copyCmd(char *buf, const Cmd::Command &cmd);
signals:

public slots:
    void            connected();
    void            onRead();
private:
    QTcpSocket          *m_sock;

    ///
    /// \brief setSerial
    /// \param :设备序列号
    ///
    void            setSerial(QString s);

    QString         m_seria;
};

#endif // QDEVICECOMMAND_H
