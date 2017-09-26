#include "Manager.h"
#include "Command.h"
#include "Calculator.h"

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>


int main(int argc, char *argv[])
{
    // Create a scientific calculator by default and initialize it.
    std::shared_ptr<Calculator> scientificCalculator(new ScientificCalculator);
    scientificCalculator->init();

    // Use the scientific calculator as current calculator.
    std::shared_ptr<Calculator> currentCalculator = scientificCalculator;

    // Create the commander.
    std::shared_ptr<Manager> manager(new Manager);


    // main loop
    while (true) {
        std::cout << ">> ";             // Output prompt.

        std::string line;
        std::getline(std::cin, line);   // Get input(could be a command or infix expression).

        if (!cin.good()) {
            std::cout << "Sorry! It seems something wrong, please try again!" << std::endl;
            continue;
        }
        if (line.empty())
            continue;
        if (line == "q" || line == "Q")
            break;

        // core logic
        auto it = commands.find(line);  // CommandExpression is not in commands.
        if (it == commands.end()) {     // If true, the input will be treated as an expression.
            // Create expression command and let the assistant execute the command.
            std::shared_ptr<CommandExpression>
                    commandExpression(new CommandExpression);
            commandExpression->setCalculator(currentCalculator);
            commandExpression->setInfixExpressoin(line);

            manager->setCommand(commandExpression);
            manager->executeCommand();

            // Show result.
            std::cout << ">> result = " << currentCalculator->getResult() << std::endl;
        } else {                        // The input is one of the non-expression commands.
            switch (it->second) {
            case C_CONVERT_NUMBER_BASE:
                std::shared_ptr<CommandConvertNumberBase>
                        commandConvertNumberBase(new CommandConvertNumberBase);
                commandConvertNumberBase->setCalculator(currentCalculator);
                commandConvertNumberBase->setNumberBase(10);

                manager->setCommand(commandConvertNumberBase);
                manager->executeCommand();
                break;
            case C_SWITCH_CALCULATOR_TYPE:
                std::shared_ptr<CommandSwitchCalculatorType>
                        commandSwitchCalculatorType(new CommandSwitchCalculatorType);
                commandSwitchCalculatorType->setCalculator(currentCalculator);
                break;
            case C_EVALUATE:
                std::shared_ptr<CommandEvaluate> commandEvaluate(new CommandEvaluate);
                commandEvaluate->setCalculator(currentCalculator);

                manager->setCommand(commandEvaluate);
                manager->executeCommand();

                // Show result.
                std::cout << ">> result = " << currentCalculator->getResult() << std::endl;
                break;
            default:
                std::cerr << "Undefined input" << std::endl;
                break;
            }
        }

    return 0;
}
