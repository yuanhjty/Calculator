#include "Parser.h"


void Parser::init() {

}

void Parser::parse(const std::shared_ptr<std::string>& infixExpression) {
//    std::shared_ptr<ExpressionTree> expressionTree;

    std::shared_ptr<ExpressionTree> expressionTree(new ExpressionTree); // for framework test

    setExpressionTree(expressionTree);
}

