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
    bool isPrefixOp = true;

    std::stack<std::string> operatorStack;
    std::istringstream is(m_infixExpression);

    std::string token;
    std::string prevToken;

    ExpressionTree *exprNode = nullptr;
    ExpressionTree *prevOperator = nullptr;

    while (is >> token) {
        if ("-" == token && true == isPrefixOp)
            token = "u-";

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
                throw LeftBracketMissing("barcket matching failed: '(' missing");
            operatorStack.pop();
        }
        else {    // if (isOperand(token) && !isVariable(token))
            try {
                double value = std::stod(token);
                exprNode = new Number(value);
                m_postfixExpression.push_back(exprNode);
            } catch (std::invalid_argument) {
                throw InvalidSymbol("undefined symbol: " + token);
            } catch (std::out_of_range) {
                throw std::overflow_error("floating point number overflow");
            }
        }

        isPrefixOp = (isBinaryOperator(token) || isPrefixOperator(token)
                      || "(" == token) ? true : false;
        prevToken = token;
    }

    while (!operatorStack.empty()) {
        const std::string& top = operatorStack.top();
        if ("(" == top)
            throw RightBracketMissing("bracket matching failed: ')' missing");

        exprNode = m_symbolTable->getExpressionNode(operatorStack.top());
        m_postfixExpression.push_back(exprNode->clone());
        operatorStack.pop();
    }
}


// generateExpressoinTree
void Parser::buildExpressionTree() {
    std::stack<ExpressionTree*> exprNodeStack;
    int childCount = 0;
    std::vector<ExpressionTree*> param;

    for (ExpressionTree* exprNode : m_postfixExpression) {
        childCount = exprNode->childCount();
        param.clear();

        while (childCount--) {
            if (exprNodeStack.empty())
                throw OperandMissing("operand missing");
            param.push_back(exprNodeStack.top());
            exprNodeStack.pop();
        }
        exprNode->build(param);
        exprNodeStack.push(exprNode);
    }

    if (exprNodeStack.size() != 1)
        throw OperatorMissing("operator missing");

    m_expressionTree.reset(exprNodeStack.top());
    exprNodeStack.pop();
}
