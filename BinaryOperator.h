#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H


#include "Expression.h"


// For real operation
// The class RealBinaryOperator
class RealBinaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_left;
    ExpressionTree *m_right;

public:
    RealBinaryOperator(ExpressionTree* left, ExpressionTree* right);
    ~RealBinaryOperator();
};


// The class Plus
class Plus : public RealBinaryOperator {
public:
    Plus(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// The class BMinus
class BMinus : public RealBinaryOperator {
public:
    BMinus(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// The class Multiple
class Multiple : public RealBinaryOperator {
public:
    Multiple(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// The class Divide
class Divide : public RealBinaryOperator {
public:
    Divide(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// For integer only operation
// The class IntegerBinaryOperator
class IntegerBinaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_left = nullptr;
    ExpressionTree *m_right = nullptr;
    long long m_integerLeft = 0;
    long long m_integerRight = 0;

public:
    IntegerBinaryOperator(ExpressionTree* left, ExpressionTree* right);
    ~IntegerBinaryOperator();

private:
    void makeIntegerOperands();
};


// The class Modulo
class Modulo : public IntegerBinaryOperator {
public:
    Modulo(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// For bitwise opoeration
// The class BitAnd
class BitAnd : public IntegerBinaryOperator {
public:
    BitAnd(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// The class BitOr
class BitOr : public IntegerBinaryOperator {
public:
    BitOr(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


// The class BitXor
class BitXor : public IntegerBinaryOperator {
public:
    BitXor(ExpressionTree* left, ExpressionTree* right);
    double evaluate() override;
};


#endif // BINARY_OPERATOR_H
