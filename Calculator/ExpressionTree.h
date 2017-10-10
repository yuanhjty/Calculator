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
        return ((double)((long long)dValue) == dValue);
    }

    static bool isLLongToDblValid(long long llValue) {
        return ((long long)((double)llValue)) == llValue;
    }

    static long long toInteger(double value);
    static double toFloat(long long value);
};



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


#endif // EXPRESSIONTREE_H
