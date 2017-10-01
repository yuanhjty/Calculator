#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "Expression.h"
#include "Scanner.h"
#include "Parser.h"
#include "Util.h"

#include <string>
#include <vector>
#include <memory>


// The class Calculator.
class Calculator {
protected:
    // Shared resources
    StringPtr m_lexemePattern;
    StringPtr m_scannedExpression;
    std::shared_ptr<Expression> m_expression;

    // Unique resources
    std::unique_ptr<Scanner> m_scanner;
    std::unique_ptr<Parser> m_parser;

    std::pair<StringPtr, StringPtr> m_result;
    std::vector<std::pair<StringPtr, StringPtr>> m_history;

public:
    Calculator();
    virtual ~Calculator();

    void updateLexemePattern(const std::string& lexemePattern);
    void scanInput(const StringPtr &input);
    void evaluate();
    void updateHistory();
    void reset();
    std::pair<StringPtr, StringPtr> getResult() const;
    std::pair<StringPtr, StringPtr> getHistory(int index) const;  // index = -1, -2, -3, ...

protected:
    void updateResult(double value);
    void configureScanner();
    void configureParser();
    virtual std::string doubleToString(double value);
};


// updateLexemePattern
inline void Calculator::updateLexemePattern(const std::string& lexemePattern) {
    *m_lexemePattern = lexemePattern;
}

// scanInput
inline void Calculator::scanInput(const StringPtr &input) {
    m_scanner->scan(input);
}

// updateHistory
inline void Calculator::updateHistory() {
    m_history.push_back(m_result);
}

// getResult
inline std::pair<StringPtr, StringPtr> Calculator::getResult() const {
    return m_result;
}




#endif // CALCULATOR_H
