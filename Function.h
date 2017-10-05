#ifndef FUNCTION_H
#define FUNCTION_H


#include "Expression.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"

#include <string>
#include <vector>
#include <map>


// The enum FUNCTION_TYPE
enum FUNCTION_TYPE {
    FUNCTION_1, FUNCTION_2, FUNCTION_3, FUNCTION_4, FUNCTION_5
};


// The map functionTable
extern std::map<std::string, FUNCTION_TYPE> functionTable;


// The class Function
class Function : public ExpressionTree {
public:
    PRIORITY getPriority() const override {
        return P_CALL;
    }
};

// For function with one parameter
// The class OneParameterFunction
class Function_1 : public ExpressionTree {
protected:
    std::vector<ExpressionTree *> m_parameter;
    static const int m_numberOfParameter;

public:
    Function_1(ExpressionTree* parameter);
};


// The class Factorial
class Factorial : public Function_1 {
public:
    Factorial(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Lg (logarithm based on 10)
class Lg : public Function_1 {
    Lg(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Ln (logarithm based on e)
class Ln : public Function_1 {
    Ln(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Sin
class Sin : public Function_1 {
    Sin(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Cos
class Cos : public Function_1 {
    Cos(ExpressionTree* parameter);
    double evaluate() override;
};


// The class Tan
class Tan : public Function_1 {
    Tan(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ASin
class ASin : public Function_1 {
    ASin(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ACos
class ACos : public Function_1 {
    ACos(ExpressionTree* parameter);
    double evaluate() override;
};


// The class ATan
class ATan : public Function_1 {
    ATan(ExpressionTree* parameter);
    double evaluate() override;
};


// For function with two parameters
// The class TwoParameterFunction
class Function_2 : public ExpressionTree {
protected:
    std::vector<ExpressionTree *> m_parameter;
    static const int m_numberOfParameter;

public:
    Function_2(ExpressionTree* parameter1, ExpressionTree* parameter2);
};


// The class Power
class Pow : public Function_2 {
public:
    Pow(ExpressionTree* parameter1, ExpressionTree* parameter2);
    double evaluate() override;
};


// The class log
class Log : public Function_2 {
    Log(ExpressionTree *parameter1, ExpressionTree *parameter2);
    double evaluate() override;
};

#endif // FUNCTION_H
