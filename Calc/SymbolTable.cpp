#include "SymbolTable.h"


SymbolTable::~SymbolTable() {
    for (auto& symbol : _symbolTable) {
        delete symbol.second;
        symbol.second = nullptr;
    }
}

void SymbolTable::registerSymbol(const std::string &id, ExprNode *obj) {
    auto it = _symbolTable.find(id);
    if (it != _symbolTable.cend()) {
        delete it->second;  // destroy earlier object associated with id
        it->second = obj;   // build new association for id
    } else
        _symbolTable[id] = obj;    // create new (id, obj) pair
}

const ExprNode *SymbolTable::exprNode(const std::string &token) const {
    const auto it = _symbolTable.find(token);
    if (_symbolTable.cend() == it)
        return nullptr;
    return it->second;
}
