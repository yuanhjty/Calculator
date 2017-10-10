#ifndef COMMAND_INTERPRETER
#define COMMAND_INTERPRETER

#include "Calculator.h"
#include "ScientificCalculator.h"

#include <memory>
#include <string>
#include <map>
#include <exception>


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

    // To return exception state.
    C_EXCEPTION,

    // Other commands
    C_HELP, C_QUIT, C_CONTINUE, C_COMPLETE, C_UNDEFINED,
    C_HISTORY, C_RESET
};


// The class CalculatorManager
class CommandInterpreter {
private:
    std::unique_ptr<Calculator> m_calculator;
    std::string m_input;
    std::pair<std::string,std::string> m_result;
    static std::map<std::string, COMMAND> commands;

public:     // public interface
    CommandInterpreter();
    COMMAND interpret(const std::string &input);
    std::pair<std::string, std::string> getResult() const;

private:
    void setInput(const std::string &input);
    void setResult(const std::pair<std::string, std::string> &result);
    std::string parseCommand() const;
    std::string parseArgument() const;
    int parseHistoryIndex() const;
    void evaluate();
    void reset();
    void switchCalculator(std::unique_ptr<Calculator>& calculator);
    COMMAND executeCommand(const std::string &command);
};


// getResult
inline std::pair<std::string, std::string> CommandInterpreter::getResult() const {
    return m_result;
}

// setResult
inline void CommandInterpreter::setResult(const std::pair<std::string, std::string>& result) {
    m_result = result;
}


#endif  // COMMAND_INTERPRETER
