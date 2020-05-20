TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        clog.cpp \
        cmain.cpp \
        cthread.cpp \
        main.cpp \
        mysocket.cpp

HEADERS += \
    _system.h \
    clog.h \
    cmain.h \
    cthread.h \
    mysocket.h \
    tcpip.h

QMAKE_CXXFLAGS += -std=c++0x -pthread

LIBS += -pthread
