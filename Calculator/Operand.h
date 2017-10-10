#ifndef OPERAND_H
#define OPERAND_H


#include "ExpressionTree.h"


class Operand : public ExpressionTree {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
    int childCount() const override;
};


class Number : public Operand {
protected:
    double m_value = 0;
public:
    Number();
    Number(double value);
    double evaluate() override;
    ExpressionTree* clone() override;
    void build(const std::vector<ExpressionTree*>& param) override;
};


class Constant : public Operand {
    void build(const std::vector<ExpressionTree*>& param) override;
};


class ConstPi : public Constant {
public:
    double evaluate() override;
    ExpressionTree* clone() override;
};


class ConstE : public Constant {
    double evaluate() override;
    ExpressionTree* clone() override;
};


#endif // OPERAND_H
