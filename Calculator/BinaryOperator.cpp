#include "BinaryOperator.h"
#include "ExpressionException.h"

#include <cmath>


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
        throw InnerError("inner error: BinaryOperator::build() failed due to invalid argument");
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



// Plus
double Plus::evaluate() {
    return m_left->evaluate() + m_right->evaluate();
}

PRIORITY Plus::priority() {
    return PRIO_PLUS;
}

ExpressionTree *Plus::clone() {
    return new Plus;
}


// BMinus
double BMinus::evaluate() {
    return m_left->evaluate() - m_right->evaluate();
}

PRIORITY BMinus::priority() {
    return PRIO_PLUS;
}

ExpressionTree *BMinus::clone() {
    return new BMinus;
}


// Multi
double Multi::evaluate() {
    return m_left->evaluate() * m_right->evaluate();
}

PRIORITY Multi::priority() {
    return PRIO_MULTI;
}

ExpressionTree *Multi::clone() {
    return new Multi;
}


// Divide
double Divide::evaluate() {
    double divisor = m_right->evaluate();
    if (0 == divisor)
        throw DivideByZero("divide-by-zero");

    return m_left->evaluate() / divisor;
}

PRIORITY Divide::priority() {
    return PRIO_MULTI;
}

ExpressionTree *Divide::clone() {
    return new Divide;
}


// Pow
double Power::evaluate() {
    return std::pow(m_left->evaluate(), m_right->evaluate());
}

PRIORITY Power::priority() {
    return PRIO_POW;
}

ExpressionTree *Power::clone() {
    return new Power;
}


// Modulo
double Modulo::evaluate() {
    double divisor = m_right->evaluate();
    if (0 == divisor)
        throw DivideByZero("divide-by-zero");

    double dividend = m_left->evaluate();

    double intpart = 0;
    std::modf(dividend / divisor, &intpart);

    return dividend - intpart * divisor;
}

PRIORITY Modulo::priority() {
    return PRIO_MULTI;
}

ExpressionTree *Modulo::clone() {
    return new Modulo;
}


// BitAnd
double BitAnd::evaluate() {
    return Util::toFloat((Util::toInteger(m_left->evaluate())
                          & Util::toInteger(m_right->evaluate())));
}

PRIORITY BitAnd::priority() {
    return PRIO_BIT_AND;
}

ExpressionTree *BitAnd::clone() {
    return new BitAnd;
}


// BitOr
double BitOr::evaluate() {
    return Util::toFloat((Util::toInteger(m_left->evaluate())
                          | Util::toInteger(m_right->evaluate())));
}

PRIORITY BitOr::priority() {
    return PRIO_BIT_OR;
}

ExpressionTree *BitOr::clone() {
    return new BitOr;
}


// BitXor
double BitXor::evaluate() {
    return Util::toFloat((Util::toInteger(m_left->evaluate())
                          ^ Util::toInteger(m_right->evaluate())));
}

PRIORITY BitXor::priority() {
    return PRIO_BIT_XOR;
}

ExpressionTree *BitXor::clone() {
    return new BitXor;
}
