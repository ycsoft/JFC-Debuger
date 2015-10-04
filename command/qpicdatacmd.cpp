#include "qpicdatacmd.h"
#include "jfcwindow.h"
#include "qdevicecommand.h"
#include "core/qhfwebview.h"

#include <QFile>

#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebView>

#else

#include <QWebView>
#include <QWebFrame>

#endif

QPicDataCmd::QPicDataCmd(QObject *parent) : QJFCProtocal(parent)
{

}

void QPicDataCmd::processPacket(QByteArray &data)
{
    quint32 filelen = 0;


    filelen = data[4] << 24 | (data[5] << 16 & 0x00ff0000) | ( data[6] << 8 & 0x0000ff00)
            | ( data[7] & 0x000000ff) - 26;

    QFile file("ui/pic.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(data.data()+34,filelen);
    file.close();

    data.resize(0);
    QString js = QString("setImg('%1')").arg("pic.jpg");

    JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
}
