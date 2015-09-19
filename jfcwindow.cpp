#include "jfcwindow.h"
#include "core/qhfwebview.h"

#include <QVBoxLayout>
#include <QWebFrame>

JFCWindow::JFCWindow(QWidget *parent) :
    QWidget(parent)
{
    setUpUi();
    setWindowFlags( windowFlags()& ~Qt::WindowMaximizeButtonHint );
    setMaximumHeight(800);
    resize(770,550);
    m_pressed = false;
}

JFCWindow::~JFCWindow()
{
}

void JFCWindow::setUpUi()
{
    QHBoxLayout *vlay = new QHBoxLayout(this);

    m_web = new QHFWebView(this);
    m_web->load(QUrl("ui/connectdevice.html"));
//    m_nav = new QHFWebView(this);
//    m_nav->load(QUrl("ui/LeftNav.html"));
//    m_nav->setMaximumWidth(150);
//    m_nav->setMinimumWidth(150);

    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObj()));
    vlay->setContentsMargins(0,0,0,0);
    vlay->setSpacing(0);
//    vlay->addWidget(m_nav);
    vlay->addWidget(m_web);
}

void JFCWindow::registerObj()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("JFCWin",this);
}

void JFCWindow::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        m_pressed = true;
        m_pressPoint = pos();
    }
}
void JFCWindow::mouseReleaseEvent(QMouseEvent *evt)
{
    m_pressed = false;
}
void JFCWindow::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed )
    {
        move( evt->globalPos() - m_pressPoint);
    }
}
