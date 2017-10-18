TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ExprNode.cpp \
    Calculator.cpp \
    Scanner.cpp \
    ScienceCalculator.cpp \
    Parser.cpp \
    Lexeme.cpp \
    SymbolTable.cpp \
    RealOperator.cpp \
    Operand.cpp \
    CalcError.cpp \
    CalcResult.cpp \
    DataConvert.cpp

HEADERS += \
    ExprNode.h \
    Calculator.h \
    Scanner.h \
    ScienceCalculator.h \
    Parser.h \
    Lexeme.h \
    SymbolTable.h \
    RealOperator.h \
    Operand.h \
    CalcFlags.h \
    CalcError.h \
    CalcResult.h \
    DataConvert.h
