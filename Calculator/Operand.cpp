#include "Operand.h"
#include "ExpressionException.h"


// Operand
PRIORITY Operand::priority() {
    return PRIO_OPERAND;
}

ASSOCIATIVITY Operand::associativity() {
    return ASSO_LEFT;
}

int Operand::childCount() const {
    return 0;
}


// Number
Number::Number() {

}

Number::Number(double value) {
    m_value = value;
}

double Number::evaluate() {
    return m_value;
}

ExpressionTree* Number::clone() {
    return new Number(m_value);
}

void Number::build(const std::vector<ExpressionTree*>& param) {
    if (!param.empty())
        throw InnerError("inner error: Number build failed due to invalid argument");
}


// Constant
void Constant::build(const std::vector<ExpressionTree *> &param) {
   if(!param.empty())
        throw InnerError("inner error: Number build failed due to invalid argument");
}


// ConstPi
double ConstPi::evaluate() {
    return 3.141592653589;
}

ExpressionTree *ConstPi::clone() {
    return new ConstPi;
}


// ConstE
double ConstE::evaluate() {
    return 2.718281828459;
}

ExpressionTree *ConstE::clone() {
    return new ConstE;
}
