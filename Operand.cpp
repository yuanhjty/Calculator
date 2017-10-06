#include "Operand.h"


void Number::build(double value) {
    m_value = value;
}

double Number::evaluate() {
    return m_value;
}

PRIORITY Number::priority() {
    return PRIO_OPERAND;
}

ASSOCIATIVITY Number::associativity() {
    return ASSO_LEFT;
}

ExpressionTree* Number::clone() {
    return new Number;
}
