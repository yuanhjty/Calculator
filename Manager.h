#ifndef COMMANDER_H
#define COMMANDER_H

#include "Command.h"
#include "Calculator.h"

#include <memory>
#include <string>


class Manager
{
private:
    std::shared_ptr<Calculator> m_calculator;
    std::shared_ptr<Command> m_command;

public:
    void setCalculator(const std::shared_ptr<Calculator>& calculator) {
        m_calculator = calculator;
    }

    void setCommand(const std::shared_ptr<Command>& command) {
        m_command = command;
    }

    void executeCommand() {
        m_command->execute();
    }

    void process(const std::string& input);
};

