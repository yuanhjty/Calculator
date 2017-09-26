#include "Manager.h"


void Manager::process(const std::string &input)
{
    std::string command = input.substr(
                0, input.find_first_of(" \t", input.find_first_not_of(" \t")));

    auto it = commands.find(command);  // CommandExpression is not in commands.
    if (it == commands.end()) {     // If true, the input will be treated as an expression.
        // Create expression command and let the assistant execute the command.
        std::shared_ptr<CommandExpression>
                commandExpression(new CommandExpression);
        commandExpression->setCalculator(currentCalculator);
        commandExpression->setInfixExpressoin(line);

        setCommand(commandExpression);
        executeCommand();
    } else {                        // The input is one of the non-expression commands.
        switch (it->second) {
        case C_EVALUATE:
            std::shared_ptr<CommandEvaluate> commandEvaluate(new CommandEvaluate);
            commandEvaluate->setCalculator(currentCalculator);

            setCommand(commandEvaluate);
            executeCommand();

            break;
        case C_CONVERT_NUMBER_BASE:
            std::shared_ptr<CommandConvertNumberBase>
                    commandConvertNumberBase(new CommandConvertNumberBase);
            commandConvertNumberBase->setCalculator(currentCalculator);
            commandConvertNumberBase->setNumberBase(10);

            setCommand(commandConvertNumberBase);
            executeCommand();
            break;
        case C_SWITCH_CALCULATOR_TYPE:
            std::shared_ptr<CommandSwitchCalculatorType>
                    commandSwitchCalculatorType(new CommandSwitchCalculatorType);
            commandSwitchCalculatorType->setCalculator(currentCalculator);

            setCommand(commandSwitchCalculatorType);
            executeCommand();
            break;
        default:
            std::cerr << "Undefined input" << std::endl;
            break;
        }
    }
}
