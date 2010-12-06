#-------------------------------------------------
#
# Project created by QtCreator 2010-11-30T21:25:54
#
#-------------------------------------------------

QT       += core gui

QT       += sql #增加SQL支持

TARGET = TraceAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        traceanalyzer.cpp \
    action.cpp \
    actionpage.cpp

HEADERS  += traceanalyzer.h \
    DBconnection.h \
    action.h \
    actionpage.h

FORMS    += traceanalyzer.ui \
    actionpage.ui
