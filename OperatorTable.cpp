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
    releaseOperators();
}

ExpressionTree *OperatorTable::getOperator(const std::string &token) {
    auto it = m_operators.find(token);
    if (it != m_operators.cend())
        return it->second;
    else
        return nullptr;
}

OperatorTable::OperatorTable() {
    initOperators();
}

void OperatorTable::initOperators() {
    // binary operaotr
    // real
    registerOperator("+", new Plus);
    registerOperator("-", new BMinus);
    registerOperator("*", new Multi);
    registerOperator("/", new Divide);
    registerOperator("%", new Modulo);
    registerOperator("^", new Pow);

    // bitwise
    registerOperator("or", new BitOr);
    registerOperator("and", new BitAnd);
    registerOperator("xor", new BitXor);


    // unary operator
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

    // bitwise
    registerOperator("not", new BitNot);
}

void OperatorTable::releaseOperators() {
    for (const auto& item : m_operators) {
        delete item.second;
    }
}

