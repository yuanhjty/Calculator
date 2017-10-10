#ifndef EXPRESSIONEXCEPTION_H
#define EXPRESSIONEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>


class SymbolError : public std::logic_error {
public:
    SymbolError(const std::string& msg) : logic_error(msg) {}
};


class OperandError : public std::logic_error {
public:
    OperandError(const std::string& msg) : logic_error(msg) {}
};


class OperatorError : public std::logic_error {
public:
    OperatorError(const std::string& msg) : logic_error(msg) {}
};


class ParenthesesError : public std::logic_error {
public:
    ParenthesesError(const std::string& msg) : logic_error(msg) {}
};


class ArgumentError : public std::logic_error {
public:
    ArgumentError(const std::string& msg) : logic_error(msg) {}
};


class NotCompleteError : public std::logic_error {
public:
    NotCompleteError(const std::string& msg) : logic_error(msg) {}
};


class InnerError : public std::runtime_error {
public:
    InnerError(const std::string& msg) : runtime_error(msg) {}
};

#endif // EXPRESSIONEXCEPTION_H
