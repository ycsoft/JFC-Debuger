#ifndef JFCWINDOW_H
#define JFCWINDOW_H

#include <QWidget>
#include <QMouseEvent>

class QHFWebView;

class JFCWindow : public QWidget
{
    Q_OBJECT

public:
    explicit JFCWindow(QWidget *parent = 0);
    ~JFCWindow();

    static QHFWebView *getWeb();

public slots:
    void            registerObj();
    void            loadFinish(bool);
protected:
    void            setUpUi();

    void            mousePressEvent(QMouseEvent *evt);
    void            mouseReleaseEvent(QMouseEvent *evt);
    void            mouseMoveEvent(QMouseEvent *evt);
private:
    static QHFWebView      *m_web;
    QHFWebView      *m_nav;

    bool            m_pressed;
    QPoint          m_pressPoint;
    QPoint          m_movePoint;

};

#endif // JFCWINDOW_H
