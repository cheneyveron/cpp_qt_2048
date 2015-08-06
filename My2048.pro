#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T15:27:27
#
#-------------------------------------------------

QT       += core gui opengl
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = My2048
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    GameWidget.cpp \
    gameover.cpp \
    menu.cpp \
    about.cpp \
    help.cpp \
    startup.cpp \
    dialog.cpp

HEADERS  += widget.h \
    GameWidget.h \
    gameover.h \
    menu.h \
    about.h \
    help.h \
    startup.h \
    dialog.h

CONFIG += mobility
MOBILITY = 

FORMS += \
    gameover.ui \
    menu.ui \
    about.ui \
    help.ui \
    startup.ui \
    win.ui

RESOURCES += \
    pic.qrc

DISTFILES +=

