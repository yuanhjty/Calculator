#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <string>
#include <memory>


//
// Define class ExpressionTree
//
class ExpressionTree {
public:
    typedef double ValueType;

public:
    virtual ~ExpressionTree() = default;
    virtual ValueType value() = 0;
    virtual void evaluate() = 0;
};


class Expression {
private:
    std::shared_ptr<ExpressionTree> m_expressionTree;
public:
    ExpressionTree::ValueType value() {
        return m_expressionTree->value();
    }

    void evaluate() {
        m_expressionTree->evaluate();
    }
};


#endif // EXPRESSION_TREE_H
