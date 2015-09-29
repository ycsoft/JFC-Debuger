#include "jfcwindow.h"
#include "command/qdevicecommand.h"
#include "jsCore/qjscore.h"
#include "udp/qudpgroup.h"

#include <QApplication>
#include <QDebug>

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JFCWindow w;
    w.show();

    QJSCore js;
    js.BaseAngle("15");
    char buf[8];
    memset(buf,'0',8);
    sprintf(buf,"%7.3f",50.3);
    QString s = QString(buf).replace(" ",QString("0"));
    qDebug()<<s;

    return a.exec();
}
