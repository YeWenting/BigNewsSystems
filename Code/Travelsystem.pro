#-------------------------------------------------
#
# Project created by QtCreator 2016-05-22T14:48:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = version10
TEMPLATE = app


SOURCES += main.cpp\
        travelsystem.cpp \
    dialog.cpp \
    people.cpp \
    trafficNet.cpp \
    rightlist.cpp \
    LeftList.cpp \
    dialogchange.cpp \
    lcdclock.cpp \
    dialogerror.cpp \
    livemap.cpp \
    blink.cpp \
    blinkline.cpp \
    dialogerror2.cpp

HEADERS  += travelsystem.h \
    dialog.h \
    people.h \
    trafficNet.h \
    rightlist.h \
    LeftList.h \
    dialogchange.h \
    lcdclock.h \
    dialogerror.h \
    livemap.h \
    blink.h \
    blinkLine.h \
    dialogerror2.h

FORMS += \
    dialog.ui \
    dialogchange.ui \
    lcdclock.ui \
    dialogerror.ui \
    livemap.ui \
    dialogerror2.ui

RESOURCES += \
    picture.qrc
