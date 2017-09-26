#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"

#include <memory>
#include <string>


class Parser
{
public:
    Parser();

    void init();

    std::shared_ptr<Expression> parse(const std::string& infixExpression);
};

#endif // PARSER_H
