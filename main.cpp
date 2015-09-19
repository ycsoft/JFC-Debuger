#include "jfcwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JFCWindow w;
    w.show();

    return a.exec();
}
