#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"

#include <memory>
#include <string>


//
// Define class Parser
//
class Parser {
private:
    std::shared_ptr<Expression> m_expression;

public:
    void setExpression(const std::shared_ptr<Expression>& expression);
    void parse(const std::shared_ptr<std::string>& infixExpression);
};


//
// Implement methods
//
// setExpressionTree
inline void Parser::setExpression(const std::shared_ptr<Expression> &expression) {
    m_expression = expression;
}


#endif // PARSER_H
