#include "qhfwebview.h"
#include "jsCore/qjscore.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>
#include <QMouseEvent>
#include <QWebSettings>
#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebFrame>

#else

#include <QWebFrame>

#endif

QHFWebView::QHFWebView(QWidget *parent) : QWebView(parent)
{

}
void QHFWebView::mouseDoubleClickEvent(QMouseEvent *evt)
{
    evt->ignore();
}

void QHFWebView::setTransparent(bool )
{
    QPalette palette = this->palette();

    palette.setBrush(QPalette::Base,Qt::transparent);
    this->page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent,false);
}

void QHFWebView::registerObject()
{
    QJSCore *core = new QJSCore(this);

    page()->mainFrame()->addToJavaScriptWindowObject("Qt",core);
}

void QHFWebView::load(const QUrl &url)
{
    QWebView::load(url);
    QWebSettings *sets = this->page()->settings();

    sets->setAttribute(QWebSettings::JavascriptEnabled,true);
    sets->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);

    connect(page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObject()));
}
