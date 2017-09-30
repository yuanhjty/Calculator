#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include "ExpressionTree.h"
#include "UnaryOperator.h"
#include "BinaryOperator.h"
#include "Function.h"
#include "Util.h"

#include <memory>
#include <string>
#include <stack>


// The class Parser
class Parser {
private:
    // Data members

    // m_expressoin:
    //   Setted in concrete Calculator
    //   Updated in this method parse
    //   Shared with concrete Calculator
    std::shared_ptr<Expression> m_expression;

    // m_scannedExpression:
    StringPtr m_scannedExpression;   //

    std::string m_postfixExpression;
    std::stack<ExpressionTree *> m_expressionTreeStack;
    ExpressionTree *m_expressionTree = nullptr;

public:
    ~Parser();
    void setExpression(const std::shared_ptr<Expression>& expression);
    void setScannedExpression(const StringPtr& scannedExpression);
    void parse();

private:
    ExpressionTree* generateExpressionTree();
    void setExpressionTree(ExpressionTree* expressionTree);
    void updateExpression();
};


// setExpression
inline void Parser::setExpression(const std::shared_ptr<Expression> &expression) {
    m_expression = expression;
}

// setInfixExpression
inline void Parser::setScannedExpression(const StringPtr& scannedExpression) {
    m_scannedExpression = scannedExpression;
}

inline void Parser::setExpressionTree(ExpressionTree *expressionTree) {
    m_expressionTree = expressionTree;
}

// updateExression
inline void Parser::updateExpression() {
    m_expression->setExpressionTree(m_expressionTree);
}


#endif // PARSER_H
