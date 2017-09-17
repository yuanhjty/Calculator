#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <string>
#include "Expression.h"


class Calculator {
public:
    Calculator() : _expression(new Expression) {}

    ~Calculator() {
        if (_expression) delete _expression;
    }

    void reset() {
        _expression->reset();
    }

    void setInfix(const std::string& expression) {
        _expression->setInfix(expression);
    }

    void setPostfix() {
        _expression->setPostfix();
    }

    void evaluate() {
        _expression->evaluate();
    }

    std::string getInfix() const {
        return _expression->getInfix();
    }

    std::string getPostfix() const {
        return _expression->getPostfix();
    }

    double getResult() const {
        return _expression->getResult();
    }

private:
    Expression* _expression;
};


#endif // CALCULATOR_H
