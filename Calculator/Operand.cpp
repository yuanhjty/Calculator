#include "Operand.h"

#include <stdexcept>



Number::Number(double value) {
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
    return new Number(m_value);
}

int Number::childCount() const {
    return 0;
}

void Number::build(const std::vector<ExpressionTree*>& param) {
    if (!param.empty())
        throw std::runtime_error("inner error: build ExpressionTree failed");
}

