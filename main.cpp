#include "jfcwindow.h"
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
    return a.exec();
}
