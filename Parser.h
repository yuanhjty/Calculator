#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
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
    std::string m_infixExpression;
    std::string m_postfixExpression;
    ExpressionTree *m_expressionTree = nullptr;

public:
    virtual ~Parser();

    ExpressionTree* getExpressionTree() const;
    void parse(const std::string &infixExpression);

protected:
    virtual void setInfixExpression(const std::string &infixExpression);
};


// setInfixExpression
inline void Parser::setInfixExpression(const std::string &infixExpression) {
    m_infixExpression = infixExpression;
}

// getExpressionTree
inline ExpressionTree *Parser::getExpressionTree() const {
    return m_expressionTree;
}


#endif // PARSER_H
