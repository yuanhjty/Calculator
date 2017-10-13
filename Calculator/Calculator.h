#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "Scanner.h"

#include <string>
#include <deque>
#include <memory>


// The class Calculator.
class Calculator {
public:
    typedef std::pair<std::string, std::string> Result_Type;

protected:
    std::unique_ptr<Scanner> m_scanner;
    Result_Type m_result;
    std::deque<Result_Type> m_history;

    static const int historySize = 1000;

public:
    Calculator();
    virtual ~Calculator();

    void setLexemePattern(const std::string &lexemePattern);
    Result_Type getResult() const;
    Result_Type getHistory(int index) const;  // index = -1, -2, -3, ...
    std::deque<Result_Type>* getHistory();

    void scan(const std::string &input);
    void updateHistory();
    void clearHistory();

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
inline Calculator::Result_Type Calculator::getResult() const {
    return m_result;
}

inline std::deque<Calculator::Result_Type>* Calculator::getHistory() {
    return &m_history;
}

// scan
inline void Calculator::scan(const std::string &input) {
    m_scanner->scan(input);
}

// clearHistory
inline void Calculator::clearHistory() {
    m_history.clear();
}


#endif // CALCULATOR_H
