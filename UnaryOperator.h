#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H


#include "ExpressionTree.h"

#include <string>
#include <memory>


// For real operation
// The class RealUnaryOperator
class RealUnaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_right = nullptr;

public:
    RealUnaryOperator(ExpressionTree* right);
    ~RealUnaryOperator();
};


// The class UMinus
class UMinus : public RealUnaryOperator {
public:
    UMinus(ExpressionTree* right);
    double evaluate() override;
};


// For integer only operation
// The class IntegerUnaryOperator
class IntegerUnaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_right = nullptr;
    long long m_integerRight = 0;

public:
    IntegerUnaryOperator(ExpressionTree* right);
    ~IntegerUnaryOperator();

private:
    void makeIntegerOperand();
};


// For bitwise operation
// The class BitNot
class BitNot : public IntegerUnaryOperator {
public:
    BitNot(ExpressionTree* right);
    double evaluate() override;
};


#endif // UNARY_OPERATOR_H
