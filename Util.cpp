#include "Util.h"


std::string trimEndsWhites(const std::string &str) {
    auto pos = str.find_first_not_of(" \t");
    auto n = str.find_last_not_of(" \t") - pos + 1;
    return str.substr(pos, n);
}

void printResult(const std::string &message, const std::string &result) {
    std::cout << ">>   " << std::string(40, '_')
              << "\n>>\n>>   " << message << "\n>>\n>>   = " << result
              << "\n>>   " << std::string(40, '_') << "\n>>\n";
}

void printWelcom() {
    std::cout << "toy-calculator 0.1\n"
              << "Type expressions to be evaluated\n"
              << "Type 'q' to quit.\n\n";
}
