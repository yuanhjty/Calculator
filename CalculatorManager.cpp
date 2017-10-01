#include "CalculatorManager.h"


// commands
std::map<std::string, COMMAND> CalculatorManager::commands = {
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
    {"continue", C_CONTINUE}
};

// constructor
CalculatorManager::CalculatorManager() :
    m_calculator(new ScientificCalculator),
    m_input(new std::string) {
    m_result.first = std::make_shared<std::string>();
    m_result.second = std::make_shared<std::string>();
}

// performTask
int CalculatorManager::performTask() {
    return executeCommand(parseCommand());
}

// parseCommand
std::string CalculatorManager::parseCommand() {
    auto firstNotBlankPos = m_input->find_first_not_of(" \t");

    if (std::string::npos == firstNotBlankPos)
        return std::string("continue");

    return m_input->substr(firstNotBlankPos, m_input->find_first_of(" \t"));
}

// executeCommand
int CalculatorManager::executeCommand(const std::string &command) {
    int ret = commands.find(command)->second;

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
        updateHistory();
        break;

    case C_RESET:
        resetCalculator();
        break;

    case C_HELP:
        // print help messages
        break;

    case C_CONTINUE:
    case C_QUIT:
        break;

    default:
        std::cerr << "Undefined Command" << std::endl;
        ret = C_CONTINUE;
        break;
    }
    return ret;
}

// evaluate
void CalculatorManager::evaluate() {
    m_calculator->scanInput(m_input);
    m_calculator->evaluate();
    setResult(m_calculator->getResult());
}
