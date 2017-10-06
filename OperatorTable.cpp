#include "OperatorTable.h"


OperatorTable* OperatorTable::m_operatorTable = new OperatorTable;

OperatorTable* OperatorTable::getInstance() {
    return m_operatorTable;
}

OperatorTable::~OperatorTable() {
    releaseBinaryOperators();
    releaseUnaryOperators();
    if (m_operatorTable) delete m_operatorTable;
}

ExpressionTree *OperatorTable::getOperator(const std::string &token) {
    std::map<std::string, ExpressionTree*>::const_iterator it;
    if ((it = m_binaryOperators.find(token)) != m_binaryOperators.cend()
            || (it = m_unaryOperators.find(token)) != m_unaryOperators.cend())
        return it->second;
    else
        return nullptr;
}

OperatorTable::OperatorTable() {
    initBinaryOperators();
    initUnaryOperators();
    initPrefixOperators();
    initPostfixOperators();
}

void OperatorTable::registerBinaryOperator(const std::string& name, ExpressionTree* binaryOperator) {
    binaryOperators.insert(std::make_pair(name, binaryOperator));
}

void OperatorTable::registerUnaryOperator(const std::string& name, ExpressionTree* unaryOperator) {
    unaryOperators.insert(std::make_pair(name, unaryOperator));
}

void OperatorTable::initBinaryOperators() {
    // real
    registerOperator("+", new Plus);
    registerOperator("-", new BMinus);
    registerOperator("*", new Multi);
    registerOperator("/", new Divide);
    registerOperator("^", new Pow);

    // bitwise
    registerOperator("or", new BitOr);
    registerOperator("and", new BitAnd);
    registerOperator("xor", new BitXor);
}

void OperatorTable::initUnaryOperators() {
    // real
    registerOperator("!", new Fact);
    registerOperator("u-", new UMinus);
    registerOperator("sin", new Sin);
    registerOperator("cos", new Cos);
    registerOperator("tan", new Tan);
    registerOperator("asin", new ASin);
    registerOperator("acos", new ACos);
    registerOperator("atan", new ATan);
    registerOperator("lg", new Lg);
    registerOperator("ln", new Ln);

    // bitwise, unary
    registerOperator("not", new BitNot);
}

void OperatorTable::initPrefixOperators() {
    m_prefixOperators.insert(
    {"u-", "sin", "cos", "tan", "asin", "acos",
     "atan", "lg", "ln", "not"});
}

void OperatorTable::initPostfixOperators() {
    m_postfixOperators.insert({"!"});
}

void OperatorTable::releaseBinaryOperators() {
    for (auto it : binaryOperators) {
        delete it->second;
    }
}

void OperatorTable::releaseUnaryOperators() {
    for (auto it : unaryOperators) {
        delete it->second;
    }
}

