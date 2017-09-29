#include "Calculator.h"


// constructor
Calculator::Calculator() :
    m_lexemePattern(new std::string),
    m_scannedExpression(new std::string),
    m_result(new std::pair<std::string, std::string>),
    m_history(new std::vector<std::pair<std::string, std::string>>) {}

// destructor
Calculator::~Calculator() {}

// clear
//void Calculator::clear() {
//    m_scannedExpression->clear();
//    m_validExpression->clear();
//    m_result->clear();
//}

// reset
void Calculator::reset() {
    m_scannedExpression->clear();
//    m_validExpression->clear();
    m_result->first.clear();
    m_result->second.clear();
    m_history->clear();
}

//std::pair<std::string, std::string> Calculator::getHistory(int index) {
//    int hSize = m_history->size();

//    // index range should be [-hSize, -1]
//    index = index > -1 ? -1 : index;            // now index range is (-infinity, -1]
//    index = index < -hSize ? -hSize : index;    // now index range is [-hSize, -1]

//    return m_history->at(hSize + index);
//}

