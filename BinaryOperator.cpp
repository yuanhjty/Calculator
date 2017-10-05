#include "BinaryOperator.h"
#include "Util.h"

#include <exception>


// BinaryOperator
RealBinaryOperator::RealBinaryOperator(ExpressionTree *left, ExpressionTree *right) :
    m_left(left), m_right(right) {
}

RealBinaryOperator::~RealBinaryOperator() {
    if (m_left) delete m_left;
    if (m_right) delete m_right;
}


// Plus
Plus::Plus(ExpressionTree *left, ExpressionTree *right) :
    RealBinaryOperator(left, right) {}

double Plus::evaluate() {
    return m_left->evaluate() + m_right->evaluate();
}


// BMinus
BMinus::BMinus(ExpressionTree *left, ExpressionTree *right) :
    RealBinaryOperator(left, right) {}

double BMinus::evaluate() {
    return m_left->evaluate() - m_right->evaluate();
}


// Multiple
Multi::Multi(ExpressionTree *left, ExpressionTree *right) :
    RealBinaryOperator(left, right) {}

double Multi::evaluate() {
    return m_left->evaluate() * m_right->evaluate();
}


// Divide
Divide::Divide(ExpressionTree *left, ExpressionTree *right) :
    RealBinaryOperator(left, right) {}

double Divide::evaluate() {
    double divisor = m_right->evaluate();
    if (0 == divisor)
        throw std::logic_error("Division by zero error");

    return m_left->evaluate() / divisor;
}


// Integer
// IntegerBinaryOperator
IntegerBinaryOperator::IntegerBinaryOperator(ExpressionTree *left, ExpressionTree *right) :
    m_left(left), m_right(right) {
    makeIntegerOperands();
}

IntegerBinaryOperator::~IntegerBinaryOperator() {
    if (m_left) delete m_left;
    if (m_right) delete m_right;
}

void IntegerBinaryOperator::makeIntegerOperands() {
    double left = m_left->evaluate();
    double right = m_right->evaluate();

    if (!(Util::isDblToLLongValid(left) && Util::isDblToLLongValid(right)))
        throw std::logic_error("Integer Overflow");

    m_integerLeft = (long long)left;
    m_integerRight = (long long)right;
}

// Modulo
Modulo::Modulo(ExpressionTree *left, ExpressionTree *right) :
    IntegerBinaryOperator(left, right) {}

double Modulo::evaluate() {
    if (0 == m_integerRight)
        throw std::logic_error("Division By Zero");

    return m_integerLeft % m_integerRight;
}


// Bitwise operation
// BitAnd
BitAnd::BitAnd(ExpressionTree *left, ExpressionTree *right) :
    IntegerBinaryOperator(left, right) {}

double BitAnd::evaluate() {
    return m_integerLeft & m_integerRight;
}


// BitOr
BitOr::BitOr(ExpressionTree *left, ExpressionTree *right) :
    IntegerBinaryOperator(left, right) {}

double BitOr::evaluate() {
    return m_integerLeft | m_integerRight;
}


// BitXor
BitXor::BitXor(ExpressionTree *left, ExpressionTree *right) :
    IntegerBinaryOperator(left, right) {}

double BitXor::evaluate() {
    return m_integerLeft ^ m_integerRight;
}
