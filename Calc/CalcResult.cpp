#include "CalcResult.h"

ResultHandler::ResultHandler() :
    _currentResult(std::make_pair(std::string(""), std::string("0"))),
    _errorState(ERROR_NOERROR) { }

void ResultHandler::updateHisotry() {
    if (_historySize == _history.size())
        _history.pop_back();
    _history.push_front(_currentResult);
}
