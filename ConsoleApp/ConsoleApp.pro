TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../Calc/BitwiseOperator.cpp \
    ../Calc/CalcError.cpp \
    ../Calc/CalcResult.cpp \
    ../Calc/Calculator.cpp \
    ../Calc/Converter.cpp \
    ../Calc/ExprCalculator.cpp \
    ../Calc/ExprNode.cpp \
    ../Calc/Lexeme.cpp \
    ../Calc/NumeralFormat.cpp \
    ../Calc/Operand.cpp \
    ../Calc/RealOperator.cpp \
    ../Calc/Scanner.cpp \
    ../Calc/SymbolTable.cpp \
    ../Calc/TableParser.cpp \
    ../Calc/TreeParser.cpp \
    ../Calc/UnitTable.cpp \
    ../Calc/Interpreter.cpp

HEADERS += \
    ../Calc/BitwiseOperator.h \
    ../Calc/CalcError.h \
    ../Calc/CalcFlags.h \
    ../Calc/CalcResult.h \
    ../Calc/Calculator.h \
    ../Calc/Converter.h \
    ../Calc/ExprCalculator.h \
    ../Calc/ExprNode.h \
    ../Calc/Lexeme.h \
    ../Calc/NumeralFormat.h \
    ../Calc/Operand.h \
    ../Calc/Parser.h \
    ../Calc/RealOperator.h \
    ../Calc/Scanner.h \
    ../Calc/SymbolTable.h \
    ../Calc/TableParser.h \
    ../Calc/TreeParser.h \
    ../Calc/UnitTable.h \
    ../Calc/Interpreter.h
