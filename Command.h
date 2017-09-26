#ifndef COMMAND_H
#define COMMAND_H

#include "Calculator.h"

#include <memory>
#include <string>
#include <map>


///
/// \brief The Command class
///
class Command
{
protected:
    std::shared_ptr<Calculator> m_calculator;

public:
    virtual ~Command() = default;

    virtual void setCalculator(const std::shared_ptr<Calculator>& calculator) = 0;
    virtual void execute() = 0;
};


///
/// \brief The CommandEvaluate class
///
class CommandExpression : public Command
{
private:
    std::string m_infixExpression;
public:
    void setCalculator(const std::shared_ptr<Calculator>& calculator) override {
        m_calculator = calculator;
    }

    void setInfixExpressoin(const std::string& infixExpression) {
        m_infixExpression = infixExpression;
    }

    void execute() override {
        m_calculator->scanInput(m_infixExpression);
        m_calculator->evaluate();
    }
};


class CommandEvaluate : public Command
{
public:
    void execute() override {
        m_calculator->evaluate();
    }
};


///
/// \brief The CommandConvertNumberBase class
///
class CommandConvertNumberBase : public Command
{
private:
    int m_numberBase = 10;

public:
    void setNumberBase(int base) {
        if (base < 1)
            base = 10;
        m_numberBase = base;
    }
};


///
/// \brief The CommandSwitchCalculatorType class
///
class CommandSwitchCalculatorType : public Command
{
public:
    CommandSwitchCalculatorType();
};


///
/// \brief The COMMAND enum
///
enum COMMAND
{
    C_EVALUATE,
    C_EXPRESSION,
    C_CONVERT_NUMBER_BASE,
    C_SWITCH_CALCULATOR_TYPE
};


std::map<std::string, COMMAND> commands =   // C_EXPRESSION not included
{
    {"eval"    , C_EVALUATE              },
    {"numbase" , C_CONVERT_NUMBER_BASE   },
    {"calctype", C_SWITCH_CALCULATOR_TYPE}
};

#endif // COMMAND_H
