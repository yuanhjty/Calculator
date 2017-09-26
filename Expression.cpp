#include "Expression.h"



std::shared_ptr<std::string> Expression::showValue() {
    double value = m_expressionTree->value();
    std::shared_ptr<std::string> ret(
                new std::string(std::to_string(value)));
    return ret;
}

