#ifndef COMMAND_INTERPRETER
#define COMMAND_INTERPRETER

#include "Calculator.h"
#include "ScientificCalculator.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <exception>


// The enum COMMAND
enum COMMAND {
    C_UNDEFINED,

    // To convert number base in programmer calculator.
    C_BINARY, C_OCTAL, C_DECIMAL, C_HEX,

    // To switch claculator type.
    C_WEIGHT, C_LENGTH, C_VOLUME, C_AREA,
    C_VELOCITY, C_TIME, C_TEMPERATURE,
    C_SCIENCE ,

    // To evaluate expression.
    C_EVALUATE,

    // Other commands
    C_HELP, C_QUIT, C_CONTINUE, C_COMPLETE,
    C_HISTORY, C_RESET, C_CLEAR_HISTORY,


    // boundary of good state and bad state
    E_CRITICALITY,

    // bad state.
    E_OPERAND_MISSING, E_OPERATOR_MISSING, E_LBRACKET_MISSING,
    E_RBRACKET_MISSING, E_INVALID_SYMBOL, E_INVALID_ARGUMENT,
    E_DIVIDE_BY_ZERO, E_INNER_ERROR, E_NUMERIC_OVERFLOW, E_UNKNOWN,
    };


// The class CalculatorManager
class CommandInterpreter {
public:
    typedef Calculator::Result_Type Result_Type;
private:
    std::unique_ptr<Calculator> m_calculator;
    std::string m_input;
    Result_Type m_result;
    COMMAND lastCalcState = C_UNDEFINED;

    static std::unordered_map<std::string, COMMAND> commands;

public:     // public interface
    CommandInterpreter();
    COMMAND interpret(const std::string &input);
    Result_Type getResult() const;
    std::deque<Result_Type>* getHistory() const;

private:
    void setInput(const std::string& input);
    void setResult(const Result_Type& result);
    std::string parseCommand() const;
    std::string parseArgument() const;
    int parseHistoryIndex() const;
    void evaluate();
    void reset();
    void switchCalculator(std::unique_ptr<Calculator>& calculator);
    COMMAND executeCommand(const std::string &command);
};


// getResult
inline Calculator::Result_Type CommandInterpreter::getResult() const {
    return m_result;
}

inline std::deque<Calculator::Result_Type>* CommandInterpreter::getHistory() const {
    return m_calculator->getHistory();
}

// setResult
inline void CommandInterpreter::setResult(const Calculator::Result_Type& result) {
    m_result = result;
}


#endif  // COMMAND_INTERPRETER
