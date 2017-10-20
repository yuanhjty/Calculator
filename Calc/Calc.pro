TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ExprNode.cpp \
    Calculator.cpp \
    Scanner.cpp \
    Lexeme.cpp \
    SymbolTable.cpp \
    RealOperator.cpp \
    Operand.cpp \
    CalcError.cpp \
    CalcResult.cpp \
    BitwiseOperator.cpp \
    Converter.cpp \
    TreeParser.cpp \
    NumeralFormat.cpp \
    TableParser.cpp \
    UnitTable.cpp \
    ExprCalculator.cpp \
    test.cpp \
    Interpreter.cpp

HEADERS += \
    ExprNode.h \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Lexeme.h \
    SymbolTable.h \
    RealOperator.h \
    Operand.h \
    CalcFlags.h \
    CalcError.h \
    CalcResult.h \
    BitwiseOperator.h \
    Converter.h \
    TreeParser.h \
    NumeralFormat.h \
    UnitTable.h \
    TableParser.h \
    ExprCalculator.h \
    Interpreter.h
