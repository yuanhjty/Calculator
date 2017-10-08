#include "ExpressionTree.h"

#include <stdexcept>



// Util
long long Util::toInteger(double value) {
    if (!isDblToLLongValid(value))
        throw std::logic_error("error: integer overflow");
    return (long long)value;
}

double Util::toFloat(long long value) {
    if (!isLLongToDblValid(value))
        throw std::logic_error("error: integer overflow");
    return (double)value;
}



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
        throw std::runtime_error("inner error: build ExpressionTree failed");
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



// UnaryOperator
UnaryOperator::~UnaryOperator() {
    if (m_child) delete m_child;
}

int UnaryOperator::childCount() const {
    return 1;
}

void UnaryOperator::build(const std::vector<ExpressionTree*>& param) {
    if (param.size() != 1)
        throw std::runtime_error("inner error: build ExpressionTree failed");
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
