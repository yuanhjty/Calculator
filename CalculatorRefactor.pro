TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Scanner.cpp \
    Parser.cpp \
    Util.cpp \
    CmdCalculator.cpp \
    ScientificCalculator.cpp \
    ExpressionTree.cpp \
    Calculator.cpp \
    CalculatorManager.cpp

HEADERS += \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Util.h \
    ScientificCalculator.h \
    ExpressionTree.h \
    CalculatorManager.h
