#include <iostream>
#include <string>
#include "Calculator.h"

int main() {
    Calculator* calc = new Calculator;
    std::string expression;  // To get input from cmd

    std::cout << ">> This is yCalculator\n"
              << ">> Plese enter expressions to be evaluated\n"
              << ">> or enter 'Q' to quit.\n>> \n";

    while (true) {
        std::cout << ">> ";     // Output prompt

        std::getline(std::cin, expression);     // Get input from cmd
        if (expression == "Q" || expression == "q")
            break;
        if (expression.empty())
            continue;

        calc->reset();
        try {
            calc->setInfix(expression);
            calc->setPostfix();
            calc->evaluate();
        } catch (std::logic_error err) {
            std::cout << ">> " << err.what() << std::endl;
            continue;
        } catch (std::exception err) {
            std::cout << ">> " << err.what() << std::endl;
            continue;
        }

        // std::cout << ">> ans = " << calc->getResult() << "\n>> \n";
        std::cout << ">>   " << std::string(40, '_')
                  << "\n>>\n>>   " << calc->getInfix() << "\n>>\n>>   = " << calc->getResult()
                  << "\n>>   " << std::string(40, '_') << "\n>>\n";
    }

    return 0;
}
