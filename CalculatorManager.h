#ifndef MANAGER_H
#define MANAGER_H


#include "Calculator.h"
#include "ScientificCalculator.h"
#include "Util.h"

#include <memory>
#include <string>
#include <map>


// Define enum COMMAND
enum COMMAND
{
    // To convert number base in programmer calculator.
    C_BINARY, C_OCTAL, C_DECIMAL, C_HEX,

    // To switch claculator type.
    C_WEIGHT, C_LENGTH, C_VOLUME, C_AREA,
    C_VELOCITY, C_TIME, C_TEMPERATURE,
    C_SCIENCE ,

    // To evaluate expression.
    C_EVALUATE,

    // To print help messages.
    C_HELP,

    // Other commands
//    C_FINISH, C_RESET, C_CLEAR,
    C_RESET,
};


// Define class CalculatorManager
class CalculatorManager {
private:
    std::shared_ptr<Calculator> m_calculator;
    std::shared_ptr<std::string> m_input;

private:
    static std::map<std::string, COMMAND> commands;

public:
    CalculatorManager();
    void processInput(const std::string& input);
    std::string showResult() const;
    std::string showHistory(int index) const;   // index expected: -1, -2, -3, ...

private:
    void updateInput(const std::string& input);
    std::string parseCommand();
    void executeCommand(const std::string& command);
    void evaluate();
    void resetCalculator();
    void switchCalculator(const std::shared_ptr<Calculator>& calculator);
};


// updateInput
inline void CalculatorManager::updateInput(const std::string& input) {
    *m_input = Util::trimEndsSpaces(input);
}

inline std::string CalculatorManager::showResult() const {
    return m_calculator->showResult();
}

inline std::string CalculatorManager::showHistory(int index) const {
    m_calculator->showHistory(index);
}

// resetCalculator
inline void CalculatorManager::resetCalculator() {
    m_calculator->reset();
}

// switchCalculator
inline void CalculatorManager::switchCalculator(const std::shared_ptr<Calculator>& calculator) {
    m_calculator = calculator;
}


#endif  //MANAGER_H
