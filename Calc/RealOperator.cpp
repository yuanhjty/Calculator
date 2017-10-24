#include "RealOperator.h"
#include "CalcError.h"
#include "NumeralFormat.h"

#include <cmath>


// Plus
ExprNode::ValueType Plus::evaluate() {
    return _leftChild->evaluate() + _rightChild->evaluate();
}

ExprNode *Plus::newNode() const {
    return new Plus;
}


// BMinus
ExprNode::ValueType BMinus::evaluate() {
    return _leftChild->evaluate() - _rightChild->evaluate();
}

ExprNode *BMinus::newNode() const {
    return new BMinus;
}


// Mult
ExprNode::ValueType Mult::evaluate() {
    return _leftChild->evaluate() * _rightChild->evaluate();
}

ExprNode *Mult::newNode() const {
    return new Mult;
}


// Divide
ExprNode::ValueType Divide::evaluate() {
    ExprNode::ValueType divisor = _rightChild->evaluate();
    if (0 == divisor)
        throw SyntaxError("diveded by zero", REPAIR_IGNORE);

    return _leftChild->evaluate() / divisor;
}

ExprNode *Divide::newNode() const {
    return new Divide;
}


// Modulo
ExprNode::ValueType Modulo::evaluate() {
    ExprNode::ValueType divisor = _rightChild->evaluate();
    if (0 == divisor)
        throw SyntaxError("diveded by zero", REPAIR_IGNORE);

    ExprNode::ValueType dividend = _leftChild->evaluate();
    ExprNode::ValueType intPart = 0;
    std::modf(dividend / divisor, &intPart);

    return dividend - intPart * divisor;
}

ExprNode *Modulo::newNode() const {
    return new Modulo;
}


// Power
ExprNode::ValueType Power::evaluate() {
    return std::pow(_leftChild->evaluate(), _rightChild->evaluate());
}

ExprNode *Power::newNode() const {
    return new Power;
}


// Fact
// Not implemented yet.
ExprNode::ValueType Fact::evaluate() {
    return 0;
}

ExprNode *Fact::newNode() const {
    return new Fact;
}


// UMinus
ExprNode::ValueType UMinus::evaluate() {
    return -_child->evaluate();
}

ExprNode *UMinus::newNode() const {
    return new UMinus;
}


// Sin 
ExprNode::ValueType Sin::evaluate() {
    return std::sin(NumeralConverter::toRad(_child->evaluate()));
}

ExprNode *Sin::newNode() const {
    return new Sin;
}


// Cos 
ExprNode::ValueType Cos::evaluate() {
    return std::cos(NumeralConverter::toRad(_child->evaluate()));
}

ExprNode *Cos::newNode() const {
    return new Cos;
}


// Tan
ExprNode::ValueType Tan::evaluate() {
    return std::tan(NumeralConverter::toRad(_child->evaluate()));
}

ExprNode *Tan::newNode() const {
    return new Tan;
}


// Asin
ExprNode::ValueType Asin::evaluate() {
    return NumeralConverter::toDeg(std::asin(_child->evaluate()));
}

ExprNode *Asin::newNode() const {
    return new Asin;
}


// Acos
ExprNode::ValueType Acos::evaluate() {
    return NumeralConverter::toDeg(std::acos(_child->evaluate()));
}

ExprNode *Acos::newNode() const {
    return new Acos;
}


// Atan
ExprNode::ValueType Atan::evaluate() {
    return NumeralConverter::toDeg(std::atan(_child->evaluate()));
}

ExprNode *Atan::newNode() const {
    return new Atan;
}


// Lg
ExprNode::ValueType Lg::evaluate() {
    return std::log10(_child->evaluate());
}

ExprNode *Lg::newNode() const {
    return new Lg;
}


// Ln 
ExprNode::ValueType Ln::evaluate() {
    return std::log(_child->evaluate());
}

ExprNode *Ln::newNode() const {
    return new Ln;
}


// Sqrt
ExprNode::ValueType Sqrt::evaluate() {
    return std::sqrt(_child->evaluate());
}

ExprNode *Sqrt::newNode() const {
    return new Sqrt;
}
