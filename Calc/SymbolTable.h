#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ExprNode.h"

#include <unordered_map>
#include <string>


class SymbolTable {
public:
    typedef std::unordered_map<std::string, ExprNode *> TableType;

public:
    ~SymbolTable();
    void registerSymbol(const std::string& id, ExprNode *obj);
    const ExprNode* exprNode(const std::string& token) const;

private:
    TableType _symbolTable;
};

#endif // SYMBOL_TABLE_H
