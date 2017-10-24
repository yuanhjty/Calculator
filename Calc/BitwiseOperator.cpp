#include "BitwiseOperator.h"
#include "NumeralFormat.h"


ExprNode::ValueType BitAnd::evaluate() {
    return NumeralConverter::toFloat(
                (NumeralConverter::toInteger(_leftChild->evaluate())
                 & NumeralConverter::toInteger(_rightChild->evaluate())));
}

ExprNode *BitAnd::newNode() const {
    return new BitAnd;
}


ExprNode::ValueType BitOr::evaluate() {
    return NumeralConverter::toFloat(
                (NumeralConverter::toInteger(_leftChild->evaluate())
                 | NumeralConverter::toInteger(_rightChild->evaluate())));
}

ExprNode *BitOr::newNode() const {
    return new BitOr;
}


ExprNode::ValueType BitXor::evaluate() {
    return NumeralConverter::toFloat(
                (NumeralConverter::toInteger(_leftChild->evaluate())
                 ^ NumeralConverter::toInteger(_rightChild->evaluate())));
}

ExprNode *BitXor::newNode() const {
    return new BitXor;
}


ExprNode::ValueType Lsh::evaluate() {
    return NumeralConverter::toFloat(
                (NumeralConverter::toInteger(_leftChild->evaluate())
                 << NumeralConverter::toInteger(_rightChild->evaluate())));
}

ExprNode *Lsh::newNode() const {
    return new Lsh;
}


ExprNode::ValueType Rsh::evaluate() {
    return NumeralConverter::toFloat(
                (NumeralConverter::toInteger(_leftChild->evaluate())
                 >> NumeralConverter::toInteger(_rightChild->evaluate())));
}

ExprNode *Rsh::newNode() const {
    return new Rsh;
}


ExprNode::ValueType BitNot::evaluate() {
    return NumeralConverter::toFloat(
                ~NumeralConverter::toInteger(_child->evaluate()));
}

ExprNode *BitNot::newNode() const {
    return new BitNot;
}
