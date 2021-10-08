TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        checking.cpp \
        cipher.cpp \
        installation.cpp

HEADERS += \
    checking.h \
    cipher.h

LIBS += -lIphlpapi
