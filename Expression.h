#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <string>
#include <exception>


class InfixError : public std::logic_error {
public:
    InfixError(const std::string& msg) : logic_error(msg) {}
};


class EvaluateError: public std::logic_error {
public:
    EvaluateError(const std::string& msg) : logic_error(msg) {}
};


class Expression {
public:
    Expression();
    ~Expression();

    void reset();
    void setInfix(const std::string& expression);
    void setPostfix();
    void evaluate();

    std::string getInfix() const {
        return *_infixPtr;
    }

    std::string getPostfix() const {
        return *_postfixPtr;
    }

    double getResult() const {
        return _result;
    }

private:
    std::string* _infixPtr;
    std::string* _postfixPtr;
    double _result;
};


#endif // EXPRESSION_H
