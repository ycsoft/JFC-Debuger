#include "jfcwindow.h"
#include "command/qdevicecommand.h"
#include "jsCore/qjscore.h"
#include "udp/qudpgroup.h"

#include <QApplication>

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JFCWindow w;
    w.show();

    QJSCore js;
    js.BaseAngle("135");

    return a.exec();
}
