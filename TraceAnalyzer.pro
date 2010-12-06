#-------------------------------------------------
#
# Project created by QtCreator 2010-11-30T21:25:54
#
#-------------------------------------------------

QT       += core gui

QT       += sql #����SQL֧��

TARGET = TraceAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        traceanalyzer.cpp \
    action.cpp \
    server.cpp \
    simsce.cpp \
    out.cpp \
    inter_arrival.cpp \
    interestconct.cpp \
    step1.cpp \
    func.cpp \
    step2.cpp

HEADERS  += traceanalyzer.h \
    DBconnection.h \
    action.h \
    server.h \
    simsce.h \
    out.h \
    inter_arrival.h \
    interestconct.h \
    step1.h \
    func.h \
    step2.h

FORMS    += traceanalyzer.ui \
    step1.ui \
    step2.ui
