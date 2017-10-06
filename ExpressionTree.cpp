#include "ExpressionTree.h"

#include <exception>
#include <stdexcept>


// BinaryOperator
BinaryOperator::~BinaryOperator() {
    if (m_left) delete m_left;
    if (m_right) delete m_right;
}

int BinaryOperator::childCount() const {
    return 2;
}

void BinaryOperator::build(const std::vector<ExpressionTree*>& param) {
    if (param.size() != 2)
        throw std::exception("Inner error: build ExpressionTree failed");
    m_left = param[1]; m_right = param[0];
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
void IntegerBinaryOperator::build(const std::vector<ExpressionTree*>& param){
    BinaryOperator::build(param);
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

int UnaryOperator::childCount() const {
    return 1;
}

void UnaryOperator::build(const std::vector<ExpressionTree*>& param) {
    if (param.size() != 1)
        throw std::exception("Inner error: build ExpressionTree failed");
    m_child = param[0];
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
void IntegerUnaryOperator::build(const std::vector<ExpressionTree*>& param) {
    UnaryOperator::build(param);
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
