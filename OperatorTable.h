#ifndef OPERATORTABLE_H
#define OPERATORTABLE_H


#include "ExpressionTree.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"

#include <string>
#include <map>
#include <set>
#include <mutex>


class OperatorTable {
private:
    std::map<std::string, ExpressionTree*> m_operators;
    std::set<std::string> m_binaryOperators;
    std::set<std::string> m_prefixOperators;
    std::set<std::string> m_postfixOperators;

    static OperatorTable* m_operatorTable;
    static std::mutex m;

public:
    static OperatorTable* getInstance();
    ~OperatorTable();

    ExpressionTree* getOperator(const std::string& token);
    bool isBinaryOperator(const std::string& token) const;
    bool isPrefixOperator(const std::string& token) const;
    bool isPostfixOperator(const std::string& token) const;


private:
    OperatorTable();

    void registerOperator(const std::string& name, ExpressionTree* op);
    void initOperators();
    void releaseOperators();

    void initBinaryOperators();
    void initPrefixOperators();
    void initPostfixOperators();
};

inline bool OperatorTable::isBinaryOperator(const std::string &token) const {
    return m_binaryOperators.find(token) != m_binaryOperators.cend();
}

inline bool OperatorTable::isPrefixOperator(const std::string &token) const {
    return m_prefixOperators.find(token) != m_prefixOperators.cend();
}

inline bool OperatorTable::isPostfixOperator(const std::string &token) const {
    return m_postfixOperators.find(token) != m_postfixOperators.cend();
}

inline void OperatorTable::registerOperator(const std::string &name, ExpressionTree *op) {
    m_operators.insert(std::make_pair(name, op));
}

#endif // OPERATORTABLE_H
