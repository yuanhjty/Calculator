#include "OperatorTable.h"


//OperatorTable* OperatorTable::m_operatorTable = new OperatorTable;

//OperatorTable* OperatorTable::getInstance() {
//    return m_operatorTable;
//}

OperatorTable* OperatorTable::m_operatorTable = nullptr;

std::mutex OperatorTable::m;

OperatorTable* OperatorTable::getInstance() {
    if (nullptr == m_operatorTable) {
        m.lock();
        if (nullptr == m_operatorTable)
            m_operatorTable = new OperatorTable;
        m.unlock();
    }
    return m_operatorTable;
}

OperatorTable::~OperatorTable() {
    releaseBinaryOperators();
    releaseUnaryOperators();
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
    m_binaryOperators.insert(std::make_pair(name, binaryOperator));
}

void OperatorTable::registerUnaryOperator(const std::string& name, ExpressionTree* unaryOperator) {
    m_unaryOperators.insert(std::make_pair(name, unaryOperator));
}

void OperatorTable::initBinaryOperators() {
    // real
    registerBinaryOperator("+", new Plus);
    registerBinaryOperator("-", new BMinus);
    registerBinaryOperator("*", new Multi);
    registerBinaryOperator("/", new Divide);
    registerBinaryOperator("^", new Pow);

    // bitwise
    registerBinaryOperator("or", new BitOr);
    registerBinaryOperator("and", new BitAnd);
    registerBinaryOperator("xor", new BitXor);
}

void OperatorTable::initUnaryOperators() {
    // real
    registerUnaryOperator("!", new Fact);
    registerUnaryOperator("u-", new UMinus);
    registerUnaryOperator("sin", new Sin);
    registerUnaryOperator("cos", new Cos);
    registerUnaryOperator("tan", new Tan);
    registerUnaryOperator("asin", new ASin);
    registerUnaryOperator("acos", new ACos);
    registerUnaryOperator("atan", new ATan);
    registerUnaryOperator("lg", new Lg);
    registerUnaryOperator("ln", new Ln);

    // bitwise, unary
    registerUnaryOperator("not", new BitNot);
}

void OperatorTable::initPrefixOperators() {
    m_prefixOperators.insert(
    {"u-", "sin", "cos", "tan", "asin", "acos",
     "atan", "lg", "ln", "not"});
}

void OperatorTable::initPostfixOperators() {
    m_postfixOperators.insert({"!"});
}

//#include <iostream>
void OperatorTable::releaseBinaryOperators() {
    for (const auto& item : m_binaryOperators) {
//        std::cerr << item.first << " " << item.second << std::endl;
        delete item.second;
    }
}

void OperatorTable::releaseUnaryOperators() {
    for (const auto& item : m_unaryOperators) {
//        std::cerr << item.first << " " << item.second << std::endl;
        delete item.second;
    }
}

