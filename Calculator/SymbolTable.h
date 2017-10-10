#ifndef OPERATORTABLE_H
#define OPERATORTABLE_H


#include "ExpressionTree.h"

#include <unordered_map>
#include <string>


class SymbolTable {
public:
    typedef std::unordered_map<std::string, ExpressionTree*> TableType;
private:
    TableType m_binaryOperators;
    TableType m_prefixOperators;
    TableType m_postfixOperators;
    TableType m_variables;

//    static SymbolTable* m_operatorTable;
//    static std::mutex m;

public:
//    static SymbolTable* getInstance();
    ~SymbolTable();

    void registerBinaryOperator(const std::string& id, ExpressionTree *obj);
    void registerPrefixOperator(const std::string& id, ExpressionTree *obj);
    void registerPostfixOperator(const std::string& id, ExpressionTree *obj);
    void registerVariable(const std::string& id, ExpressionTree *obj);

    bool hasBinaryOperator(const std::string& token) const;
    bool hasPrefixOperator(const std::string& token) const;
    bool hasPostfixOperator(const std::string& token) const;
    bool hasVariable(const std::string& token) const;

    ExpressionTree* getExpressionNode(const std::string& token) const;

private:
    void releaseTable(const std::unordered_map<std::string, ExpressionTree*>& table);
    void registerSymbol
    (const std::string &id, ExpressionTree *obj,
     std::unordered_map<std::string, ExpressionTree *> &table);
};


// register...
inline void SymbolTable::registerBinaryOperator(const std::string& id, ExpressionTree *obj) {
    registerSymbol(id, obj, m_binaryOperators);
}

inline void SymbolTable::registerPrefixOperator(const std::string& id, ExpressionTree *obj) {
    registerSymbol(id, obj, m_prefixOperators);
}

inline void SymbolTable::registerPostfixOperator(const std::string& id, ExpressionTree *obj) {
    registerSymbol(id, obj, m_postfixOperators);
}

inline void SymbolTable::registerVariable(const std::string& id, ExpressionTree *obj) {
    registerSymbol(id, obj, m_variables);
}


// has...
inline bool SymbolTable::hasBinaryOperator(const std::string &token) const {
    return m_binaryOperators.find(token) != m_binaryOperators.cend();
}

inline bool SymbolTable::hasPrefixOperator(const std::string &token) const {
    return m_prefixOperators.find(token) != m_prefixOperators.cend();
}

inline bool SymbolTable::hasPostfixOperator(const std::string &token) const {
    return m_postfixOperators.find(token) != m_postfixOperators.cend();
}

inline bool SymbolTable::hasVariable(const std::string &token) const {
    return m_variables.find(token) != m_variables.cend();
}


#endif // OPERATORTABLE_H
