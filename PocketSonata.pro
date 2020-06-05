TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        clog.cpp \
        cmain.cpp \
        cprompt.cpp \
        creclan.cpp \
        cthread.cpp \
        curbit.cpp \
        dev/minIni.c \
        main.cpp \
        mysocket.cpp

HEADERS += \
    _sysmsg.h \
    _system.h \
    clog.h \
    cmain.h \
    cprompt.h \
    creclan.h \
    cthread.h \
    curbit.h \
    dev/minGlue-FatFs.h \
    dev/minGlue-ccs.h \
    dev/minGlue-efsl.h \
    dev/minGlue-ffs.h \
    dev/minGlue-mdd.h \
    dev/minGlue-stdio.h \
    dev/minGlue.h \
    dev/minIni.h \
    dev/wxMinIni.h \
    mysocket.h \
    tcpip.h

QMAKE_CXXFLAGS += -std=c++0x -pthread

LIBS += -pthread
LIBS += -lreadline

INCLUDEPATH += $$PWD/include


