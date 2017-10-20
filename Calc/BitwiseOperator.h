#ifndef BITWISE_OPERATOR_H
#define BITWISE_OPERATOR_H

#include "ExprNode.h"


class BitAnd : public LeftAssoBinaryOperator {
public:
    BitAnd();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline BitAnd::BitAnd() {
    _attrs |= PRIO_BIT_AND;
}


class BitOr : public LeftAssoBinaryOperator {
public:
    BitOr();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline BitOr::BitOr() {
    _attrs |= PRIO_BIT_OR;
}


class BitXor : public LeftAssoBinaryOperator {
public:
    BitXor();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline BitXor::BitXor() {
    _attrs |= PRIO_BIT_XOR;
}


class Lsh : public LeftAssoBinaryOperator {
public:
    Lsh();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Lsh::Lsh() {
    _attrs |= PRIO_BIT_SHIFT;
}


class Rsh : public LeftAssoBinaryOperator {
public:
    Rsh();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Rsh::Rsh() {
    _attrs |= PRIO_BIT_SHIFT;
}


class BitNot : public PrefixOperator {
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


#endif // BITWISE_OPERATOR_H
