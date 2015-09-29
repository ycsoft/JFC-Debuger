#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QHostAddress>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:

    void    onNewConnection();
private:
    Ui::Widget *ui;

    QTcpServer   *m_server;
};

#endif // WIDGET_H
