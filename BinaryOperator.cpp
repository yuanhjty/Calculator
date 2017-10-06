#include "BinaryOperator.h"
#include "Util.h"

#include <exception>



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
        throw std::logic_error("Division by zero error");

    return m_left->evaluate() / divisor;
}

PRIORITY Divide::priority() {
    return PRIO_MULTI;
}

ExpressionTree *Divide::clone() {
    return new Divide;
}


// Pow
double Pow::evaluate() {
    return std::pow(m_left->evaluate(), m_right->evaluate());
}

PRIORITY Pow::priority() {
    return PRIO_POW;
}

ExpressionTree *Pow::clone() {
    return new Pow;
}


// Modulo
double Modulo::evaluate() {
    if (0 == m_integerRight)
        throw std::logic_error("Division By Zero");

    return m_integerLeft % m_integerRight;
}

PRIORITY Modulo::priority() {
    return PRIO_MULTI;
}

ExpressionTree *Modulo::clone() {
    return new Modulo;
}


// BitAnd
double BitAnd::evaluate() {
    return m_integerLeft & m_integerRight;
}

PRIORITY BitAnd::priority() {
    return PRIO_BIT_AND;
}

ExpressionTree *BitAnd::clone() {
    return new BitAnd;
}


// BitOr
double BitOr::evaluate() {
    return m_integerLeft | m_integerRight;
}

PRIORITY BitOr::priority() {
    return PRIO_BIT_OR;
}

ExpressionTree *BitOr::clone() {
    return new BitOr;
}


// BitXor
double BitXor::evaluate() {
    return m_integerLeft ^ m_integerRight;
}

PRIORITY BitXor::priority() {
    return PRIO_BIT_XOR;
}

ExpressionTree *BitXor::clone() {
    return new BitXor;
}
