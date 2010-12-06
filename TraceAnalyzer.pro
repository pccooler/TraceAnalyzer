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
    serverpage.cpp \
    server.cpp \
    simsce.cpp \
    out.cpp \
    inter_arrival.cpp \
    interestconct.cpp \
    step1.cpp \
    func.cpp

HEADERS  += traceanalyzer.h \
    DBconnection.h \
    action.h \
    serverpage.h \
    server.h \
    simsce.h \
    out.h \
    inter_arrival.h \
    interestconct.h \
    step1.h \
    func.h

FORMS    += traceanalyzer.ui \
    serverpage.ui \
    step1.ui
