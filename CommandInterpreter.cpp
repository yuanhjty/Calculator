#include "CommandInterpreter.h"

#include <stdexcept>
#include <iostream>

// commands
std::map<std::string, COMMAND> CommandInterpreter::commands = {
    // To convert number base in programmer calculator.
    {"binary", C_BINARY}, {"octal", C_OCTAL}, {"decimal", C_DECIMAL}, {"hex", C_HEX},

    // To switch claculator type.
    {"weight", C_WEIGHT}, {"length", C_LENGTH}, {"volume", C_VOLUME}, {"area", C_AREA},
    {"velocity", C_VELOCITY}, {"time", C_TIME}, {"temperature", C_TEMPERATURE},
    {"science", C_SCIENCE},

    // To evaluate expression.
    {"evaluate", C_EVALUATE},

    // To reset calculator
    {"reset", C_RESET},

    // Other commands
    {"help", C_HELP}, {"quit", C_QUIT}, {"complete", C_COMPLETE},
    {"continue", C_CONTINUE}, {"undefined", C_UNDEFINED},
    {"viewHistory", C_VIEW_HISTORY}, {"quitHistory", C_QUIT_HISTORY}
};

// constructor
CommandInterpreter::CommandInterpreter() :
    m_calculator(new ScientificCalculator) {}

// interpreter
COMMAND CommandInterpreter::interpreter(const std::string& input) {
    setInput(input);
    try {
        return executeCommand(parseCommand());
    } catch (std::logic_error e) {
        setResult(std::make_pair(std::string(), e.what()));
    }
}

// setInput
void CommandInterpreter::setInput(const std::string &input) {
    auto firstNotBlankPos = input.find_first_not_of(" \t");
    if (std::string::npos == firstNotBlankPos) {
        m_input = std::string();
        return;
    }

    auto lastNotBlankPos = input.find_last_not_of(" \t");
    auto count = lastNotBlankPos - firstNotBlankPos + 1;

    m_input = input.substr(firstNotBlankPos, count);
}

// parseCommand
std::string CommandInterpreter::parseCommand() const {
    if (m_input.empty())
        return std::string("continue");

    auto firstBlankPos = m_input.find_first_of(" \t");
    if (std::string::npos == firstBlankPos)
        return m_input;

    return m_input.substr(0, firstBlankPos + 1);
}

// parseParameter
std::string CommandInterpreter::parseArgument() const {
    auto firstBlankPos = m_input.find_first_of(" \t");
    if (std::string::npos == firstBlankPos)
        return std::string();
    return m_input.substr(m_input.find_first_not_of(" \t", firstBlankPos));
}

// historyIndex
int CommandInterpreter::parseHistoryIndex() const {
    std::string argument = parseArgument();
    size_t idx;
    int ret = std::stoi(argument, &idx);
    if (idx != argument.size())
        throw std::logic_error("error: invalid argument: " + argument);
    return ret;
}

// evaluate
void CommandInterpreter::evaluate() {
    m_calculator->scan(m_input);
    m_calculator->evaluate();
    setResult(m_calculator->getResult());
}

// reset
void CommandInterpreter::reset() {
    m_result.first.clear();
    m_result.second.clear();
    m_calculator->reset();
}

// switchCalculator
void CommandInterpreter::switchCalculator(std::unique_ptr<Calculator> &calculator) {
    m_calculator.reset(calculator.release());
}

// executeCommand
COMMAND CommandInterpreter::executeCommand(const std::string &command) {
    const auto it = commands.find(command);
    COMMAND ret = (it != commands.cend()) ? it->second : C_EVALUATE;

    switch (ret) {
    case C_BINARY:
    case C_OCTAL:
    case C_DECIMAL:
    case C_WEIGHT:
    case C_LENGTH:
    case C_VOLUME:
    case C_AREA:
    case C_VELOCITY:
    case C_TIME:
    case C_TEMPERATURE:
    case C_SCIENCE:

    case C_EVALUATE:
        evaluate();
        break;

    case C_COMPLETE:
        m_calculator->updateHistory();
        break;

    case C_VIEW_HISTORY:
        setResult(m_calculator->getHistory(parseHistoryIndex()));
        break;

    case C_QUIT_HISTORY:
        setResult(m_calculator->getResult());
        break;

    case C_RESET:
        reset();
        break;

    case C_HELP:
        // print help messages
        ret = C_CONTINUE;
        break;

    case C_CONTINUE:
        break;

    case C_QUIT:
        break;

    case C_UNDEFINED:
    default:
        setResult(std::make_pair(std::string(), "Undefined Command"));
        ret = C_CONTINUE;
        break;
    }
    return ret;
}
