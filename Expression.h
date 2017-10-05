#ifndef EXPRESSION_H
#define EXPRESSION_H


#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "Function.h"

#include <string>
#include <initializer_list>
#include <set>
#include <map>
#include <utility>


// The enum PRIORITY
enum PRIORITY {      // the same as operator priority of c++ language
    P_COMMA,                  // ,
    p_THROW_EXCEPTION,        // throw
    P_COMPOUND_ASSIGN,        // += -= ......
    P_ASSIGN,                 // =
    P_CONDITION,              // ?:
    P_LOGIC_OR,               // ||
    P_LOGIC_AND,              // &&
    P_BIT_OR,                 // |
    P_BIT_XOR,                // ^
    P_BIT_AND,                // &
    P_EQUAL,                  // == !=
    P_LESS,                   // < > <= >=
    P_SHIFT,                  // >> <<
    P_PLUS,                   // + -
    P_MULTI,                  // * / %
    P_MEM_PTR,                // ->* .*
    P_PREFIX,                 // ++ -- - ! ~ ......
    P_POSTFIX,                // ++ -- typeid ......
    P_CALL,                   // . -> [] ()
    P_SCOPE,                  // ::
    P_OPERAND
};


// The enum ASSOCIATIVITY
enum  ASSOCIATIVITY {
    A_LEFT, A_RIGHT
};


//

// The class ExpressionTree
class ExpressionTree {
public:
    virtual ~ExpressionTree() = default;
    virtual double evaluate() = 0;
};


extern const std::map<std::string, ExpressionTree*> prefixOperators;
extern const std::map<std::string, ExpressionTree*> postfixOperators;
extern const std::map<std::string, ExpressionTree*> binaryOperators;

extern const std::map<std::string, ExpressionTree*> operators;

void registerOperator(const std::string &name, ExpressoinTree *object) {
    operators.insert(std::make_pair(name, object));
}

void initOperators() {
    registerOperator("+", new Plus);
    registerOperator("-", new BMinus);
    registerOperator("*", new Multi);
    registerOperator("/", new Divide);
    registerOperator("|", new BitOr);
    registerOperator("&", new BitAnd);
    registerOperator("^", new BitXor);
    registerOperator("~", new BitNot);
    registerOperator("u-", new UMinus);

    registerOperator("sin", new Sin);
    registerOperator("cos", new Cos);
    registerOperator("tan", new Tan);
    registerOperator("pow", new Pow);
}

inline bool isIn(const std::set<std::string> &operators,
                 const std::string &token) {
    return operators.find(token) != operators.cend();
}

inline bool isPrefixOperator(const std::string &token) {
    return isIn(prefixOperators, token);
}

inline bool isPostfixOperator(const std::string &token) {
    return isIn(postfixOperators, token);
}

inline bool isBinaryOperator(const std::string &token) {
    return isIn(binaryOperators, token);
}

inline bool isFunction(const std::string &token) {
    return isIn(functions, token);
}

inline bool isOperator(const std::string &token) {
    return isPrefixOperator(token)
            || isPostfixOperator(token)
            || isFunction(token);
}

inline bool isOperand(const std::string &token) {
    return !isOperator(token);
}



// The class Operator
class Operator : public ExpressionTree {
protected:
    std::initializer_list<ExpressionTree *> m_childs;
public:
    Operator(const std::initializer_list<ExpressionTree *> &childs) :
        m_childs(childs) {}

    virtual int getChildCount() const = 0;
    virtual PRIORITY getPriority() const = 0;
    virtual ASSOCIATIVITY getAssociativity() const = 0;
};


// The class Expression
class Expression {
private:
    ExpressionTree *m_expressionTree = nullptr;

public:
    ~Expression();
    void setExpressionTree(ExpressionTree* expressionTree);
    double evaluate();
};


inline Expression::~Expression() {
    if (m_expressionTree) delete m_expressionTree;
}

inline void Expression::setExpressionTree(ExpressionTree *expressionTree) {
    m_expressionTree = expressionTree;
}

inline double Expression::evaluate() {
    return m_expressionTree->evaluate();
}


#endif // EXPRESSION_H

