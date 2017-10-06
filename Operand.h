#ifndef OPERAND_H
#define OPERAND_H


#include "Expression.h"


class Number : public ExpressionTree {
protected:
    double m_value = 0;
public:
    void build(double value);
    double evaluate() override;
    ExpressionTree* clone() override;
};

#endif // OPERAND_H
