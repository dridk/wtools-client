#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T14:05:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wtools-gui
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    WTools.cpp \
    Request.cpp \
    FieldsModel.cpp \
    VariantModel.cpp \
    LogicModel.cpp \
    LogicView.cpp \
    LogicDelegate.cpp \
    ConditionWidget.cpp

HEADERS  += MainWindow.h \
    WTools.h \
    Request.h \
    FieldsModel.h \
    VariantModel.h \
    LogicModel.h \
    LogicView.h \
    LogicDelegate.h \
    ConditionWidget.h

FORMS    += MainWindow.ui
