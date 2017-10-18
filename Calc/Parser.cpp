#include "Parser.h"
#include "CalcError.h"

#include <sstream>


TreeParser::TreeParser() :
    _symbolTable(nullptr), _exprTree(nullptr) { }

TreeParser::~TreeParser() {
    destroyExprTree();
}

void TreeParser::parse(const std::string &infixExpr) {
    destroyExprTree();
    buildPostfixExpr(infixExpr);
    buildExprTree();
}

void TreeParser::buildPostfixExpr(const std::string &infixExpr) {
    std::stack<std::string> operatorStack;
    std::istringstream is(infixExpr);

    std::string token;
    const ExprNode *currNode;
    const ExprNode *precOperator;

    ExprAttr precType = TYPE_DUMMY_NODE;
    bool isPrefixOperator = true;

    while (is >> token) {
        if ("-" == token && true == isPrefixOperator)
            token = "u-";

        if ((currNode = _symbolTable->exprNode(token)) != nullptr) {
            if (!currNode->isPrecursorValid(precType)) {
                destroyPostfixExpr();

                ErrorFlags filterFlag = (TYPE_BINARY_OPERATOR == precType) ?
                            FILTER_REPLACE : FILTER_IGNORE;
                throw SyntaxError("invalid operator: " + token, filterFlag);
            }

            while (!operatorStack.empty() && operatorStack.top() != "(") {
                precOperator = _symbolTable->exprNode(operatorStack.top());
                if (currNode->priority() < precOperator->priority()
                        || (currNode->priority() == precOperator->priority()
                            && currNode->associativity() == ASSO_LEFT)) {
                    _postfixExpr.push_back(precOperator->newNode());
                    operatorStack.pop();
                } else {
                    break;
                }
            }
            operatorStack.push(token);

            precType = currNode->nodeType();
            isPrefixOperator = (precType == TYPE_BINARY_OPERATOR
                                || precType == TYPE_PREFIX_OPERATOR) ?
                        true : false;
        }
        else if ("(" == token) {
            if (TYPE_OPERAND == precType
                    || TYPE_POSTFIX_OPERATOR == precType
                    || TYPE_RIGHT_BRACKET == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", FILTER_IGNORE);
            }

            operatorStack.push(token);
            precType = TYPE_LEFT_BRACKET;
            isPrefixOperator = true;
        }
        else if (")" == token) {
            if (TYPE_BINARY_OPERATOR == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", FILTER_REPLACE);
            }
            else if (TYPE_PREFIX_OPERATOR == precType
                     || TYPE_LEFT_BRACKET == precType
                     || TYPE_DUMMY_NODE == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", FILTER_IGNORE);
            }

            while (!operatorStack.empty() && (operatorStack.top() != "(")) {
                currNode = _symbolTable->exprNode(operatorStack.top());
                _postfixExpr.push_back(currNode->newNode());
                operatorStack.pop();
            }
            if (operatorStack.empty()) {
                destroyPostfixExpr();
                throw SyntaxError("bracket matching failed: '(' missing", FILTER_IGNORE);
            }

            operatorStack.pop();    // pop "("
            precType = TYPE_RIGHT_BRACKET;
            isPrefixOperator = false;
        }
        else {
            if (TYPE_OPERAND == precType
                    || TYPE_POSTFIX_OPERATOR == precType
                    || TYPE_RIGHT_BRACKET == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", FILTER_IGNORE);
            }

            try {
                double value = std::stod(token);
                ExprNode *number = new Number(value);
                _postfixExpr.push_back(number);
            } catch (std::invalid_argument) {
                destroyPostfixExpr();
                throw SyntaxError("undefined symbol: " + token, FILTER_IGNORE);
            } catch (std::out_of_range) {
                destroyPostfixExpr();
                throw std::overflow_error("floating point number overflow");
            }

            precType = TYPE_OPERAND;
            isPrefixOperator = false;
        }
    }

    while (!operatorStack.empty()) {
        const std::string& token = operatorStack.top();
        if ("(" == token) {
            continue;   // The ')' at the end can be omitted.
                        // This '(' can be considered to match the omitted ')' at the end.
//            destroyPostfixExpr();
//            throw SyntaxError("bracket matching failed: ')' missing");
        }

        currNode = _symbolTable->exprNode(token);
        _postfixExpr.push_back(currNode->newNode());
        operatorStack.pop();
    }
}

void TreeParser::buildExprTree() {
    std::stack<ExprNode *> exprNodeStack;
    std::vector<ExprNode *> param;

    for (const auto &exprNode : _postfixExpr) {
        param.clear();
        int numberOfChildren = exprNode->numberOfChildren();

        while (numberOfChildren--) {
            if (exprNodeStack.empty()) {
                destroyPostfixExpr();
                throw SyntaxError("operand missing", REPAIR_APPEND);
            }

            param.push_back(exprNodeStack.top());
            exprNodeStack.pop();
        }

        exprNode->setChildren(param);
        exprNodeStack.push(exprNode);
    }

    if (1 == exprNodeStack.size())
        _exprTree = exprNodeStack.top();
    else if (exprNodeStack.empty()) {
        destroyPostfixExpr();
        throw std::runtime_error("empty expression");
    }
    else {
        destroyPostfixExpr();
        throw std::runtime_error("unknown error");
    }
}

void TreeParser::destroyExprTree() {
    if (_exprTree) {
        delete _exprTree;
        _exprTree = nullptr;
    }
    _postfixExpr.clear();
}

void TreeParser::destroyPostfixExpr() {
    for (auto &node : _postfixExpr) {
        if (node) {
            delete node;
            node = nullptr;
        }
    }
    _postfixExpr.clear();
}
