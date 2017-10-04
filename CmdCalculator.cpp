#include "CommandInterpreter.h"

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>


int main() {
    std::unique_ptr<CommandInterpreter> interpreter(new CommandInterpreter);
    std::string input;
    std::pair<std::string, std::string> result;
    COMMAND command = C_UNDEFINED;

    // print welcome
    std::cout << "toy-calculator 0.1\n"
              << "Type expressions to be evaluated\n"
              << "Type 'q' to quit.\n\n";

    // main loop
    while (true) {
        std::cout << ">> ";     // Print prompt chars.

        std::getline(std::cin, input);   // Get input(could be a command or infix expression).

        if (!std::cin.good()) {
            std::cout << "Sorry! It seems something wrong, please try again!" << std::endl;
            std::cin.clear();
            continue;
        }

        command = interpreter->interpreter(input);

        if (C_CONTINUE == command)
            continue;

        if (C_QUIT == command)
            break;

        result = interpreter->getResult();
        std::cout << "   " << std::string(40, '_')
                  << "\n   " << result.first << "\n   =" << result.second
                  << "\n   " << std::string(40, '_') << "\n\n";
    }

    return 0;
}
