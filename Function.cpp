// The function Factorial::evaluate has't been implemented yet.

#include "Function.h"

#include <cmath>


extern std::map<std::string, FUNCTION_TYPE> functionTable = {
    {"sin", FUNCTION_1}, {"cos", FUNCTION_1}, {"tan", FUNCTION_1},
    {"asin", FUNCTION_1}, {"acos", FUNCTION_1}, {"atan", FUNCTION_1},
    {"sinh", FUNCTION_1}, {"cosh", FUNCTION_1}, {"tanh", FUNCTION_1},
    {"lg", FUNCTION_1}, {"ln", FUNCTION_1}, {"fact", FUNCTION_1},
    {"sqrt", FUNCTION_1}, {"log", FUNCTION_2}, {"pow", FUNCTION_2},
};


// For function with one parameter
// OneParameterFunction
const int Function_1::m_numberOfParameter = 1;

Function_1::Function_1(ExpressionTree *parameter) {
    m_parameter.push_back(parameter);
}


// Factorial
Factorial::Factorial(ExpressionTree *parameter):
    Function_1(parameter) {}

double Factorial::evaluate() {
    return 0;
}


// Lg
Lg::Lg(ExpressionTree *parameter) :
    Function_1(parameter) {}

double Lg::evaluate() {
    return std::sin(m_parameter[0]->evaluate());
}



// For function with two parameters
// TwoParameterFunction
const int Function_2::m_numberOfParameter = 2;

Function_2::Function_2(
        ExpressionTree *parameter1, ExpressionTree *parameter2) {
    m_parameter.push_back(parameter1);
    m_parameter.push_back(parameter2);
}


// Power
Pow::Pow(ExpressionTree *parameter1, ExpressionTree *parameter2) :
    Function_2(parameter1, parameter2) {}

double Pow::evaluate() {
    return std::pow(m_parameter[0]->evaluate(), m_parameter[1]->evaluate());
}


// Log
Log::Log(ExpressionTree *parameter1, ExpressionTree *parameter2) :
    Function_2(parameter1, parameter2) {}

double Log::evaluate() {
    return std::pow(m_parameter[0]->evaluate(), m_parameter[1]->evaluate());
}
