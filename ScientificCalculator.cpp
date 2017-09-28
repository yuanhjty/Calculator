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

// evaluate
void ScientificCalculator::evaluate() {
    m_parser->parse(m_scannedExpression);
    m_Expression->evaluate();
    updateValidExpression();
    updateResult();
}

// configureScanner
void ScientificCalculator::configureScanner() {
    m_scanner->setExpression(m_scannedExpression);
    m_scanner->setLexemePattern(m_lexemePattern);
}

// configureLexemePattern
void ScientificCalculator::configureLexemePattern(const std::string &lexemePattern) {
    *m_lexemePattern = lexemePattern;
}

// configureParser
void ScientificCalculator::configureParser() {
    m_parser->setExpression(m_Expression);
}
