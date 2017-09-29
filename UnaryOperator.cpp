#include "UnaryOperator.h"
#include "Util.h"


// RealUnaryOperator
RealUnaryOperator::RealUnaryOperator(ExpressionTree *right) :
    m_right(right) {}

RealUnaryOperator::~RealUnaryOperator() {
    if (m_right) delete m_right;
}


// UMinus
UMinus::UMinus(ExpressionTree *right) :
    RealUnaryOperator(right) {}

double UMinus::evaluate() {
    return -m_right->evaluate();
}


// For integer only operation
// IntegerUnrayOperator
IntegerUnaryOperator::IntegerUnaryOperator(ExpressionTree *right) :
    m_right(right) {
    makeIntegerOperand();
}

IntegerUnaryOperator::~IntegerUnaryOperator() {
    if (m_right) delete m_right;
}

void IntegerUnaryOperator::makeIntegerOperand() {
    double right = m_right->evaluate();

    if (!Util::isDblToLLongValid(right))
        throw std::logic_error("Integer Overflow");

    m_integerRight = (long long)right;
}


// For bitwise operation
// BitNot
BitNot::BitNot(ExpressionTree *right) :
    IntegerUnaryOperator(right) {}

double BitNot::evaluate() {
    return ~m_integerRight;
}
