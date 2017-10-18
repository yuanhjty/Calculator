#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Scanner.h"
#include "Parser.h"
#include "CalcResult.h"
#include "CalcError.h"
#include "DataConvert.h"

#include <string>
#include <deque>
#include <utility>


class Calculator {
public:
    typedef double ValueType;
    typedef ResultHandler::ResultType ResultType;

public:
    Calculator(Parser *parser, DataConverter *dataConvert = nullptr);
    ~Calculator();

    void setDataFormat(DataFormat dataFormat);
    void evaluate(const std::string &userExpression);

    void updateHistory();
    void clearHistory();

    ResultType currentResult() const;
    const std::deque<ResultType> *history() const;
    ErrorFlags errorState() const;

protected:
    Scanner *_scanner;
    ResultHandler *_resultHandler;
    Parser *_parser;
    DataConverter *_dataConvert;
};

inline void Calculator::setDataFormat(DataFormat dataFormat) {
    if (_dataConvert) _dataConvert->setDataFormat(dataFormat);
}

inline void Calculator::updateHistory() {
    _resultHandler->updateHisotry();
}

inline void Calculator::clearHistory() {
    _resultHandler->clearHistory();
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
