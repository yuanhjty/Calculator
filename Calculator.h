#ifndef CALCULATOR_H
#define CALCULATOR_H


<<<<<<< HEAD
#include <string>
#include "Expression.h"


class Calculator {
public:
    Calculator() : _expression(new Expression) {}

    ~Calculator() {
        if (_expression) delete _expression;
    }

    void reset() {
        _expression->reset();
    }

    void setInfix(const std::string& expression) {
        _expression->setInfix(expression);
    }

    void setPostfix() {
        _expression->setPostfix();
    }

    void evaluate() {
        _expression->evaluate();
    }

    std::string getInfix() const {
        return _expression->getInfix();
    }

    std::string getPostfix() const {
        return _expression->getPostfix();
    }

    double getResult() const {
        return _expression->getResult();
    }

private:
    Expression* _expression;
};
=======
#include "Scanner.h"

#include <string>
#include <vector>
#include <memory>


// The class Calculator.
class Calculator {
protected:
    std::unique_ptr<Scanner> m_scanner;
    std::pair<std::string, std::string> m_result;
    std::vector<std::pair<std::string, std::string>> m_history;

public:
    Calculator();
    virtual ~Calculator();

    void setLexemePattern(const std::string &lexemePattern);
    std::pair<std::string, std::string> getResult() const;
    std::pair<std::string, std::string> getHistory(int index) const;  // index = -1, -2, -3, ...

    void scan(const std::string &input);
    void updateHistory();
    void reset();

    virtual void evaluate() = 0;

protected:
    void setResult(const std::string &expression, const std::string &value);
};


// setLexemePattern
inline void Calculator::setLexemePattern(const std::string& lexemePattern) {
    m_scanner->setLexemePattern(lexemePattern);
}

// getResult
inline std::pair<std::string, std::string> Calculator::getResult() const {
    return m_result;
}

// scan
inline void Calculator::scan(const std::string &input) {
    m_scanner->scan(input);
}
>>>>>>> refactor1


#endif // CALCULATOR_H
