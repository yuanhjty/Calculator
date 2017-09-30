#include "CalculatorManager.h"

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>


int main() {
    std::shared_ptr<CalculatorManager> calculatorManager(new CalculatorManager);
    StringPtr input(new std::string);
    std::pair<StringPtr, StringPtr> result;
    int command = -1;

    // print welcome
    std::cout << "toy-calculator 0.1\n"
              << "Type expressions to be evaluated\n"
              << "Type 'q' to quit.\n\n";

    // main loop
    while (true) {
        std::cout << ">> ";     // Print prompt chars.

        std::getline(std::cin, *input);   // Get input(could be a command or infix expression).

        if (!std::cin.good()) {
            std::cout << "Sorry! It seems something wrong, please try again!" << std::endl;
            std::cin.clear();
            continue;
        }

        calculatorManager->setInput(input);
        command = calculatorManager->performTask();

        if (C_CONTINUE == command)
            continue;

        if (C_QUIT == command)
            break;

        result = calculatorManager->showResult();
        std::cout << "   " << std::string(40, '_')
                  << "\n   " << *result.first << "\n   =" << *result.second
                  << "\n   " << std::string(40, '_') << "\n\n";
    }

    return 0;
}
