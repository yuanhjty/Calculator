#include "TreeParser.h"
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

                ErrorFlags repairFlag = (TYPE_BINARY_OPERATOR == precType) ?
                            REPAIR_REPLACE : REPAIR_IGNORE;
                throw SyntaxError("invalid operator: " + token, repairFlag);
            }

            if (currNode->nodeType() == TYPE_OPERAND) {
                _postfixExpr.push_back(currNode->newNode());
            } else {
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
            }

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
                throw SyntaxError("syntax error", REPAIR_IGNORE);
            }

            operatorStack.push(token);
            precType = TYPE_LEFT_BRACKET;
            isPrefixOperator = true;
        }
        else if (")" == token) {
            if (TYPE_BINARY_OPERATOR == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", REPAIR_REPLACE);
            }
            else if (TYPE_PREFIX_OPERATOR == precType
                     || TYPE_LEFT_BRACKET == precType
                     || TYPE_DUMMY_NODE == precType) {
                destroyPostfixExpr();
                throw SyntaxError("syntax error", REPAIR_IGNORE);
            }

            while (!operatorStack.empty() && (operatorStack.top() != "(")) {
                currNode = _symbolTable->exprNode(operatorStack.top());
                _postfixExpr.push_back(currNode->newNode());
                operatorStack.pop();
            }
            if (operatorStack.empty()) {
                destroyPostfixExpr();
                throw SyntaxError("bracket matching failed: '(' missing", REPAIR_IGNORE);
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
                throw SyntaxError("syntax error", REPAIR_IGNORE);
            }

            try {
                ValueType value = _toValue(token); // may throw exception
                ExprNode *number = new Number(value);
                _postfixExpr.push_back(number);
            } catch (...) {
                destroyPostfixExpr();
                throw;
            }

            precType = TYPE_OPERAND;
            isPrefixOperator = false;
        }
    }

    while (!operatorStack.empty()) {
        const std::string& token = operatorStack.top();
        if ("(" == token) {
            operatorStack.pop();
            continue;   // The ')' at the end can be omitted.
        }

        currNode = _symbolTable->exprNode(token);
        _postfixExpr.push_back(currNode->newNode());
        operatorStack.pop();
    }
}

void TreeParser::buildExprTree() {
    std::stack<ExprNode *> exprNodeStack;
    std::vector<ExprNode *> param;

    for (auto it = _postfixExpr.begin(); it != _postfixExpr.end(); ++it) {
        param.clear();
        int numberOfChildren = (*it)->numberOfChildren();

        while (numberOfChildren--) {
            if (exprNodeStack.empty()) {
                // Now, current (*it) has associated to all (*it)s in front of current (*it).
                // Delete current (*it) means delete all (*it)s in front of current (*it).
                // So delete current (*it) and all (*it)s behind current (*it) to free all memroy.
                for (; it != _postfixExpr.end(); ++it) {
                    delete (*it);
                    (*it) = nullptr;
                }
                throw SyntaxError("operand missing", REPAIR_APPEND);
            }

            param.push_back(exprNodeStack.top());
            exprNodeStack.pop();
        }

        (*it)->setChildren(param);
        exprNodeStack.push(*it);
    }

    if (1 == exprNodeStack.size()) {
        _exprTree = exprNodeStack.top();
    } else if (1 < exprNodeStack.size()) {
        destroyPostfixExpr();
        throw InnerError("unknown error");
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
