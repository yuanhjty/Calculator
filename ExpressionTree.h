#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H


#include <vector>


// The enum PRIORITY
enum PRIORITY {      // the same as operator priority of c++ language
    PRIO_COMMA,             // ,
    PRIO_THROW_EXCEPTION,   // throw
    PRIO_COMPOUND_ASSIGN,   // += -= ......
    PRIO_ASSIGN,            // =
    PRIO_CONDITION,         // ?:
    PRIO_LOGIC_OR,          // ||
    PRIO_LOGIC_AND,         // &&
    PRIO_BIT_OR,            // or
    PRIO_BIT_XOR,           // xor
    PRIO_BIT_AND,           // and
    PRIO_EQUAL,             // == !=
    PRIO_LESS,              // < > <= >=
    PRIO_SHIFT,             // >> <<
    PRIO_PLUS,              // + -
    PRIO_MULTI,             // * / %
    PRIO_POW,               // ^
    PRIO_MEM_PTR,           // ->* .*
    PRIO_PREFIX,            // ++ -- - ! ~ ......
    PRIO_POSTFIX,           // ++ -- typeid ......
    PRIO_CALL,              // . -> [] ()
    PRIO_SCOPE,             // ::
    PRIO_OPERAND
};

// The enum ASSOCIATIVITY
enum  ASSOCIATIVITY {
    ASSO_LEFT, ASSO_RIGHT
};

// The class Util
class Util {
public:
    static bool isDblToLLongValid(double dValue) {
        return ((long)dValue == dValue);
    }
};



// abstract base class
// The class ExpressionTree
class ExpressionTree {
public:
    virtual ~ExpressionTree() = default;
    virtual double evaluate() = 0;
    virtual PRIORITY priority() = 0;
    virtual ASSOCIATIVITY associativity() = 0;
    virtual ExpressionTree* clone() = 0;
    virtual int childCount() const = 0;
    virtual void build(const std::vector<ExpressionTree*>& param) = 0;
                 // TreeNodes in param are contrary to the order of their positions in expression
};



// For binary operation ////////////////////////////////////
// For real operation //////////////////////////////
// The class BinaryOperator
class BinaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_left = nullptr;
    ExpressionTree *m_right = nullptr;

public:
    ~BinaryOperator();
    int childCount() const override;
    void build(const std::vector<ExpressionTree *>& param) override;
};


// The class LeftAssoOperator
class LeftAssoOperator : public BinaryOperator {
public:
    ASSOCIATIVITY associativity() override;
};


// The class RightAssoOperator
class RightAssoOperator : public BinaryOperator {
public:
    ASSOCIATIVITY associativity() override;
};
// For real operation //////////////////////////////


// For integer only operation //////////////////////
// The class IntegerBinaryOperator
class IntegerBinaryOperator : public BinaryOperator {
protected:
    long long m_integerLeft = 0;
    long long m_integerRight = 0;

public:
    void build(const std::vector<ExpressionTree *> &param) override;

protected:
    void makeIntegerOperands();
};


// The class IntegerLeftAssoOperator
class IntegerLeftAssoOperator : public IntegerBinaryOperator {
public:
    ASSOCIATIVITY associativity() override;
};


// The class IntegerRightAssoOperator
class IntegerRightAssoOperator : public IntegerBinaryOperator {
public:
    ASSOCIATIVITY associativity() override;
};
// For integer only operation //////////////////////
// For binary operation ////////////////////////////////////



// For unary operation /////////////////////////////////////
// For real operation //////////////////////////////
// The class UnaryOperator
class UnaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_child = nullptr;

public:
    ~UnaryOperator();
    int childCount() const override;
    virtual void build(const std::vector<ExpressionTree*>& child);
};


// The class PrefixOperator
class PrefixOperator : public UnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};


// The class PostfixOperator
class PostfixOperator : public UnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};
// For real operation //////////////////////////////


// For integer only operation //////////////////////
// The class IntegerUnaryOperator
class IntegerUnaryOperator : public UnaryOperator {
protected:
    long long m_integerChild = 0;

public:
    void build(const std::vector<ExpressionTree*>& param) override;

protected:
    void makeIntegerOperand();
};


// The class IntegerPrefixOperator
class IntegerPrefixOperator : public IntegerUnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};


// The class IntegerPostfixOperator
class IntegerPostfixOperator : public IntegerUnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};
// For integer only operation //////////////////////
// For unary operation /////////////////////////////////////

#endif // EXPRESSIONTREE_H
