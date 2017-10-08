TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../Calculator/BinaryOperator.cpp \
    ../Calculator/Calculator.cpp \
    ../Calculator/CommandInterpreter.cpp \
    ../Calculator/ExpressionTree.cpp \
    ../Calculator/LexicalSet.cpp \
    ../Calculator/Operand.cpp \
    ../Calculator/OperatorTable.cpp \
    ../Calculator/Parser.cpp \
    ../Calculator/Scanner.cpp \
    ../Calculator/ScientificCalculator.cpp \
    ../Calculator/UnaryOperator.cpp

HEADERS += \
    ../Calculator/BinaryOperator.h \
    ../Calculator/Calculator.h \
    ../Calculator/CommandInterpreter.h \
    ../Calculator/Expression.h \
    ../Calculator/ExpressionTree.h \
    ../Calculator/LexicalSet.h \
    ../Calculator/Operand.h \
    ../Calculator/OperatorTable.h \
    ../Calculator/Parser.h \
    ../Calculator/Scanner.h \
    ../Calculator/ScientificCalculator.h \
    ../Calculator/UnaryOperator.h
