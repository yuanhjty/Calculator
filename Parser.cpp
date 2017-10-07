#include "Parser.h"

#include <sstream>
#include <stack>
#include <stdexcept>


// constructor
Parser::Parser() {
    m_operatorTable = OperatorTable::getInstance();
}

// parse
void Parser::parse(const std::string &infixExpression) {
    setInfixExpression(infixExpression);
    buildPostfixExpression();
    buildExpressionTree();
}

// generatePostfixExpression
void Parser::buildPostfixExpression() {
    m_postfixExpression.clear();

    std::stack<std::string> operatorStack;
    std::istringstream is(m_infixExpression);

    std::string token;
    std::string prevToken;

    ExpressionTree *exprNode = nullptr;
    ExpressionTree *prevOperator = nullptr;

    while (is >> token) {
        if ("-" == token && true == isPrefix)
            token = "u-";

        if (!validPrevToken(token, prevToken))
            throw std::logic_error("error: invalid expression: " + prevToken + " " + token);

        if (isOperator(token)) {
            exprNode = m_operatorTable->getOperator(token);

            while (!operatorStack.empty() && (operatorStack.top() != "(")) {
                prevOperator = m_operatorTable->getOperator(operatorStack.top());

                if (exprNode->priority() < prevOperator->priority()
                        || (exprNode->priority() == prevOperator->priority()
                            && exprNode->associativity() == ASSO_LEFT)) {
                    m_postfixExpression.push_back(prevOperator->clone());
                    operatorStack.pop();
                } else
                    break;
            }

            operatorStack.push(token);
        }
        else if ("(" == token){
            operatorStack.push(token);
        }
        else if (")" == token) {
            while (!operatorStack.empty() && (operatorStack.top() != "(")) {
                exprNode = m_operatorTable->getOperator(operatorStack.top());
                m_postfixExpression.push_back(exprNode->clone());
                operatorStack.pop();
            }
            if (operatorStack.empty())
                throw std::logic_error("error: parentheses matching failed: lack of '('.");
            operatorStack.pop();
        }
        else {    // if (isOperand(token))
            try {
                double value = std::stod(token);
                exprNode = new Number(value);
                m_postfixExpression.push_back(exprNode);
            } catch (std::invalid_argument) {
                throw std::logic_error("error: undefined symbol: " + token);
            } catch (std::out_of_range) {
                throw std::logic_error("error: floating point number overflow");
            }
        }
        prevToken = token;
    }
    // Check if the last token is valid.
    if (isPrefixOperator(token) || isBinaryOperator(token)
            || "(" == token)
        throw std::logic_error("error: invalid expression: " + token);

    while (!operatorStack.empty()) {
        exprNode = m_operatorTable->getOperator(operatorStack.top());
        m_postfixExpression.push_back(exprNode->clone());
        operatorStack.pop();
    }
}


// generateExpressoinTree
void Parser::buildExpressionTree() {
    std::stack<ExpressionTree*> exprTreeStack;

    int childCount = 0;
    std::vector<ExpressionTree*> param;

    for (ExpressionTree* node : m_postfixExpression) {
        childCount = node->childCount();
        param.clear();

        while (childCount--) {
            if (exprTreeStack.empty())
                throw std::logic_error("error: invalid expression: lack of operand");
            param.push_back(exprTreeStack.top());
            exprTreeStack.pop();
        }
        node->build(param);
        exprTreeStack.push(node);
    }

    if (exprTreeStack.size() != 1)
        throw std::logic_error("error: invalid expression: lack of operand");

    m_expressionTree.reset(exprTreeStack.top());
    exprTreeStack.pop();
}

// validPrevToken
bool Parser::validPrevToken(const std::string &token,
                            const std::string &prevToken) const {
    if (isBinaryOperator(token)){
        isPrefix = true;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            return false;
    }
    else if (isPrefixOperator(token)) {
        isPrefix = true;
        if (isPostfixOperator(prevToken) || isOperand(prevToken)
                || ")" == prevToken)
            return false;
    }
    else if (isPostfixOperator(token)) {
        isPrefix = false;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            return false;
    }
    else if ("(" == token) {
        isPrefix = true;
        if (isPostfixOperator(prevToken) || isOperand(prevToken)
                || ")" == prevToken)
            return false;
    }
    else if (")" == token) {
        isPrefix = false;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            return false;
    }
    else { // if (isOperand(token)
        isPrefix = false;
        if (isPostfixOperator(prevToken) || isOperand(prevToken) || ")" == prevToken)
            return false;
    }
    return true;
}
