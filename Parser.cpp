#include "Parser.h"

#include <sstream>
#include <stack>


// destructor
Parser::~Parser() {
    if (m_expressionTree) delete m_expressionTree;
}

// parse
void Parser::parse(const std::string &infixExpression) {
    setInfixExpression(infixExpression);
    generatePostfixExpression();
    generateExpressionTree();
}

// generatePostfixExpression
void Parser::generatePostfixExpression() {
    std::stack<ExpressionTree *> operatorStack;
    std::istringstream is(m_infixExpression);
    std::string token;
    std::string prevToken = "(";
    std::map<std::string, ExpressionTree *>::const_iterator opIt;
    ExpressionTree *currentTree = nullptr;
    bool isPrefix = true;

    while (is >> token) {
        if ((opIt = operators.find(token)) == operators.cend()) {
            if
            currentTree = new Number(std::stod(token));
        } else {

        }

//        if ((it = prefixOperators.find(token)) != prefixOperators.cend()) {

//        } else if ((it = postfixOperators.find(token))!= postfixOperators.cend()) {

//        } else if ((it = binaryOperators.find(token)) != binaryOperators.cend()) {

//        } else if ((it = functions.find(token)) != functions.cend()) {

//        } else if ("(" == token) {

//        } else if (")" == token) {

//        } else {

//        }
        prevToken = token;
    }
}

// generateExpressoinTree
void Parser::generateExpressionTree() {

}
