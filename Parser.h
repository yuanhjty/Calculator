#ifndef PARSER_H
#define PARSER_H


#include "Expression.h"
#include "OperatorTable.h"
#include "Operand.h"

#include <memory>
#include <string>
#include <vector>


// The class Parser
class Parser {
private:
    OperatorTable *m_operatorTable = nullptr;
    std::string m_infixExpression;
    std::vector<ExpressionTree*> m_postfixExpression;
    std::shared_ptr<ExpressionTree> m_expressionTree;

public:
    Parser();
    virtual ~Parser();

    std::shared_ptr<ExpressionTree> getExpressionTree() const;
    void parse(const std::string &infixExpression);

protected:
    virtual void setInfixExpression(const std::string &infixExpression);
    void buildPostfixExpression();
    void buildExpressionTree();

private:
    mutable bool isPrefix = true;
    bool validPrevToken(const std::string& token, const std::string& prevToken) const;
    bool isPrefixOperator(const std::string& token) const;
    bool isPostfixOperator(const std::string& token) const;
    bool isBinaryOperator(const std::string& token) const;
    bool isOperator(const std::string& token) const;
    bool isOperand(const std::string& token) const;
};



// setInfixExpression
inline void Parser::setInfixExpression(const std::string &infixExpression) {
    m_infixExpression = infixExpression;
}

inline bool Parser::isPrefixOperator(const std::string &token) const {
    return m_operatorTable->isPrefixOperator(token);
}

inline bool Parser::isPostfixOperator(const std::string &token) const {
    return m_operatorTable->isPostfixOperator(token);
}

inline bool Parser::isBinaryOperator(const std::string &token) const {
    return m_operatorTable->isBinaryOperator(token);
}

inline bool Parser::isOperator(const std::string &token) const {
    return isPrefixOperator(token) || isPostfixOperator(token) || isBinaryOperator(token);
}

inline bool Parser::isOperand(const std::string &token) const {
    return !(token.empty() || isOperator(token) || "(" == token || ")" == token);
}

// getExpressionTree
inline std::shared_ptr<ExpressionTree> Parser::getExpressionTree() const {
    return m_expressionTree;
}


#endif // PARSER_H
