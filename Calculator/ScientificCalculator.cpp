#include "ScientificCalculator.h"

#include <sstream>
#include <set>

// constructor
ScientificCalculator::ScientificCalculator() :
    Calculator(),
    m_symbolTable(new SymbolTable),
    m_expression(new Expression),
    m_parser(new Parser) {
    m_parser->setSymbolTable(m_symbolTable);
}

ScientificCalculator::~ScientificCalculator() {
    if (m_expression) delete m_expression;
    if (m_parser) delete m_parser;
}

void ScientificCalculator::init() {
    initSymbolTable();
    setLexemePattern(LexicalSet::getRealExprLexicalSet());
}

// evaluate
void ScientificCalculator::evaluate() {
    m_expression->setExpressionTree(m_parser->parse(m_scanner->getExpression()));
    setResult(m_scanner->getExpression(), valueToString(m_expression->evaluate()));
}

std::string ScientificCalculator::valueToString(double value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void ScientificCalculator::initSymbolTable() {
    m_symbolTable->registerBinaryOperator ("+", new Plus);
    m_symbolTable->registerBinaryOperator ("-", new BMinus);
    m_symbolTable->registerBinaryOperator ("*", new Multi);
    m_symbolTable->registerBinaryOperator ("/", new Divide);
    m_symbolTable->registerBinaryOperator ("%", new Modulo);
    m_symbolTable->registerBinaryOperator ("^", new Power);

    // bitwise
//    m_symbolTable->registerBinaryOperator ("or", new BitOr);
//    m_symbolTable->registerBinaryOperator ("and", new BitAnd);
//    m_symbolTable->registerBinaryOperator ("xor", new BitXor);

    m_symbolTable->registerPrefixOperator ("u-", new UMinus);
    m_symbolTable->registerPrefixOperator ("sin", new Sin);
    m_symbolTable->registerPrefixOperator ("cos", new Cos);
    m_symbolTable->registerPrefixOperator ("tan", new Tan);
    m_symbolTable->registerPrefixOperator ("asin", new ASin);
    m_symbolTable->registerPrefixOperator ("acos", new ACos);
    m_symbolTable->registerPrefixOperator ("atan", new ATan);
    m_symbolTable->registerPrefixOperator ("lg", new Lg);
    m_symbolTable->registerPrefixOperator ("ln", new Ln);

    // not implemented
//    m_symbolTable->registerPrefixOperator ("!", new Fact);

    // bitwise
//    m_symbolTable->registerPostfixOperator("not", new BitNot);

    m_symbolTable->registerVariable("pi", new ConstPi);
    m_symbolTable->registerVariable("e", new ConstE);
}

