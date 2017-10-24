#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Lexeme.h"
#include "Scanner.h"
#include "Parser.h"
#include "CalcResult.h"
#include "CalcError.h"
#include "NumeralFormat.h"


class Calculator {
public:
    typedef double ValueType;
    typedef ResultHandler::ResultType ResultType;

public:
    Calculator(Parser *parser, std::string (*toString)(double));
    virtual ~Calculator();

    virtual void setNumeralFormat(NumeralFormat format) = 0;

    void evaluate(const std::string &userExpression);

    void updateHistory();
    void clearHistory();
    void clear();

    ValueType currentValue() const;
    std::string currentValueStr() const;
    ResultType currentResult() const;
    const std::deque<ResultType> *history() const;
    ErrorFlags errorState() const;

protected:
    Scanner *_scanner;
    ResultHandler *_resultHandler;
    Parser *_parser;
    std::string (*_toString)(double);
};


inline void Calculator::updateHistory() {
    _resultHandler->updateHisotry();
}

inline void Calculator::clearHistory() {
    _resultHandler->clearHistory();
}

inline void Calculator::clear() {
    evaluate("");
}

inline Calculator::ValueType Calculator::currentValue() const {
    return _parser->value();
}

inline std::string Calculator::currentValueStr() const {
    return _toString(_parser->value());
}

inline Calculator::ResultType Calculator::currentResult() const {
    return _resultHandler->currentResult();
}

inline const std::deque<Calculator::ResultType> *Calculator::history() const {
    return _resultHandler->history();
}

inline ErrorFlags Calculator::errorState() const {
    return _resultHandler->errorState();
}

#endif // CALCULATOR_H
