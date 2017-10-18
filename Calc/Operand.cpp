#include "Operand.h"


// Number
ExprNode::ValueType Number::evaluate() {
    return _value;
}

ExprNode *Number::newNode() const {
    return new Number(_value);
}


// ConstPi
ExprNode::ValueType ConstPi::evaluate() {
    return 3.141592653589793;
}

ExprNode *ConstPi::newNode() const {
    return new ConstPi;
}


// ConstE
ExprNode::ValueType ConstE::evaluate() {
    return 2.718281828459045;
}

ExprNode *ConstE::newNode() const {
    return new ConstE;
}
