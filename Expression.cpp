#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>

#include "Expression.h"
#include "ExpressionUtil.h"


Expression::Expression() :
    _postfixPtr(new std::string),
    _infixPtr(new std::string),
    _result(0) {}

Expression::~Expression() {
    if (_postfixPtr) delete _postfixPtr;
}

void Expression::reset() {
    _infixPtr->clear();
    _postfixPtr->clear();
    _result = 0;
}

void Expression::setInfix(const std::string& expression) {
    auto exprBeg = expression.cbegin();
    auto exprEnd = expression.cend();

    auto operBeg = operators.cbegin();
    auto operEnd = operators.cend();

    for (auto it = exprBeg; it != exprEnd; ++it) {

        if (*it < -1 || *it > 255)
            throw InfixError(std::string("Undifined symbol: ")
                             + *it + *(it + 1));

        // one-character operators
        else if (std::find(operBeg, operEnd,
                      std::string(1, *it)) != operEnd
                || *it == '(' || *it == ')') {

            if (it != exprBeg && *(it - 1) != ' ')
                _infixPtr->append(1, ' ');

            _infixPtr->append(1, *it);

            if (it != exprEnd - 1 && *(it + 1) != ' ')
                _infixPtr->append(1, ' ');
        }

        // three-character operators
        else if (exprEnd - it > 3 &&
                   std::find(operBeg, operEnd,
                             std::string(it, it + 3)) != operEnd) {

            if (it != exprBeg && *(it - 1) != ' ')
                _infixPtr->append(1, ' ');

            _infixPtr->append(it, it + 3);
            it += 2;

            if (it != exprEnd - 1 && *(it + 1) != ' ')
                _infixPtr->append(1, ' ');
        }

        // four-character operators
        else if (exprEnd - it > 4 &&
                   std::find(operBeg, operEnd,
                             std::string(it, it + 4)) != operEnd) {

            if (it != exprBeg && *(it - 1) != ' ')
                _infixPtr->append(1, ' ');

            _infixPtr->append(it, it + 4);
            it += 3;

            if (it != exprEnd - 1 && *(it + 1) != ' ')
                _infixPtr->append(1, ' ');
        }

        // operands and whites
        else {
            if (!isspace(*it))
                _infixPtr->append(1, *it);
            else if (it != exprBeg && *(it - 1) != ' ')
                _infixPtr->append(1, ' ');
        }
    }

    // Discard whites in the end.
    for (size_t i = _infixPtr->size() - 1; i >= 0 && isspace((*_infixPtr)[i]); --i)
        _infixPtr->pop_back();

    if (_infixPtr->find('=') == _infixPtr->size() - 1)
        _infixPtr->pop_back();

    if (_infixPtr->find('=') != std::string::npos)
        throw InfixError("Invalid Expression: incorrect using of '='");
}

void Expression::setPostfix() {
    std::stack<std::string> operatorStack;
    std::string token, prevToken, exprSlice;
    std::string errMsg = "Invalid Expression: ";
    int parenCount = 0;
    bool isUnary = true;

    std::istringstream is(*_infixPtr);

    while (is >> token) {
        exprSlice = prevToken + " " + token;

        // left parentheses
        if (token == "(") {
            if (isOperand(prevToken) || prevToken == ")")
                throw InfixError(errMsg + exprSlice);

            operatorStack.push(token);
            ++parenCount;

            isUnary = true;
        }

        // right parentheses
        else if (token == ")") {
            if (parenCount == 0 || isOperator(prevToken) || prevToken == "(")
                throw InfixError(errMsg + exprSlice);

            while (!operatorStack.empty() && operatorStack.top() != "(") {
                *_postfixPtr += operatorStack.top() + " ";
                operatorStack.pop();
            }

            operatorStack.pop();
            --parenCount;

            isUnary = false;
        }

        // operators
        else if (isOperator(token)) {
            if (token == "-" && isUnary)
                token = "u-";

            if (isBinaryOperator(token)) {
                if (prevToken == "(" || prevToken.empty()
                    || isBinaryOperator(prevToken))
                    throw InfixError(errMsg + exprSlice);
            } else {
                if (prevToken == ")" || isOperand(prevToken))
                    throw InfixError(errMsg + exprSlice);
            }

            if (!operatorStack.empty() &&
                    !(token == operatorStack.top() && isRightAssociative(token))) {
                while (!isPrior(token, operatorStack.top())) {
                    *_postfixPtr += operatorStack.top() + " ";
                    operatorStack.pop();
                }
            }

            operatorStack.push(token);

            isUnary = true;
        }

        // operands
        else if (isOperand(token)) {
            if (prevToken == ")" || isOperand(prevToken))
                throw InfixError(errMsg + exprSlice);

            *_postfixPtr += token + " ";

            isUnary = false;
        }

        // undefined cases
        else {
            throw InfixError("Undefined symbol: " + token);
        }

        prevToken = token;
    }

    while (!operatorStack.empty()) {
        *_postfixPtr += operatorStack.top() + " ";
        operatorStack.pop();
    }

    // Discard whites in the end.
    for (size_t i = _postfixPtr->size() - 1; i >= 0 && isspace((*_postfixPtr)[i]); --i)
        _postfixPtr->pop_back();
}

void Expression::evaluate(){
    std::stack<double> operandStack;
    std::string token;
    std::istringstream is(*_postfixPtr);

    while (is >> token) {
       if (isUnaryOperator(token)) {
           double val = 0;

           if (operandStack.empty())
               throw InfixError("Invalid infix");
           double rhs = operandStack.top();
           operandStack.pop();

           auto it = unaryOperatorsMap.find(token);

           switch(it->second) {
           case OP::U_MIN: val = -1 * rhs ; break;
           case OP::SIN  : val = sin(rhs) ; break;
           case OP::COS  : val = cos(rhs) ; break;
           case OP::TAN  : val = tan(rhs) ; break;
           case OP::ASIN : val = asin(rhs); break;
           case OP::ACOS : val = acos(rhs); break;
           case OP::ATAN : val = atan(rhs); break;
           default       :                  break;
           }

           operandStack.push(val);
       }

       else if (isBinaryOperator(token)) {
           double val = 0;

           if (operandStack.empty())
               throw InfixError("Invalid infix");
           double rhs = operandStack.top();
           operandStack.pop();


           if (operandStack.empty())
               throw InfixError("Invalid infix");
           double lhs = operandStack.top();
           operandStack.pop();

           auto it = binaryOperatorsMap.find(token);

           switch(it->second) {
           case OP::PLUS : val = lhs + rhs    ; break;
           case OP::B_MIN: val = lhs - rhs    ; break;
           case OP::MUL  : val = lhs * rhs    ; break;
           case OP::DIV  : val = lhs / rhs    ; break;
           // case OP::MOD  : val = lhs % rhs    ; break;
           case OP::POW  : val = pow(lhs, rhs); break;
           default       :                    ; break;
           }

           operandStack.push(val);
       }

       else {   // must be operand
           operandStack.push(std::stod(token));
       }
    }

    if (operandStack.size() != 1)
        throw EvaluateError("EvaluateError");
    _result = operandStack.top();
}












