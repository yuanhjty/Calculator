#include "Operand.h"


void Number::build(double value) {
    m_value = value;
}

double Number::evaluate() {
    return m_value;
}

ExpressionTree* Number::clone() {
    return new Number;
}
