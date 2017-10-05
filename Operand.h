#ifndef OPERAND_H
#define OPERAND_H


#include "Expression.h"

#include <map>
#include <string>
#include <exception>


std::map<std::string, double> varTable = {
    {"e", 2.71828183}, {"E", 2.71828183},
    {"pi", 3.14159265}, {"Pi", 3.14159265}, {"PI", 3.14159265}
};

class Number : public ExpressionTree {
private:
    double m_value = 0;
public:
    Number(double value) : m_value(value) {}

    double evaluate() override {
        return m_value;
    }
};

//class ConstE : ExpressionTree {
//public:
//    double evaluate() override {
//        return 2.71828183;
//    }
//};


//class ConstPi : ExpressionTree {
//public:
//    double evaluate() override {
//        return 3.14159265;
//    }
//};


#endif // OPERAND_H
