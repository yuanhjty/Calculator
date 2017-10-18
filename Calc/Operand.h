#ifndef OPERANDS_H
#define OPERANDS_H

#include "ExprNode.h"

class Number : public Operand{
public:
    Number(ValueType value);
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;

private:
    ValueType _value = 0;
};

inline Number::Number(ValueType value) : _value(value) { }


class ConstPi : public Operand {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class ConstE : public Operand {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


#endif // OPERANDS_H
