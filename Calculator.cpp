#include "Calculator.h"


void ScientificCalculator::init()
{
    std::shared_ptr<Scanner> scanner(new Scanner);
    std::shared_ptr<Parser> parser(new Parser);

    scanner->init();
    parser->init();

    setScanner(scanner);
    setParser(parser);
}

void ScientificCalculator::evaluate() {
    m_parser->parse(m_infixExpression);

    std::shared_ptr<Expression> expression(
                new Expression(m_parser->getExpressionTree()));
    setExpression(expression);

    m_expression->evaluate();
}

void ScientificCalculator::scanInput(const std::string &input) {
    m_scanner->scan(input);
    setInfixExpression(m_scanner->getExpression());
}
