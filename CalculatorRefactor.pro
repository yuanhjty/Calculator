TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Calculator.cpp \
    Scanner.cpp \
    Parser.cpp \
    Command.cpp \
    Expression.cpp \
    Manager.cpp

HEADERS += \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Command.h \
    Expression.h \
    Manager.h
