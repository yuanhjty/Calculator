#ifndef MANAGER_H
#define MANAGER_H


#include "Calculator.h"
#include "ScientificCalculator.h"
#include "Util.h"

#include <memory>
#include <string>
#include <map>


// The enum COMMAND
enum COMMAND {
    // To convert number base in programmer calculator.
    C_BINARY, C_OCTAL, C_DECIMAL, C_HEX,

    // To switch claculator type.
    C_WEIGHT, C_LENGTH, C_VOLUME, C_AREA,
    C_VELOCITY, C_TIME, C_TEMPERATURE,
    C_SCIENCE ,

    // To evaluate expression.
    C_EVALUATE,

    // To reset caldulator
    C_RESET,

    // Other commands
    C_HELP, C_QUIT, C_CONTINUE, C_COMPLETE, C_UNDIFINED
};


// The class CalculatorManager
class CalculatorManager {
private:
    std::shared_ptr<Calculator> m_calculator;
    StringPtr m_input;
    std::pair<StringPtr,StringPtr> m_result;

private:
    static std::map<std::string, COMMAND> commands;

public:
    CalculatorManager();
    void setInput(const StringPtr& input);
    int performTask();
    std::pair<StringPtr, StringPtr> showResult() const;
    std::pair<StringPtr, StringPtr> getResult() const;
    std::pair<StringPtr, StringPtr> getHistory(int index) const;    // index expected: -1, -2, -3, ...

private:
    std::string parseCommand();
    int executeCommand(const std::string& command);
    void evaluate();
    void setResult(const std::pair<StringPtr, StringPtr>& result);
    void updateHistory();
    void resetCalculator();
    void switchCalculator(const std::shared_ptr<Calculator>& calculator);
};


// setInput
inline void CalculatorManager::setInput(const StringPtr& input) {
    m_input = input;
}

// showResult
inline std::pair<StringPtr, StringPtr> CalculatorManager::showResult() const {
    return m_result;
}

// getResult
inline std::pair<StringPtr, StringPtr> CalculatorManager::getResult() const {
    return m_calculator->getResult();
}

// getHistory
inline std::pair<StringPtr, StringPtr> CalculatorManager::getHistory(int index) const {
    return m_calculator->getHistory(index);
}

// setResult
inline void CalculatorManager::setResult(const std::pair<StringPtr, StringPtr>& result) {
    m_result = result;
}

// updateHistory
inline void CalculatorManager::updateHistory() {
    m_calculator->updateHistory();
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
