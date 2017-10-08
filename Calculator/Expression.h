#ifndef EXPRESSION_H
#define EXPRESSION_H


#include "ExpressionTree.h"

#include <memory>


// The class Expression
class Expression {
private:
    std::shared_ptr<ExpressionTree> m_expressionTree = nullptr;

public:
    void setExpressionTree(const std::shared_ptr<ExpressionTree>& expressionTree);
    double evaluate();
};


inline void Expression::setExpressionTree(const std::shared_ptr<ExpressionTree>& expressionTree) {
    m_expressionTree = expressionTree;
}

inline double Expression::evaluate() {
    return m_expressionTree->evaluate();
}


#endif // EXPRESSION_H
