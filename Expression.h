#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <string>


// The class ExpressionTree
class ExpressionTree {
public:
    virtual ~ExpressionTree() = default;
    virtual double evaluate() = 0;
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
