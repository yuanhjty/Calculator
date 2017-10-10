#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H


#include "Calculator.h"
#include "LexicalSet.h"
#include "Expression.h"
#include "SymbolTable.h"
#include "Parser.h"

#include <string>
#include <memory>


class ScientificCalculator : public Calculator {
protected:
    std::shared_ptr<SymbolTable> m_symbolTable;
    Expression *m_expression;
    Parser *m_parser;

public:
    ScientificCalculator();
    virtual ~ScientificCalculator();
    void init() override;
    void evaluate() override;

protected:
    virtual void initSymbolTable();
    virtual std::string valueToString(double value);
};

#endif // SCIENTIFICCALCULATOR_H
