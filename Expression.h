#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>


class ExpressionTree {
public:
    virtual ~ExpressionTree() = default;
//    virtual double value() = 0;
//    virtual void evaluate() = 0;
    virtual double value() {return 0.01001;}    // for framework test
    virtual void evaluate() {}  // for framework test
};


class Expression
{
protected:
    std::shared_ptr<ExpressionTree> m_expressionTree;

public:
    Expression(const std::shared_ptr<ExpressionTree>& expressionTree);

    void evaluate();
    std::shared_ptr<std::string> showValue();
};


inline Expression::Expression(const std::shared_ptr<ExpressionTree> &expressionTree) :
    m_expressionTree(expressionTree) {}

inline void Expression::evaluate() {
    m_expressionTree->evaluate();
}


#endif // EXPRESSION_H
