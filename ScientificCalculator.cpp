#include "ScientificCalculator.h"

#include <sstream>

// constructor
ScientificCalculator::ScientificCalculator() :
    Calculator(),
    m_expression(new Expression),
    m_parser(new Parser) {
    setLexemePattern(LexicalSet::getScientificRealSet());
}

// evaluate
void ScientificCalculator::evaluate() {
    m_parser->parse(m_scanner->getExpression());
    m_expression->setExpressionTree(m_parser->getExpressionTree());
    setResult(m_scanner->getExpression(), valueToString(m_expression->evaluate()));
}

std::string ScientificCalculator::valueToString(double value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

