#include "Calculator.h"


// constructor
Calculator::Calculator() :
    m_lexemePattern(new std::string),
    m_scannedExpression(new std::string),
    m_expression(new Expression),

    m_scanner(new Scanner),
    m_parser(new Parser) {
    configureScanner();
    configureParser();

    m_result.first = std::make_shared<std::string>();
    m_result.second = std::make_shared<std::string>();
}

// destructor
Calculator::~Calculator() {}

// evaluate
void Calculator::evaluate() {
    m_parser->parse();
    updateResult(m_expression->evaluate());
}

// reset
void Calculator::reset() {
    m_scannedExpression->clear();
    m_result.first->clear();
    m_result.second->clear();
    m_history.clear();
}

std::pair<StringPtr, StringPtr> Calculator::getHistory(int index) const {
    if (m_history.empty())
        return std::make_pair(std::make_shared<std::string>(),
                              std::make_shared<std::string>());

    int hSize = (int)m_history.size();

    // index range expected: [-hSize, -1]
    index = index > -1 ? -1 : index;            // now index range is (-infinity, -1]
    index = index < -hSize ? -hSize : index;    // now index range is [-hSize, -1]

    return m_history[index];
}

void Calculator::updateResult(double value) {
    *m_result.first = *m_scannedExpression;
    *m_result.second = doubleToString(value);
}

// configureScanner
void Calculator::configureScanner() {
    m_scanner->setScannedExpression(m_scannedExpression);
    m_scanner->setLexemePattern(m_lexemePattern);
}

// configureParser
void Calculator::configureParser() {
    m_parser->setExpression(m_expression);
    m_parser->setScannedExpression(m_scannedExpression);
}

// doubleToString
std::string Calculator::doubleToString(double value) {
    return std::to_string(value);
}
