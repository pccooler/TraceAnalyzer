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
    server.cpp \
    simsce.cpp \
    out.cpp \
    inter_arrival.cpp \
    interestconct.cpp \
    step1.cpp \
    func.cpp \
    step2.cpp \
    step3.cpp \
    step4.cpp

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
    step2.h \
    step3.h \
    step4.h

FORMS    += traceanalyzer.ui \
    step1.ui \
    step2.ui \
    step3.ui \
    step4.ui


#-------------------------------------------------
#
# QWT
#
#-------------------------------------------------
QWT_ROOT = ../..
include( $${QWT_ROOT}/qwtconfig.pri )
include( $${QWT_ROOT}/qwtbuild.pri )

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

contains(QWT_CONFIG, QwtFramework) {

    LIBS      += -F$${QWT_ROOT}/lib
}
else {

    LIBS      += -L$${QWT_ROOT}/lib
}

IPATH       = $${INCLUDEPATH}
qtAddLibrary(qwt)
INCLUDEPATH = $${IPATH}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES    += QT_DLL QWT_DLL
    }
}
