TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Calculator.cpp \
    Scanner.cpp \
    Parser.cpp \
    Expression.cpp \
    Manager.cpp \
    Util.cpp

HEADERS += \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Expression.h \
    Manager.h \
    Util.h
