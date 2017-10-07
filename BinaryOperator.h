#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H


#include "Expression.h"


// The class Plus
class Plus : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class BMinus
class BMinus : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class Multi
class Multi : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class Divide
class Divide : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class Pow
class Pow : public RightAssoOperator {
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class Modulo
class Modulo : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class BitAnd
class BitAnd : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class BitOr
class BitOr : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


// The class BitXor
class BitXor : public LeftAssoOperator {
public:
    double evaluate() override;
    PRIORITY priority() override;
    ExpressionTree* clone() override;
};


#endif // BINARY_OPERATOR_H
