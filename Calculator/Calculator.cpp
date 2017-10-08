#include "Calculator.h"


// constructor
Calculator::Calculator() : m_scanner(new Scanner) {}

// destructor
Calculator::~Calculator() {}

// reset
void Calculator::reset() {
    m_scanner->reset();
    m_result.first.clear();
    m_result.second.clear();
    m_history.clear();
}

// getHistory
std::pair<std::string, std::string> Calculator::getHistory(int index) const {
    if (m_history.empty())
        return std::pair<std::string, std::string>();

    int hSize = (int)m_history.size();

    // index range expected: [-hSize, -1]
    index = index > -1 ? -1 : index;            // now index range is (-infinity, -1]
    index = index < -hSize ? -hSize : index;    // now index range is [-hSize, -1]

    return m_history[hSize + index];
}

// updateResult
void Calculator::setResult(const std::string &expression, const std::string &value) {
    m_result.first = expression;
    m_result.second = value;
}

// updateHistory
void Calculator::updateHistory() {
    if (historySize == m_history.size())
        m_history.pop_front();
    m_history.push_back(m_result);
}
