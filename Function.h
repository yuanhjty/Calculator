#ifndef FUNCTION_H
#define FUNCTION_H


#include "ExpressionTree.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"

#include <vector>


// For function with one parameter
// The class OneParameterFunction
class OneParameterFunction : public ExpressionTree {
protected:
    std::vector<ExpressionTree *> m_parameter;
    static const int m_numberOfParameter;

public:
    OneParameterFunction(ExpressionTree* parameter);
};


// The class Factorial
class Factorial : public OneParameterFunction {
public:
    Factorial(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Lg (logarithm based on 10)
class Lg : public OneParameterFunction {
    Lg(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Ln (logarithm based on e)
class Ln : public OneParameterFunction {
    Ln(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Sin
class Sin : public OneParameterFunction {
    Sin(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Cos
class Cos : public OneParameterFunction {
    Cos(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Tan
class Tan : public OneParameterFunction {
    Tan(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ASin
class ASin : public OneParameterFunction {
    ASin(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ACos
class ACos : public OneParameterFunction {
    ACos(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ATan
class ATan : public OneParameterFunction {
    ATan(ExpressionTree* parameter);
    double evaluate() override;
};


// For function with two parameters
// The class TwoParameterFunction
class TwoParameterFunction : public ExpressionTree {
protected:
    std::vector<ExpressionTree *> m_parameter;
    static const int m_numberOfParameter;

public:
    TwoParameterFunction(ExpressionTree* parameter1, ExpressionTree* parameter2);
};


// The class Power
class Power : public TwoParameterFunction {
public:
    Power(ExpressionTree* parameter1, ExpressionTree* parameter2);
    double evaluate() override;
};


#endif // FUNCTION_H
