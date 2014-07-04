#-------------------------------------------------
#
# Project created by QtCreator 2014-06-28T21:41:34
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    simulator.cpp \
    datafile.cpp \
    simplecamera.cpp

HEADERS  += mainwindow.h \
    simulator.h \
    datafile.h \
    simplecamera.h

FORMS    += mainwindow.ui

#LIBS += -lglut -lGLU
#INCLUDEPATH += ./externals/glm-0.9.5.4
