﻿#include "jfcwindow.h"
#include "core/qhfwebview.h"
#include "command/qdevicecommand.h"

#include <QVBoxLayout>
#include <QWebFrame>

QHFWebView * JFCWindow::m_web = NULL;

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
QHFWebView * JFCWindow::getWeb()
{
    return m_web;
}

void JFCWindow::setUpUi()
{
    QHBoxLayout *vlay = new QHBoxLayout(this);


    m_web = new QHFWebView(this);
    m_web->load(QUrl("ui/connectdevice.html"));

    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObj()));
    connect(m_web,SIGNAL(loadFinished(bool)),this,SLOT(loadFinish(bool)));

    vlay->setContentsMargins(0,0,0,0);
    vlay->setSpacing(0);
    vlay->addWidget(m_web);
}

void JFCWindow::registerObj()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("JFCWin",this);
}
void JFCWindow::loadFinish(bool)
{
    Cmd::Command   cmd;
    cmd.data = (byte*)("Hello");
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
