#include "ScientificCalculator.h"


//
// Implement public methods
//
// constructor
ScientificCalculator::ScientificCalculator() :
    Calculator(),
    m_Expression(new Expression),
    m_scanner(new Scanner),
    m_parser(new Parser) {
    configureLexemePattern(LexemePattern::numReal
                           + "|" + LexemePattern::opCommon
                           + "|" + LexemePattern::symFunction
                           + "|" + LexemePattern::parenthesis
                           + "|" + LexemePattern::space);
    configureScanner();
    configureParser();
}

// configureScanner
void ScientificCalculator::configureScanner() {
    m_scanner->setExpression(m_scannedExpression);
    m_scanner->setLexemePattern(m_lexemePattern);
}

// configureParser
void ScientificCalculator::configureParser() {
    m_parser->setExpression(m_Expression);
}

// configureLexemePattern
void ScientificCalculator::configureLexemePattern(const std::string &lexemePattern) {
    *m_lexemePattern = lexemePattern;
}


//
// override methods
//
// evaluate
void ScientificCalculator::evaluate() {
    m_parser->parse(m_scannedExpression);
    updateResult(m_Expression->evaluate());
}

// showHistory
std::string ScientificCalculator::showHistory(int index) const {    // index = -1, -2, -3, ...
    int hSize = m_history->size();

    // index range expected: [-hSize, -1]
    index = index > -1 ? -1 : index;            // now index range is (-infinity, -1]
    index = index < -hSize ? -hSize : index;    // now index range is [-hSize, -1]

    return formatResult(m_history->at(hSize + index));
}

// formatResult
std::string ScientificCalculator::formatResult(const std::pair<std::string, std::string>& result) const{
    return result.first + "\n= " + result.second;
}

void ScientificCalculator::updateResult(const std::string& value) {
    m_result->first = *m_scannedExpression;
    m_result->second = value;
}
