#include "qseriacmd.h"
#include "qdevicecommand.h"
#include "jfcwindow.h"
#include "core/qhfwebview.h"


#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebView>

#else

#include <QWebView>
#include <QWebFrame>

#endif

QSeriaCmd::QSeriaCmd(QObject *parent) : QJFCProtocal(parent)
{

}

void QSeriaCmd::processPacket( QByteArray &pack )
{
    char seria[SERIAL_LEN + 1] = {0};
    memcpy(seria,pack.data() + 6,SERIAL_LEN);
    pack.resize(0);
    QString js = QString("setDevCode('%1')").arg(seria);
    JFCWindow::getWeb()->page()->mainFrame()->evaluateJavaScript(js);
}
