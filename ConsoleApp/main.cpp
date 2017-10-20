#include <iostream>
#include "../Calc/Interpreter.h"


void printHistory(const std::deque<Calculator::ResultType> *history);
void printResult(const Calculator::ResultType& result, const ErrorFlags &errorFlags);

int main() {
    Interpreter *interpreter = new Interpreter;
    std::string input;

    std::cout << "Calculator\n"
                 "Enter expression to evaluate\n"
                 "'help' for help\n"
                 "'quit' to quit\n\n";

    while (true) {
        std::cout << ">> ";

        std::getline(std::cin, input);
        if (!std::cin.good()) {
            std::cout << "Sorry! It seems something wrong, please try again!" << std::endl;
            std::cin.clear();
            continue;
        }

        if ("history" == input) {
            auto history = interpreter->history();
            printHistory(history);
            continue;
        }

        COMMAND cmd = interpreter->interpret(input);

        if (CMD_CONTINUE == cmd)
            continue;

        if (CMD_QUIT == cmd)
            break;

        if (CMD_EVALUATE == cmd)
            interpreter->interpret("complete");

        printResult(interpreter->result(), interpreter->errorState());
    }

    delete interpreter;
    return 0;
}

void printHistory(const std::deque<Calculator::ResultType> *history) {
    for (auto result : *history)
        printResult(result, ERROR_NOERROR);
}

void printResult(const Calculator::ResultType& result, const ErrorFlags &errorFlags) {
    std::string resultIndicator = ((errorFlags & ERROR_FIELD) == ERROR_NOERROR
                                   && !result.first.empty()) ? "= " : "";
    std::cout << "   " << std::string(40, '_') << "\n\n"
              << "   " << result.first << "\n\n"
              << "   " << resultIndicator << result.second << "\n"
              << "   " << std::string(40, '_') << "\n\n";
}
