#ifndef EXPRESSIONEXCEPTION_H
#define EXPRESSIONEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>


class LeftBracketMissing : public std::logic_error {
public:
    LeftBracketMissing(const std::string& msg) : logic_error(msg) {}
};


class RightBracketMissing : public std::logic_error {
public:
    RightBracketMissing(const std::string& msg) : logic_error(msg) {}
};


class OperandMissing : public std::logic_error {
public:
    OperandMissing(const std::string& msg) : logic_error(msg) {}
};


class OperatorMissing : public std::logic_error {
public:
    OperatorMissing(const std::string& msg) : logic_error(msg) {}
};


class InvalidSymbol : public std::logic_error {
public:
    InvalidSymbol(const std::string& msg) : logic_error(msg) {}
};


class InvalidArgument : public std::logic_error {
public:
    InvalidArgument(const std::string& msg) : logic_error(msg) {}
};


class DivideByZero : public std::logic_error {
public:
    DivideByZero(const std::string& msg) : logic_error(msg) {}
};


class InnerError : public std::runtime_error {
public:
    InnerError(const std::string& msg) : runtime_error(msg) {}
};


class NumericOverflow : public std::overflow_error {
public:
    NumericOverflow(const std::string& msg) : overflow_error(msg) {}
};


#endif // EXPRESSIONEXCEPTION_H
