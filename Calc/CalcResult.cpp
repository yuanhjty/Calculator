#include "CalcResult.h"

ResultHandler::ResultHandler() :
    _currentResult(std::make_pair(std::string(""), std::string(""))),
    _errorState(ERROR_NOERROR) { }

void ResultHandler::setCurrentResult(const std::string &formattedExpression, const std::string &value) {
    _currentResult.first = formattedExpression;
    _currentResult.second = value;
}

void ResultHandler::updateHisotry() {
    if (_historySize == _history.size())
        _history.pop_back();
    _history.push_front(_currentResult);
}
