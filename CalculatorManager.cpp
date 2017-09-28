#include "CalculatorManager.h"


//
// Implenent static data members.
//
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

    // To print help messages.
    {"help", C_HELP},

    // Other commands
    {"finish",C_FINISH}, {"reset", C_RESET}, {"clear", C_CLEAR},
};


//
// Implement public methods.
//
// constructor
CalculatorManager::CalculatorManager() :
    m_calculator(new ScientificCalculator),
    m_input(new std::string) {}

// processInput
void CalculatorManager::processInput(const std::string& input) {
    updateInput(input);
    executeCommand(parseCommand());
}

// getResult
std::string CalculatorManager::getResult() const {
    return *(m_calculator->getResult());
}

std::string CalculatorManager::getExpression() const {
    return *(m_calculator->getValidExpression());
}


//
// Implement private methods
//
// parseCommand
std::string CalculatorManager::parseCommand() {
    return m_input->substr(0, m_input->find_first_of(" \t"));
}

// executeCommand
void CalculatorManager::executeCommand(const std::string &command) {
    if (command.empty())
        return;

    auto it = commands.find(command);
    if (it == commands.end()) { // If true, the input will be treated as an expression.
        evaluate();
    } else {
        switch (it->second) {
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
        case C_HELP:
            Util::printHelp();
            break;
        case C_FINISH:
            finish();
            break;
        case C_RESET:
            resetCalculate();
            break;
        case C_CLEAR:
            clearCalculator();
            break;
        default:
            std::cerr << "Invalid input" << std::endl;
            break;
        }
    }
}

// evaluate
void CalculatorManager::evaluate() {
    m_calculator->scanInput(m_input);
    m_calculator->evaluate();
}


