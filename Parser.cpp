#include "Parser.h"

Parser::Parser()
{

}

void Parser::init()
{

}

std::shared_ptr<Expression> Parser::parse(const std::string &infixExpression)
{
    std::shared_ptr<Expression> expression(new Expression);
    return expression;
}
