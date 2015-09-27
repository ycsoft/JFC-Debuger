#ifndef QJSCORE_H
#define QJSCORE_H

#include "command/qdevicecommand.h"

#include <QObject>
#include <QWidget>
/**
 * @brief The QJSCore class
 *封装一些本地方法，供js调用
 *
 */
class QJSCore : public QObject
{
    Q_OBJECT
public:
    explicit QJSCore(QObject *parent = 0);
    ~QJSCore(){}

signals:

public slots:

    void    connectDev(QString host, int port);
    void    BaseAngle(QString angle);
    void    NegAngle(QString angle);
    void    PicAcq();


    void     msgBox(const QString &title,const QString &txt);
    QString  readFromFile(const QString &fn);
    void     open(const QString &path);
    void     open(const QString &path,const QStringList &arglist);
    void     exit();

private:
    QDeviceCommand          *m_dev;

};

#endif // QJSCORE_H
