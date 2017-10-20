#ifndef EXPR_CALCULATOR_H
#define EXPR_CALCULATOR_H

#include "Calculator.h"
#include "SymbolTable.h"
#include "TreeParser.h"
#include "NumeralFormat.h"


class ExprCalculator : public Calculator {
public:
    ExprCalculator(std::string (*toString)(double));
    ~ExprCalculator();

protected:
    SymbolTable *_symbolTable;
};


class ScienceCalculator : public ExprCalculator {
public:
    ScienceCalculator();
    void setNumeralFormat(NumeralFormat format) override;

private:
    void initSymbolTable();
};


class ProgrammerCalculator : public ExprCalculator {
public:
    ProgrammerCalculator();
    void setNumeralFormat(NumeralFormat format) override;

private:
    void initSymbolTable();
};


#endif // EXPR_CALCULATOR_H
