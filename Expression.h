#ifndef EXPRESSION_H
#define EXPRESSION_H


#include "ExpressionTree.h"

#include <string>


class Expression {
private:
    ExpressionTree *m_expressionTree = nullptr;

public:
    ~Expression();
    void setExpressionTree(ExpressionTree* expressionTree);
    std::string evaluate();
};

inline void Expression::setExpressionTree(ExpressionTree *expressionTree) {
    m_expressionTree = expressionTree;
}


#endif // EXPRESSION_H
