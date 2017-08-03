#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T18:55:43
#
#-------------------------------------------------

QT       += core gui
QT       += bluetooth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A_for_w8
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    devicemanager.cpp

HEADERS  += widget.h \
    devicemanager.h

FORMS    += widget.ui \
    devicemanager.ui

CONFIG += mobility
MOBILITY = 

