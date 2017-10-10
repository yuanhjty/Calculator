#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H


#include "Expression.h"


// The class UnaryOperator
class UnaryOperator : public ExpressionTree {
protected:
    ExpressionTree *m_child = nullptr;

public:
    ~UnaryOperator();
    int childCount() const override;
    virtual void build(const std::vector<ExpressionTree*>& child);
};


// The class PrefixOperator
class PrefixOperator : public UnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};


// The class PostfixOperator
class PostfixOperator : public UnaryOperator {
public:
    PRIORITY priority() override;
    ASSOCIATIVITY associativity() override;
};



// The class BitNot
class BitNot : public PrefixOperator {
public:
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Fact
class Fact : public  PostfixOperator{
public:
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class UMinus
class UMinus : public PrefixOperator {
public:
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Lg (logarithm based on 10)
class Lg : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Ln (logarithm based on e)
class Ln : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Sin
class Sin : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Cos
class Cos : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class Tan
class Tan : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class ASin
class ASin : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class ACos
class ACos : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


// The class ATan
class ATan : public PrefixOperator {
    double evaluate() override;
    ExpressionTree* clone() override;
};


#endif // UNARY_OPERATOR_H
