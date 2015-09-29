#include "jfcwindow.h"
#include "command/qdevicecommand.h"
#include "jsCore/qjscore.h"
#include "udp/qudpgroup.h"

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
    JFCWindow w;
    w.show();

    return a.exec();
}
