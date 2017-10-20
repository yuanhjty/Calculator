#ifndef CALC_RESULT_H
#define CALC_RESULT_H

#include "CalcError.h"

#include <utility>
#include <string>
#include <deque>


class ResultHandler {
public:
    typedef std::pair<std::string, std::string> ResultType;

public:
    ResultHandler();
    void setCurrentResult(const std::string &expr,
                          const std::string &value);
    void updateCurrentValue(const std::string &value);
    void updateCurrentExpr(const std::string &expr);
    void setErrorState(ErrorFlags errorState);
    void updateHisotry();
    void clearHistory();
    ResultType currentResult() const;
    const std::deque<ResultType> *history() const;
    ErrorFlags errorState() const;


private:
    ResultType _currentResult;
    std::deque<ResultType> _history;
    ErrorFlags _errorState;

    // static date members
    static const size_t _historySize = 1000;
};

inline void ResultHandler::setCurrentResult(const std::string &expr, const std::string &value) {
    _currentResult.first = expr;
    _currentResult.second = value;
}

inline void ResultHandler::updateCurrentValue(const std::string &value) {
    _currentResult.second = value;
}

inline void ResultHandler::updateCurrentExpr(const std::string &expr) {
    _currentResult.first = expr;
}

inline void ResultHandler::setErrorState(ErrorFlags errorState) {
    _errorState = errorState;
}

inline void ResultHandler::clearHistory() {
    _history.clear();
}

inline ResultHandler::ResultType ResultHandler::currentResult() const {
    return _currentResult;
}

inline const std::deque<ResultHandler::ResultType> *ResultHandler::history() const {
    return &_history;
}

inline ErrorFlags ResultHandler::errorState() const {
    return _errorState;
}

#endif // CALC_RESULT_H
