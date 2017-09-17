TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Expression.cpp \
    ExpressionUtil.cpp

HEADERS += \
    Calculator.h \
    Expression.h \
    ExpressionUtil.h
