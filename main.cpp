#include "jfcwindow.h"
#include "command/qdevicecommand.h"
#include "jsCore/qjscore.h"

#include <QApplication>

#include <iostream>
#include <stdio.h>

using namespace std;

union  data
{
    char c[4];
    int  it;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    data d;
    d.it = 1;

    JFCWindow w;
    w.show();
    QDeviceCommand  dev;
    dev.onRead();

    QJSCore js;
    js.BaseAngle("15.34");

    return a.exec();
}
