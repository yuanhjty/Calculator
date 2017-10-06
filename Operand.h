#ifndef OPERAND_H
#define OPERAND_H


#include "ExpressionTree.h"


class Number : public ExpressionTree {
protected:
    double m_value = 0;
public:
    Number(double value);
    double evaluate() override;
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
    ExpressionTree* clone() override;
    int childCount() const override;
    void build(const std::vector<ExpressionTree*>& param) override;
};

#endif // OPERAND_H
