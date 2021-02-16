#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T00:00:33
#
#-------------------------------------------------

QT       += widgets testlib

QT       -= gui

TARGET = tst_huntertesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_huntertesttest.cpp \
    gamemanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    gamemanager.h
