#include "ExpressionTree.h"

#include <exception>
#include <stdexcept>


// BinaryOperator
BinaryOperator::~BinaryOperator() {
    if (m_left) delete m_left;
    if (m_right) delete m_right;
}

void BinaryOperator::build(ExpressionTree *left, ExpressionTree *right) {
    m_left = left; m_right = right;
}


// LeftAssoOperator
ASSOCIATIVITY LeftAssoOperator::associativity() {
    return ASSO_LEFT;
}


// LeftAssoOperator
ASSOCIATIVITY RightAssoOperator::associativity() {
    return ASSO_RIGHT;
}


// IntegerBinaryOperator
void IntegerBinaryOperator::build(ExpressionTree *left, ExpressionTree *right) {
    BinaryOperator::build(left, right);
    makeIntegerOperands();
}

void IntegerBinaryOperator::makeIntegerOperands() {
    double left = m_left->evaluate();
    double right = m_right->evaluate();

    if (!(Util::isDblToLLongValid(left) && Util::isDblToLLongValid(right)))
        throw std::logic_error("Integer Overflow");

    m_integerLeft = (long long)left;
    m_integerRight = (long long)right;
}


// IntegerLeftAssoOperator
ASSOCIATIVITY IntegerLeftAssoOperator::associativity() {
    return ASSO_LEFT;
}


// IntegerRightAssoOperator
ASSOCIATIVITY IntegerRightAssoOperator::associativity() {
    return ASSO_RIGHT;
}


// UnaryOperator
UnaryOperator::~UnaryOperator() {
    if (m_child) delete m_child;
}

void UnaryOperator::build(ExpressionTree *child) {
    m_child = child;
}


// PrefixOperator
PRIORITY PrefixOperator::priority() {
    return PRIO_PREFIX;
}

ASSOCIATIVITY PrefixOperator::associativity() {
    return ASSO_RIGHT;
}


// PostfixOperator
PRIORITY PostfixOperator::priority() {
    return PRIO_POSTFIX;
}

ASSOCIATIVITY PostfixOperator::associativity() {
    return ASSO_LEFT;
}


// IntegerUnaryOperator
void IntegerUnaryOperator::build(ExpressionTree *child) {
    UnaryOperator::build(child);
    makeIntegerOperand();
}

void IntegerUnaryOperator::makeIntegerOperand() {
    double child = m_child->evaluate();

    if (!Util::isDblToLLongValid(child))
        throw std::logic_error("Integer Overflow");

    m_integerChild = (long long)child;
}


// IntegerPrefixOperator
PRIORITY IntegerPrefixOperator::priority() {
    return PRIO_PREFIX;
}

ASSOCIATIVITY IntegerPrefixOperator::associativity() {
    return ASSO_RIGHT;
}


// IntegerPostfixOperator
PRIORITY IntegerPostfixOperator::priority() {
    return PRIO_POSTFIX;
}

ASSOCIATIVITY IntegerPostfixOperator::associativity() {
    return ASSO_LEFT;
}
