#-------------------------------------------------
#
# Project created by QtCreator 2015-01-13T21:01:42
#
#-------------------------------------------------

QT       += core gui positioning network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GeoTrans
TEMPLATE = app


SOURCES += main.cpp\
        geotrans.cpp \
    cnmeagen.cpp

HEADERS  += geotrans.h \
    cnmeagen.h

FORMS    += geotrans.ui

CONFIG += mobility
MOBILITY = 



