TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        rotor.cpp \
        rotor2.cpp \
        rotor3.cpp \
        stator.cpp

HEADERS += \
    generator.h \
    rotor.h \
    rotor2.h \
    rotor3.h \
    stator.h
