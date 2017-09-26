#ifndef MANAGER_H
#define MANAGER_H

#include "Calculator.h"
#include "Util.h"

#include <memory>
#include <string>
#include <map>


enum COMMAND
{
    C_BINARY  , C_OCTAL , C_DECIMAL    , C_HEX ,     // number system
    C_WEIGHT  , C_LENGTH, C_VOLUME     , C_AREA,     // unit conversion calculator
    C_VELOCITY, C_TIME  , C_TEMPERATURE,             // unit conversion calculator
    C_SCIENCE,                                       // scientific calculator
    C_EVALUATE                                       // evaluate command
};

class Manager
{
private:
    std::shared_ptr<Calculator> m_calculator;
    std::string m_input;
    static std::map<std::string, COMMAND> commands;

public:
    void setCalculator(const std::shared_ptr<Calculator>& calculator);
    void process(const std::string& input);

private:
    void setInput(const std::string& input);

    std::string getCommand();
    void executeCommand(const std::string& command);
    void evaluate();
};

inline void Manager::setCalculator(const std::shared_ptr<Calculator> &calculator) {
    m_calculator = calculator;
}

inline void Manager::setInput(const std::string& input) {
    m_input = trimEndsWhites(input);
}

inline std::string Manager::getCommand() {
    return m_input.substr(0, m_input.find_first_of(" \t"));
}


#endif  //MANAGER_H
