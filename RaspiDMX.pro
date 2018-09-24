#-------------------------------------------------
#
# Project created by QtCreator 2018-09-24T10:07:31
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaspiDMX
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    button.cpp \
    lights.cpp \
    sensors.cpp

HEADERS  += mainwindow.h \
    button.h \
    sensors.h

FORMS    += mainwindow.ui
LIBS += -lpigpio

