#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H


#include "Calculator.h"
#include "Expression.h"
#include "Parser.h"
#include "Util.h"

#include <memory>
#include <string>
#include <map>


class ScientificCalculator : public Calculator {
protected:
    std::unique_ptr<Expression> m_expression;
    std::unique_ptr<Parser> m_parser;

public:
    ScientificCalculator();
    void evaluate() override;

protected:
    virtual std::string valueToString(double value);
};

#endif // SCIENTIFICCALCULATOR_H
