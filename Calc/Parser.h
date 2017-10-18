#ifndef PARSER_H
#define PARSER_H

#include "SymbolTable.h"
#include "ExprNode.h"
#include "Operand.h"

#include <string>
#include <stack>
#include <vector>
#include <cassert>


class Parser {
public:
    typedef double ValueType;

public:
    virtual ~Parser() = default;
    virtual void parse(const std::string &formattedExpression) = 0;
    virtual ValueType evalueate() = 0;
};


// The class TreeParser
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
    assert(_exprTree != nullptr);
    return _exprTree->evaluate();
}


#endif // PARSER_H
