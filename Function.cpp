// The function Factorial::evaluate has't been implemented yet.

#include "Function.h"

#include <cmath>


// For function with one parameter
// OneParameterFunction
const int OneParameterFunction::m_numberOfParameter = 1;

OneParameterFunction::OneParameterFunction(ExpressionTree *parameter) {
    m_parameter.push_back(parameter);
}


// Factorial
Factorial::Factorial(ExpressionTree *parameter):
    OneParameterFunction(parameter) {}

double Factorial::evaluate() {
    return 0;
}


// Lg
Lg::Lg(ExpressionTree *parameter) :
    OneParameterFunction(parameter) {}

double Lg::evaluate() {
    return std::sin(m_parameter[0]->evaluate());
}



// For function with two parameters
// TwoParameterFunction
const int TwoParameterFunction::m_numberOfParameter = 2;

TwoParameterFunction::TwoParameterFunction(
        ExpressionTree *parameter1, ExpressionTree *parameter2) {
    m_parameter.push_back(parameter1);
    m_parameter.push_back(parameter2);
}


// Power
Power::Power(ExpressionTree *parameter1, ExpressionTree *parameter2) :
    TwoParameterFunction(parameter1, parameter2) {}

double Power::evaluate() {
    return std::pow(m_parameter[0]->evaluate(), m_parameter[1]->evaluate());
}
