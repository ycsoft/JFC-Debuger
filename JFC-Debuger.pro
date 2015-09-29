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
    command/qdevicecommand.cpp \
    core/hfpgsql.cpp \
    command/qparse.cpp \
    udp/qudpgroup.cpp \
    net/qnetwork.cpp

HEADERS  += jfcwindow.h \
    core/qhfwebview.h \
    jsCore/qjscore.h \
    command/qdevicecommand.h \
    core/hfpgsql.h \
    command/qparse.h \
    udp/qudpgroup.h \
    net/qnetwork.h

FORMS    += jfcwindow.ui

#RESOURCES += \
#    res.qrc
INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\WIN32-Code"
INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\include"
INCLUDEPATH += "D:\PostgreSQL\9.3\include"
LIBS += "D:\PostgreSQL\9.3\lib\libpq.lib"
