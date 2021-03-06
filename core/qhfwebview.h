﻿#ifndef QHFWEBVIEW_H
#define QHFWEBVIEW_H

#include <QWidget>


#if( QT_VERSION > 0x040000)

#include <QtWebKitWidgets/QWebView>

#else

#include <QWebView>

#endif
class QHFWebView : public QWebView
{
    Q_OBJECT
public:
    explicit QHFWebView(QWidget *parent = 0);
    ~QHFWebView()
    {

    }

    void     setTransparent( bool );
    void     load(const QUrl& url);

protected:
//    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *evt);
signals:

public slots:
    void    registerObject();
private:
    QWidget  *m_parent;
};

#endif // QHFWEBVIEW_H
