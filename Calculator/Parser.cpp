#include "Parser.h"
#include "ExpressionException.h"

#include <sstream>
#include <stack>


// constructor
Parser::~Parser()
{

}


// parse
std::shared_ptr<ExpressionTree> Parser::parse(const std::string &infixExpression) {
    setInfixExpression(infixExpression);
    buildPostfixExpression();
    buildExpressionTree();
    return m_expressionTree;
}

// generatePostfixExpression
void Parser::buildPostfixExpression() {
    m_postfixExpression.clear();
    m_isPrefix = true;

    std::stack<std::string> operatorStack;
    std::istringstream is(m_infixExpression);

    std::string token;
    std::string prevToken;

    ExpressionTree *exprNode = nullptr;
    ExpressionTree *prevOperator = nullptr;

    while (is >> token) {
        if ("-" == token && true == m_isPrefix)
            token = "u-";

//        if (!validPrevToken(token, prevToken))
//            throw std::logic_error("error: invalid expression: " + prevToken + " " + token);

        checkValidity(token, prevToken);

        if (isOperator(token) || isVariable(token)) {
            exprNode = m_symbolTable->getExpressionNode(token);

            while (!operatorStack.empty() && (operatorStack.top() != "(")) {
                prevOperator = m_symbolTable->getExpressionNode(operatorStack.top());

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
                exprNode = m_symbolTable->getExpressionNode(operatorStack.top());
                m_postfixExpression.push_back(exprNode->clone());
                operatorStack.pop();
            }
            if (operatorStack.empty())
                throw ParenthesesError("parentheses matching failed: '(' missing");
            operatorStack.pop();
        }
        else {    // if (isOperand(token) && !isVariable(token))
            try {
                double value = std::stod(token);
                exprNode = new Number(value);
                m_postfixExpression.push_back(exprNode);
            } catch (std::invalid_argument) {
                throw SymbolError("undefined symbol: " + token);
            } catch (std::out_of_range) {
                throw std::logic_error("floating point number overflow");
            }
        }
        prevToken = token;
    }
    // Check if the last token is valid.
    if (isPrefixOperator(token) || isBinaryOperator(token)
            || "(" == token)
        throw NotCompleteError("invalid expression: " + token);

    while (!operatorStack.empty()) {
        exprNode = m_symbolTable->getExpressionNode(operatorStack.top());
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
                throw OperandError("operand missing");
            param.push_back(exprTreeStack.top());
            exprTreeStack.pop();
        }
        node->build(param);
        exprTreeStack.push(node);
    }

    if (exprTreeStack.size() != 1)
        throw OperatorError("operator missing");

    m_expressionTree.reset(exprTreeStack.top());
    exprTreeStack.pop();
}

// validPrevToken
//bool Parser::validPrevToken(const std::string &token,
//                            const std::string &prevToken) const {
//    if (isBinaryOperator(token)){
//        m_isPrefix = true;
//        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
//                || "(" == prevToken || prevToken.empty())
//            return false;
//    }
//    else if (isPrefixOperator(token)) {
//        m_isPrefix = true;
//        if (isPostfixOperator(prevToken) || isOperand(prevToken)
//                || ")" == prevToken)
//            return false;
//    }
//    else if (isPostfixOperator(token)) {
//        m_isPrefix = false;
//        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
//                || "(" == prevToken || prevToken.empty())
//            return false;
//    }
//    else if ("(" == token) {
//        m_isPrefix = true;
//        if (isPostfixOperator(prevToken) || isOperand(prevToken)
//                || ")" == prevToken)
//            return false;
//    }
//    else if (")" == token) {
//        m_isPrefix = false;
//        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
//                || "(" == prevToken || prevToken.empty())
//            return false;
//    }
//    else { // if (isOperand(token)
//        m_isPrefix = false;
//        if (isPostfixOperator(prevToken) || isOperand(prevToken) || ")" == prevToken)
//            return false;
//    }
//    return true;
//}

// checkValidity
void Parser::checkValidity(const std::string &token,
                            const std::string &prevToken) const {
    if (isBinaryOperator(token)) {
        m_isPrefix = true;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            throw OperatorError("invalid operator: " + token);
    }
    else if (isPrefixOperator(token)) {
        m_isPrefix = true;
        if (isPostfixOperator(prevToken) || isOperand(prevToken)
                || ")" == prevToken)
            throw OperatorError("invalid operator: " + token);
    }
    else if (isPostfixOperator(token)) {
        m_isPrefix = false;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            throw OperatorError("invalid operator: " + token);
    }
    else if ("(" == token) {
        m_isPrefix = true;
        if (isPostfixOperator(prevToken) || isOperand(prevToken)
                || ")" == prevToken)
            throw ParenthesesError("invalid parentheses: " + token);
    }
    else if (")" == token) {
        m_isPrefix = false;
        if (isPrefixOperator(prevToken) || isBinaryOperator(prevToken)
                || "(" == prevToken || prevToken.empty())
            throw ParenthesesError("invalid parentheses: " + token);
    }
    else { // if (isOperand(token)
        m_isPrefix = false;
        if (isPostfixOperator(prevToken) || isOperand(prevToken) || ")" == prevToken)
            throw OperandError("invalid operand: " + token);
    }
}
