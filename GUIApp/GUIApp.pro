#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T16:20:51
#
#-------------------------------------------------

QT       += core gui
RC_ICONS += calculator.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        CalcWidget.cpp \
    ../Calculator/BinaryOperator.cpp \
    ../Calculator/Calculator.cpp \
    ../Calculator/CommandInterpreter.cpp \
    ../Calculator/ExpressionTree.cpp \
    ../Calculator/LexicalSet.cpp \
    ../Calculator/Operand.cpp \
    ../Calculator/Parser.cpp \
    ../Calculator/Scanner.cpp \
    ../Calculator/ScientificCalculator.cpp \
    ../Calculator/UnaryOperator.cpp \
    CalcButton.cpp \
    ../Calculator/SymbolTable.cpp

HEADERS += \
        CalcWidget.h \
    ../Calculator/BinaryOperator.h \
    ../Calculator/Calculator.h \
    ../Calculator/CommandInterpreter.h \
    ../Calculator/Expression.h \
    ../Calculator/ExpressionTree.h \
    ../Calculator/LexicalSet.h \
    ../Calculator/Operand.h \
    ../Calculator/Parser.h \
    ../Calculator/Scanner.h \
    ../Calculator/ScientificCalculator.h \
    ../Calculator/UnaryOperator.h \
    CalcButton.h \
    ../Calculator/SymbolTable.h \
    ../Calculator/ExpressionException.h

FORMS += \
        CalcWidget.ui

RESOURCES += \
    images.qrc
