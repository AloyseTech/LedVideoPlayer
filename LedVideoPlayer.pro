#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T11:11:47
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LedVideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    surface.cpp \
    ledbar.cpp

HEADERS  += mainwindow.h \
    surface.h \
    ledbar.h

FORMS    += mainwindow.ui

QMAKE_AR += -v

mac: QMAKE_INFO_PLIST = Info.plist
