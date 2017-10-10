#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "Scanner.h"

#include <string>
#include <deque>
#include <memory>


// The class Calculator.
class Calculator {
protected:
    std::unique_ptr<Scanner> m_scanner;
    std::pair<std::string, std::string> m_result;
    std::deque<std::pair<std::string, std::string>> m_history;

    static const int historySize = 1000;

public:
    Calculator();
    virtual ~Calculator();

    void setLexemePattern(const std::string &lexemePattern);
    std::pair<std::string, std::string> getResult() const;
    std::pair<std::string, std::string> getHistory(int index) const;  // index = -1, -2, -3, ...

    void scan(const std::string &input);
    void updateHistory();
    void reset();

    virtual void init() = 0;
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


#endif // CALCULATOR_H
