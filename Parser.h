#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include "OperatorTable.h"
#include "Operand.h"

#include <string>
#include <vector>


// The class Parser
class Parser {
private:
    OperatorTable *m_operatorTable;
    std::string m_infixExpression;
    std::vector<ExpressionTree *> m_postfixExpression;
    ExpressionTree *m_expressionTree = nullptr;

public:
    Parser();
    virtual ~Parser();

    ExpressionTree* getExpressionTree() const;
    void parse(const std::string &infixExpression);

protected:
    virtual void setInfixExpression(const std::string &infixExpression);
    void generatePostfixExpression();
    void generateExpressionTree();
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
