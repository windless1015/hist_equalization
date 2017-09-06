#-------------------------------------------------
#
# Project created by QtCreator 2017-08-28T16:52:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = img_process
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    displaywidget.cpp \
    histwidget.cpp \
    imgalgorithm.cpp

HEADERS  += maindialog.h \
    displaywidget.h \
    histwidget.h \
    imgalgorithm.h

FORMS    += \
    displaywidget.ui \
    histwidget.ui
