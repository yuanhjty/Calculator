#include "SymbolTable.h"


//OperatorTable* OperatorTable::m_operatorTable = new OperatorTable;

//OperatorTable* OperatorTable::getInstance() {
//    return m_operatorTable;
//}

//SymbolTable* SymbolTable::m_operatorTable = nullptr;

//std::mutex SymbolTable::m;

//SymbolTable* SymbolTable::getInstance() {
//    if (nullptr == m_operatorTable) {
//        m.lock();
//        if (nullptr == m_operatorTable)
//            m_operatorTable = new SymbolTable;
//        m.unlock();
//    }
//    return m_operatorTable;
//}

SymbolTable::~SymbolTable() {
    releaseTable(m_variables);
    releaseTable(m_binaryOperators);
    releaseTable(m_prefixOperators);
    releaseTable(m_postfixOperators);
}

ExpressionTree *SymbolTable::getExpressionNode(const std::string &token) const {
    TableType::const_iterator it;

    if ((it = m_binaryOperators.find(token)) != m_binaryOperators.cend())
        return it->second;

    if ((it = m_prefixOperators.find(token)) != m_prefixOperators.cend())
        return it->second;

    if ((it = m_postfixOperators.find(token)) != m_postfixOperators.cend())
        return it->second;

    return m_variables.find(token)->second;
}

void SymbolTable::releaseTable
(const std::unordered_map<std::string, ExpressionTree*>& table) {
    for (const auto& item : table) {
        delete item.second;
    }
}

void SymbolTable::registerSymbol
(const std::string &id, ExpressionTree* obj,
 std::unordered_map<std::string, ExpressionTree*> &table) {
    auto it = table.find(id);
    if (it != table.cend()) {
        delete it->second;
        it->second = obj;
    } else
        table[id] = obj;
}

