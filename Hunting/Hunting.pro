#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T23:53:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hunting
TEMPLATE = app


SOURCES += main.cpp\
        hunter.cpp \
    gamemanager.cpp \
    hunterdataaccess.cpp \
    savegamewidget.cpp \
    loadgamewidget.cpp

HEADERS  += hunter.h \
    gamemanager.h \
    hunterdataaccess.h \
    savegamewidget.h \
    loadgamewidget.h
