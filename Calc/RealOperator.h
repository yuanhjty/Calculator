#ifndef REAL_OPERATORS_H
#define REAL_OPERATORS_H

#include "ExprNode.h"


class Plus : public LeftAssoBinaryOperator {
public:
    Plus();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Plus::Plus() {
    _attrs |= PRIO_PLUS;
}


class BMinus : public LeftAssoBinaryOperator {
public:
    BMinus();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline BMinus::BMinus() {
    _attrs |= PRIO_PLUS;
}


class Mult : public LeftAssoBinaryOperator {
public:
    Mult();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Mult::Mult() {
    _attrs |= PRIO_MULTI;
}


class Divide : public LeftAssoBinaryOperator {
public:
    Divide();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Divide::Divide() {
    _attrs |= PRIO_MULTI;
}


class Modulo : public LeftAssoBinaryOperator {
public:
    Modulo();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Modulo::Modulo() {
    _attrs |= PRIO_MULTI;
}


class Power : public RightAssoBinaryOperator {
public:
    Power();
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};

inline Power::Power() {
    _attrs |= PRIO_POW;
}


// All postfix operators have the same priority PRIO_POSTFIX
class Fact : public PostfixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


// All prefix operators have the same priority PRIO_PREFIX
class UMinus : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


// Rrigonometric function
class Sin : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Cos : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Tan : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Asin : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Acos : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Atan : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


// Logarithmic function
class Lg : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


class Ln : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


// Square root function
class Sqrt : public PrefixOperator {
public:
    ExprNode::ValueType evaluate() override;
    ExprNode *newNode() const override;
};


#endif // REAL_OPERATORS_H
