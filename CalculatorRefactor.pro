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
    Calculator.cpp \
    CalculatorManager.cpp \
    BinaryOperator.cpp \
    UnaryOperator.cpp \
    Function.cpp \
    Expression.cpp

HEADERS += \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Util.h \
    ScientificCalculator.h \
    CalculatorManager.h \
    Expression.h \
    ExpressionTree.h \
    BinaryOperator.h \
    UnaryOperator.h \
    Function.h \
    Operand.h

DISTFILES += \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.ilk \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.pdb \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.vc.pdb \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.exe \
    .gitignore \
    commit-description.txt
