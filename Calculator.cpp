#include "Calculator.h"


Calculator::Calculator() :
    m_lexemePattern(new std::string),
    m_scannedExpression(new std::string),
    m_validExpression(new std::string),
    m_result(new std::string),
    m_history(new std::vector<std::pair<std::string, std::string>>) {}

void Calculator::clear() {
    m_scannedExpression->clear();
    m_validExpression->clear();
    m_result->clear();
}

void Calculator::reset() {
    clear();
    m_history->clear();
}

std::pair<std::string, std::string> Calculator::getHistory(int index) {
    int hSize = m_history->size();

    // index range should be [-hSize, -1]
    index = index > -1 ? -1 : index;            // now index range is (-infinity, -1]
    index = index < -hSize ? -hSize : index;    // now index range is [-hSize, -1]

    return m_history->at(hSize + index);
}
