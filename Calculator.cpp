#include "Calculator.h"


ScientificCalculator::ScientificCalculator(
        const std::shared_ptr<Scanner> &scanner,
        const std::shared_ptr<Parser> &parser,
        const std::shared_ptr<Expression> &expression)
{

}

void ScientificCalculator::init()
{
    std::shared_ptr<Scanner> scanner(new Scanner);
    std::shared_ptr<Parser> parser(new Parser);
    std::shared_ptr<Expression> expression(new Expression);

    scanner->init();
    parser->init();
    expression->init();

    m_scanner = scanner;
    m_parser = parser;
    m_expression = expression;
}

void ScientificCalculator::evaluate() {
    buildExpression();
    m_expression->evaluate();

    m_result = m_expression->getResult();
    m_message = m_infixExpression;
}


void ConversionCalculator::init()
{

}

void ConversionCalculator::evaluate()
{

}
