#include "ExprNode.h"


const ExprAttrs OperandAsPrecursor::_validPrecursorTypes =
        ExprAttrs(TYPE_OPERAND) | TYPE_POSTFIX_OPERATOR | TYPE_RIGHT_BRACKET;

const ExprAttrs OperatorAsPrecursor::_validPrecursorTypes =
        ExprAttrs(TYPE_BINARY_OPERATOR) | TYPE_PREFIX_OPERATOR | TYPE_LEFT_BRACKET | TYPE_DUMMY_NODE;

BinaryOperator::~BinaryOperator() {
    if (_leftChild) {
        delete _leftChild;
        _leftChild = nullptr;
    }

    if (_rightChild) {
        delete _rightChild;
        _rightChild = nullptr;
    }
}

UnaryOperator::~UnaryOperator() {
    if (_child) {
        delete _child;
        _child = nullptr;
    }
}
