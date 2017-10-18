#ifndef SCIENCE_CALCULATOR_H
#define SCIENCE_CALCULATOR_H

#include "Calculator.h"
#include "Lexeme.h"
#include "Parser.h"
#include "ExprNode.h"
#include "RealOperator.h"
#include "Operand.h"
#include "SymbolTable.h"


class ScienceCalculator : public Calculator {
public:
    ScienceCalculator();
    ~ScienceCalculator();

private:
    void initSymbolTable();

private:
    SymbolTable *_symbolTable;
};

#endif // SCIENCE_CALCULATOR_H
