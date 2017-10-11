#include "UnaryOperator.h"
#include "ExpressionException.h"

#include <cmath>


// UnaryOperator
UnaryOperator::~UnaryOperator() {
    if (m_child) delete m_child;
}

int UnaryOperator::childCount() const {
    return 1;
}

void UnaryOperator::build(const std::vector<ExpressionTree*>& param) {
    if (param.size() != 1)
        throw InnerError("inner error: BinaryOperator::build() failed due to invalid argument");
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



// BitNot
double BitNot::evaluate() {
    return Util::toFloat(~Util::toInteger(m_child->evaluate()));
}

ExpressionTree *BitNot::clone() {
    return new BitNot;
}


// Fact
// Not implemented yet.
double Fact::evaluate() {
    return 0;
}

ExpressionTree *Fact::clone() {
    return new Fact;
}


// UMinus
double UMinus::evaluate() {
    return -m_child->evaluate();
}

ExpressionTree *UMinus::clone() {
    return new UMinus;
}


// Lg
double Lg::evaluate() {
    return std::log10(m_child->evaluate());
}

ExpressionTree *Lg::clone() {
    return new Lg;
}


// Ln
double Ln::evaluate() {
    return std::log(m_child->evaluate());
}

ExpressionTree *Ln::clone() {
    return new Ln;
}


// Sin
double Sin::evaluate() {
    return std::sin(m_child->evaluate());
}

ExpressionTree *Sin::clone() {
    return new Sin;
}


// Cos
double Cos::evaluate() {
    return std::cos(m_child->evaluate());
}

ExpressionTree *Cos::clone() {
    return new Cos;
}


// Tan
double Tan::evaluate() {
    return std::tan(m_child->evaluate());
}

ExpressionTree *Tan::clone() {
    return new Tan;
}


// ASin
double ASin::evaluate() {
    return std::asin(m_child->evaluate());
}

ExpressionTree *ASin::clone() {
    return new ASin;
}


// ACos
double ACos::evaluate() {
    return std::acos(m_child->evaluate());
}

ExpressionTree *ACos::clone() {
    return new ACos;
}


// ATan
double ATan::evaluate() {
    return std::atan(m_child->evaluate());
}

ExpressionTree *ATan::clone() {
    return new ATan;
}

double Sqrt::evaluate()
{
    return std::sqrt(m_child->evaluate());
}

ExpressionTree *Sqrt::clone() {
    return new Sqrt;
}

double Square::evaluate()
{
    return std::pow(m_child->evaluate(), 2);
}

ExpressionTree *Square::clone() {
    return new Square;
}
