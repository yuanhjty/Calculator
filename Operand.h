#ifndef OPERAND_H
#define OPERAND_H


#include "ExpressionTree.h"


class Number : public ExpressionTree {
protected:
    double m_value = 0;
public:
    void build(double value);
    double evaluate() override;
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
    ExpressionTree* clone() override;
};

#endif // OPERAND_H
