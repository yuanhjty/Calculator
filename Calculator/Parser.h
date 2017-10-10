#ifndef PARSER_H
#define PARSER_H


#include "Expression.h"
#include "SymbolTable.h"
#include "Operand.h"

#include <memory>
#include <string>
#include <vector>


// The class Parser
class Parser {
private:
    std::string m_infixExpression;
    std::vector<ExpressionTree*> m_postfixExpression;
    mutable bool m_isPrefix = true;

    std::shared_ptr<SymbolTable> m_symbolTable;
    std::shared_ptr<ExpressionTree> m_expressionTree;

public:
    virtual ~Parser();

    void setSymbolTable(const std::shared_ptr<SymbolTable>& symbolTable);
    std::shared_ptr<ExpressionTree> parse(const std::string &infixExpression);

protected:
    virtual void setInfixExpression(const std::string &infixExpression);
    void buildPostfixExpression();
    void buildExpressionTree();

private:
//    bool validPrevToken(const std::string& token, const std::string& prevToken) const;
    void checkValidity(const std::string& token, const std::string& prevToken) const;

    bool isPrefixOperator(const std::string& token) const;
    bool isPostfixOperator(const std::string& token) const;
    bool isBinaryOperator(const std::string& token) const;
    bool isVariable(const std::string& token) const;

    bool isOperator(const std::string& token) const;
    bool isOperand(const std::string& token) const;
};



inline void Parser::setSymbolTable(const std::shared_ptr<SymbolTable> &symbolTable) {
    m_symbolTable = symbolTable;
}

// setInfixExpression
inline void Parser::setInfixExpression(const std::string &infixExpression) {
    m_infixExpression = infixExpression;
}


// is...
inline bool Parser::isPrefixOperator(const std::string &token) const {
    return m_symbolTable->hasPrefixOperator(token);
}

inline bool Parser::isPostfixOperator(const std::string &token) const {
    return m_symbolTable->hasPostfixOperator(token);
}

inline bool Parser::isBinaryOperator(const std::string &token) const {
    return m_symbolTable->hasBinaryOperator(token);
}

inline bool Parser::isVariable(const std::string &token) const {
    return m_symbolTable->hasVariable(token);
}

inline bool Parser::isOperator(const std::string &token) const {
    return isPrefixOperator(token) || isPostfixOperator(token) || isBinaryOperator(token);
}

inline bool Parser::isOperand(const std::string &token) const {
    return isVariable(token)
            || !(token.empty() || isOperator(token) || "(" == token || ")" == token);
}



#endif // PARSER_H
