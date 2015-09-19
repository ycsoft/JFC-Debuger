#-------------------------------------------------
#
# Project created by QtCreator 2015-09-19T10:35:25
#
#-------------------------------------------------

QT       += core gui network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JFC-Debuger
TEMPLATE = app


SOURCES += main.cpp\
        jfcwindow.cpp \
    core/qhfwebview.cpp \
    jsCore/qjscore.cpp \
    command/qdevicecommand.cpp

HEADERS  += jfcwindow.h \
    core/qhfwebview.h \
    jsCore/qjscore.h \
    command/qdevicecommand.h

FORMS    += jfcwindow.ui

RESOURCES += \
    res.qrc
