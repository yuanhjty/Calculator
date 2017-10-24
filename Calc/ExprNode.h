#ifndef EXPR_NODE_H
#define EXPR_NODE_H

#include "CalcFlags.h"

#include <vector>
#include <cassert>


// The enum ExprAttr
enum ExprAttr {
    ATTR_EMPTY = 0x0,

    // 1~2 bits of an int type number for associativity.
    ASSO_FIELD  = 0x3,

    ASSO_LEFT  = 0x1,
    ASSO_RIGHT = 0x2,


    // 3~20 bits of an int type number for priority
    PRIO_FIELD            = 0xffffc,

    PRIO_COMMA           = 0x00004,       // ,
    PRIO_COMPOUND_ASSIGN = 0x00008,       // += -= ......

    PRIO_ASSIGN          = 0x00010,       // =
    PRIO_LOGIC_OR        = 0x00020,       // ||
    PRIO_LOGIC_AND       = 0x00040,       // &&
    PRIO_BIT_OR          = 0x00080,       // or

    PRIO_BIT_XOR         = 0x00100,       // xor
    PRIO_BIT_AND         = 0x00200,       // and
    PRIO_EQUAL           = 0x00400,       // == !=
    PRIO_LESS            = 0x00800,       // < > <= >=

    PRIO_BIT_SHIFT       = 0x01000,       // >> <<
    PRIO_PLUS            = 0x02000,       // + -
    PRIO_MULTI           = 0x04000,       // * / %
    PRIO_POW             = 0x08000,       // ^

    PRIO_PREFIX          = 0x10000,       // ++ -- - !(not) ~
    PRIO_POSTFIX         = 0x20000,       // ++ -- !(factorial)
    PRIO_FUNCTION_CALL   = 0x40000,       // ()
    PRIO_OPERAND         = 0x80000,        // operand's priority is highest


    // 21~32 bits of an int type number for node type.
    TYPE_FIELD             = 0xfff00000,

    TYPE_PREFIX_OPERATOR  = 0x00100000,
    TYPE_BINARY_OPERATOR  = 0x00200000,
    TYPE_POSTFIX_OPERATOR = 0x00400000,
    TYPE_OPERAND          = 0x00800000,

    TYPE_LEFT_BRACKET     = 0x01000000,
    TYPE_RIGHT_BRACKET    = 0x02000000,
    TYPE_DUMMY_NODE       = 0x04000000,
};


typedef CalcFlags<ExprAttr> ExprAttrs;

// The class ExprNode
class ExprNode {
public:
    typedef double ValueType;

public:
    ExprNode() = default;
    virtual ~ExprNode() = default;
    virtual ValueType evaluate() = 0;
    virtual bool isPrecursorValid(ExprAttr precursorType) const = 0;
    virtual int numberOfChildren() const = 0;
    virtual void setChildren(const std::vector<ExprNode *>& children) = 0;
    virtual ExprNode *newNode() const = 0;

    ExprAttr associativity() const {return (ExprAttr)(_attrs & ASSO_FIELD);}
    ExprAttr priority() const {return (ExprAttr)(_attrs & PRIO_FIELD);}
    ExprAttr nodeType() const {return (ExprAttr)(_attrs & TYPE_FIELD);}

protected:
    ExprAttrs _attrs = 0;
};


// The class OperandAsPrecursor
class OperandAsPrecursor {
protected:
    const static ExprAttrs _validPrecursorTypes;
};


// The class OperatorAsPrecursor
class OperatorAsPrecursor {
protected:
    const static ExprAttrs _validPrecursorTypes;
};



// The class BinaryOperator
class BinaryOperator : public ExprNode, public OperandAsPrecursor {
public:
    BinaryOperator();
    ~BinaryOperator();

    bool isPrecursorValid(ExprAttr precursorType) const override;
    int numberOfChildren() const override;
    void setChildren(const std::vector<ExprNode *>& children) override;

protected:
    ExprNode *_leftChild = nullptr;
    ExprNode *_rightChild = nullptr;

private:
    const static int _numberOfChildren = 2;
};

inline bool BinaryOperator::isPrecursorValid(ExprAttr precursorType) const {
    return ATTR_EMPTY != (ExprAttr)(_validPrecursorTypes & precursorType);
}

inline int BinaryOperator::numberOfChildren() const {
    return _numberOfChildren;
}

// Children's sequence in the argument children should be reversed.
inline void BinaryOperator::setChildren(const std::vector<ExprNode *> &children) {
    assert(_numberOfChildren == children.size());
    _leftChild = children[1];
    _rightChild = children[0];
}

inline BinaryOperator::BinaryOperator() {
    _attrs |= TYPE_BINARY_OPERATOR;
}


// The class LeftAssoBinaryOperator
class LeftAssoBinaryOperator : public BinaryOperator {
public:
    LeftAssoBinaryOperator();
};

inline LeftAssoBinaryOperator::LeftAssoBinaryOperator() {
    _attrs |= ASSO_LEFT;
}


// The class RightAssoBinaryOperator
class RightAssoBinaryOperator : public BinaryOperator {
public:
    RightAssoBinaryOperator();
};

inline RightAssoBinaryOperator::RightAssoBinaryOperator() {
    _attrs |= ASSO_RIGHT;
}



// The class UnaryOperator
class UnaryOperator : public ExprNode {
public:
    ~UnaryOperator();

    int numberOfChildren() const override;
    void setChildren(const std::vector<ExprNode *>& children);

protected:
    ExprNode *_child = nullptr;

private:
    const static int _numberOfChildren = 1;
};

inline int UnaryOperator::numberOfChildren() const {
    return _numberOfChildren;
}

inline void UnaryOperator::setChildren(const std::vector<ExprNode *> &children) {
    assert(_numberOfChildren == children.size());
    _child = children[0];
}


// The class PrefixOperator
class PrefixOperator : public UnaryOperator,  public OperatorAsPrecursor {
public:
    PrefixOperator();
    bool isPrecursorValid(ExprAttr precursorType) const override;
};

inline PrefixOperator::PrefixOperator() {
    ((_attrs |= ASSO_RIGHT) |= PRIO_PREFIX) |= TYPE_PREFIX_OPERATOR;
}

inline bool PrefixOperator::isPrecursorValid(ExprAttr precursorType) const {
    return ATTR_EMPTY != (ExprAttr)(_validPrecursorTypes & precursorType);
}


// The class PostfixOperator
class PostfixOperator : public UnaryOperator, public OperandAsPrecursor {
public:
    PostfixOperator();
    bool isPrecursorValid(ExprAttr precursorType) const override;
};

inline PostfixOperator::PostfixOperator() {
    ((_attrs |= ASSO_LEFT) |= PRIO_POSTFIX) |= TYPE_POSTFIX_OPERATOR;
}

inline bool PostfixOperator::isPrecursorValid(ExprAttr precursorType) const {
    return ATTR_EMPTY != (ExprAttr)(_validPrecursorTypes & precursorType);
}



// The class Operand
class Operand : public ExprNode,  public OperatorAsPrecursor {
public:
    Operand();
    bool isPrecursorValid(ExprAttr precursorType) const override;
    int numberOfChildren() const override;
    void setChildren(const std::vector<ExprNode *>& children) override;

private:
    const static int _numberOfChildren = 0;
};

inline Operand::Operand() {
    _attrs |= TYPE_OPERAND;
}

inline bool Operand::isPrecursorValid(ExprAttr precursorType) const {
    return ATTR_EMPTY != (ExprAttr)(_validPrecursorTypes & precursorType);
}

inline int Operand::numberOfChildren() const {
    return _numberOfChildren;
}

inline void Operand::setChildren(const std::vector<ExprNode *> &children) {
    assert(_numberOfChildren == children.size());
}

#endif // EXPR_NODE_H
