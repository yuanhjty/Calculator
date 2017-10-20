#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Calculator.h"
#include "ExprCalculator.h"
#include "Converter.h"

#include <string>
#include <unordered_map>
#include <type_traits>
#include <functional>


enum COMMAND {
    // Switch calculator type
    // calculator
    CMD_SCIENCE, CMD_PROGRAMMER,
    // converter
    CMD_LENGTH, CMD_AREA, CMD_VOLUME, CMD_QUALITY, CMD_TIME, CMD_VELOCITY,
    CMD_POWER, CMD_ENERGY, CMD_PRESSURE, CMD_DATA, CMD_ANGLE,

    // Switch data format
    // For science calculator
    CMD_DEGREE, CMD_RADIAN, CMD_DEFAULT, CMD_FIXED, CMD_SCIENTIFIC,
    // For programmer calculator
    CMD_BINARY, CMD_OCTAL, CMD_DECIMAL, CMD_HEX,

    // evaluate expression
    CMD_EVALUATE,

    // clear history
    CMD_CLEAR,

    // Others
    CMD_COMPLETE, CMD_CONTINUE, CMD_QUIT,
};

enum CALCULATOR {
    CAL_SCIENCE, CAL_PROGRAMMER,
    CAL_LENGTH, CAL_AREA, CAL_VOLUME, CAL_QUALITY, CAL_TIME, CAL_VELOCITY,
    CAL_POWER, CAL_ENERGY, CAL_PRESSURE, CAL_DATA, CAL_ANGLE,
};

struct CalcHash {
    size_t operator()(CALCULATOR cal) const {
        return std::hash<std::underlying_type<CALCULATOR>::type>()(cal);
    }
};


class Interpreter {
public:
    typedef Calculator::ResultType ResultType;

public:
    Interpreter();
    ~Interpreter();
    COMMAND interpret(const std::string &input);
    ResultType result() const;
    const std::deque<ResultType> *history() const;
    ErrorFlags errorState() const;

private:
    void setInput(const std::string &input);
    std::string parseCommand() const;
    COMMAND execute(const std::string &command);
    void switchCalculator(CALCULATOR id);

private:
    Calculator *_calculator;
    std::string _input;
    CALCULATOR _calculatorID;
    std::unordered_map<CALCULATOR, Calculator *, CalcHash> _calculatorPool;
    static std::unordered_map<std::string, COMMAND> _commands;
};

inline Calculator::ResultType Interpreter::result() const {
    return _calculator->currentResult();
}

inline const std::deque<Interpreter::ResultType> *Interpreter::history() const {
    return _calculator->history();
}

inline ErrorFlags Interpreter::errorState() const {
    return _calculator->errorState();
}


#endif // INTERPRETER_H
