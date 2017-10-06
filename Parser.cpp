#include "Parser.h"

#include <sstream>
#include <stack>


// constructor
Parser::Parser() {
    m_operatorTable = OperatorTable::getInstance();
}

// destructor
Parser::~Parser() {
    if (m_expressionTree) delete m_expressionTree;
    if (m_operatorTable) delete m_operatorTable;
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
    std::string prevToken;

    std::map<std::string, ExpressionTree*>::const_iterator opIt;
    std::map<std::string, ExpressionTree*>::const_iterator prevOpIt;

    bool isPrefix = true;

    while (is >> token) {
        // Token is an unary operator.
//        if ((opIt = unaryOperators.find(token)) != UnaryOperator.cend()) {
//            UnaryOperator *op = opIt->second->clone();
//            if (")" == prevToken || ) {

//            }
//        }

//        // Token is a binary operator.
//        else if ((opIt = binaryOperators.find(token)) != binaryOperators.cend()) {

//        }

//        // Token is an operand.
//        else {

//        }

//        prevToken = token;
    }
}

// generateExpressoinTree
void Parser::generateExpressionTree() {

}
