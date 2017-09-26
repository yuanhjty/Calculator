#include "Manager.h"
#include "Calculator.h"
#include "Util.h"

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>


int main(int argc, char *argv[])
{
    // Create a scientific calculator by default and initialize it.
    std::shared_ptr<Calculator> calculator(new ScientificCalculator);
    calculator->init();

    // Create the manager.
    std::shared_ptr<Manager> manager(new Manager);
    manager->setCalculator(calculator);

    // Print welcom and help
    printWelcom();

    // main loop
    while (true) {
        std::cout << ">> ";             // Output prompt.

        std::string line;
        std::getline(std::cin, line);   // Get input(could be a command or infix expression).

        if (!std::cin.good()) {
            std::cout << "Sorry! It seems something wrong, please try again!" << std::endl;
            continue;
        }

        line = trimEndsWhites(line);
        if (line.empty())
            continue;
        if (line == "q" || line == "Q")
            break;

        manager->process(line);

        printResult(calculator->getMessage(), calculator->getResult());
    }

    return 0;
}
