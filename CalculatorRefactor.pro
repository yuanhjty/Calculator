TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Scanner.cpp \
    Parser.cpp \
    Util.cpp \
    CmdCalculator.cpp \
    Calculator.cpp \
    BinaryOperator.cpp \
    UnaryOperator.cpp \
    Function.cpp \
    CommandInterpreter.cpp \
    ScientificCalculator.cpp

HEADERS += \
    Calculator.h \
    Scanner.h \
    Parser.h \
    Util.h \
    Expression.h \
    BinaryOperator.h \
    UnaryOperator.h \
    Function.h \
    Operand.h \
    CommandInterpreter.h \
    ScientificCalculator.h \
    Operator.h

DISTFILES += \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.ilk \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.pdb \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.vc.pdb \
    build/Desktop_Qt_5_6_2_MSVC2015_64bit/debug/CalculatorRefactor.exe \
    .gitignore \
    commit-description.txt
