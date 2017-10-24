#ifndef TREE_PARSER_H
#define TREE_PARSER_H

#include "Parser.h"
#include "SymbolTable.h"
#include "Operand.h"
#include "NumeralFormat.h"

#include <stack>
#include <vector>
#include <cassert>


class TreeParser : public Parser {
public:
    TreeParser();
    ~TreeParser();
    void setSymbolTable(SymbolTable *symbolTable);

    void parse(const std::string &infixExpr) override;
    ValueType evalueate() override;

private:
    void buildPostfixExpr(const std::string &infixExpr);
    void buildExprTree();
    void destroyExprTree();
    void destroyPostfixExpr();

private:
    SymbolTable *_symbolTable;
    std::vector<ExprNode *> _postfixExpr;
    ExprNode *_exprTree;
};


inline void TreeParser::setSymbolTable(SymbolTable *symbolTable) {
    _symbolTable = symbolTable;
}

inline Parser::ValueType TreeParser::evalueate() {
    return _value = nullptr == _exprTree ? 0 : _exprTree->evaluate();
}


#endif // TREE_PARSER_H
