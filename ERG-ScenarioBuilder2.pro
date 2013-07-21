#-------------------------------------------------
#
# Project created by QtCreator 2013-07-10T12:52:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ERG-ScenarioBuilder2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    floorwidget.cpp \
    scenario.cpp \
    floortile.cpp \
    test_environment.cpp

HEADERS  += mainwindow.h \
    floorwidget.h \
    scenario.h \
    floortile.h \
    test_environment.h \
    exception.h \
    main_directory.h \
    registry.h

FORMS    += mainwindow.ui \
    floorwidget.ui \
    floortile.ui
