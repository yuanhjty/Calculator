#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H


#include "Calculator.h"
#include "LexicalSet.h"
#include "Expression.h"
#include "OperatorTable.h"
#include "Parser.h"

#include <memory>
#include <string>


class ScientificCalculator : public Calculator {
protected:
    std::unique_ptr<Expression> m_expression;
    std::unique_ptr<Parser> m_parser;
    OperatorTable *m_operatorTable;

public:
    ScientificCalculator();
    virtual ~ScientificCalculator();
    void evaluate() override;

protected:
    virtual std::string valueToString(double value);
    virtual void setOperators();
};

#endif // SCIENTIFICCALCULATOR_H
