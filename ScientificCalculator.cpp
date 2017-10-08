#include "ScientificCalculator.h"

#include <sstream>
#include <set>

// constructor
ScientificCalculator::ScientificCalculator() :
    Calculator(),
    m_expression(new Expression),
    m_parser(new Parser) ,
    m_operatorTable(OperatorTable::getInstance()) {
    setOperators();
    setLexemePattern(LexicalSet::getRealExprLexicalSet());
}

ScientificCalculator::~ScientificCalculator() {
    if (m_operatorTable) delete m_operatorTable;
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

void ScientificCalculator::setOperators() {
    std::set<std::string> binaryOperators = { "+", "-", "*", "/", "^" };
    std::set<std::string> prefixOPerators = {
        "u-", "sin", "cos", "tan", "asin", "acos", "atan", "lg", "ln" };
    std::set<std::string> postfixOperators = {};

    m_operatorTable->setBinaryOperators(binaryOperators);
    m_operatorTable->setPrefixOperators(prefixOPerators);
    m_operatorTable->setPostfixOperators(postfixOperators);
}

