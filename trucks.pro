#-------------------------------------------------
#
# Project created by QtCreator 2014-06-01T19:45:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trucks
TEMPLATE = app


SOURCES += main.cpp\
    trucks.cpp \
    properties.cpp \
    scene.cpp \
    view.cpp \
    link.cpp \
    node.cpp \
    truck.cpp

HEADERS  += \
    common.h \
    trucks.h \
    properties.h \
    view.h \
    scene.h \
    link.h \
    node.h \
    truck.h

FORMS    += \
    trucks.ui

RESOURCES += \
    trucks.qrc
