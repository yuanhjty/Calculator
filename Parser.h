#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"

#include <memory>
#include <string>


class Parser
{
protected:
    std::shared_ptr<ExpressionTree> m_expressionTree;

public:
    virtual ~Parser() = default;
    virtual void init();
    virtual void parse(const std::shared_ptr<std::string>& infixExpression);

    std::shared_ptr<ExpressionTree> getExpressionTree() const;

private:
    void setExpressionTree(const std::shared_ptr<ExpressionTree>& expressionTree);

};

inline std::shared_ptr<ExpressionTree> Parser::getExpressionTree() const {
    return m_expressionTree;
}

inline void Parser::setExpressionTree(const std::shared_ptr<ExpressionTree> &expressionTree) {
    m_expressionTree = expressionTree;
}


#endif // PARSER_H
