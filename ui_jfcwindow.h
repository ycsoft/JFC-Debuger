/********************************************************************************
** Form generated from reading UI file 'jfcwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JFCWINDOW_H
#define UI_JFCWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JFCWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWebView *webView;

    void setupUi(QWidget *JFCWindow)
    {
        if (JFCWindow->objectName().isEmpty())
            JFCWindow->setObjectName(QStringLiteral("JFCWindow"));
        JFCWindow->resize(515, 391);
        verticalLayout = new QVBoxLayout(JFCWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        webView = new QWebView(JFCWindow);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("qrc:/ui/connectdevice.html")));

        verticalLayout->addWidget(webView);


        retranslateUi(JFCWindow);

        QMetaObject::connectSlotsByName(JFCWindow);
    } // setupUi

    void retranslateUi(QWidget *JFCWindow)
    {
        JFCWindow->setWindowTitle(QApplication::translate("JFCWindow", "JFCWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class JFCWindow: public Ui_JFCWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JFCWINDOW_H
