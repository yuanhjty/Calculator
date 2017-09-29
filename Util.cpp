#include "Util.h"


//
// Implement public methods
//
// trimEndsSpaces
std::string Util::trimEndsSpaces(const std::string &str) {
    auto first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return str.substr(0, 0);

    auto last = str.find_last_not_of(" \t");
    auto n = last == std::string::npos ? str.size() - first : last - first + 1;

    return str.substr(first, n);
}

// printResult
//void Util::printResult(const std::string& expression, const std::string& result) {
//    std::cout << ">>   " << std::string(40, '_')
//              << "\n>>\n>>   " << expression << "\n>>\n>>   = " << result
//              << "\n>>   " << std::string(40, '_') << "\n>>\n";
//}

// printWelcome
//void Util::printWelcome() {
//    std::cout << "toy-calculator 0.1\n"
//              << "Type expressions to be evaluated\n"
//              << "Type 'q' to quit.\n\n";
//}

// printHelp
//void Util::printHelp() {
//    // print help messages
//}

// toString
std::string Util::toString(double value) {
    return std::to_string(value);
}


// static members of class LexemePattern
const std::string LexemePattern::numReal = "\\d+(\\.\\d*)?(e\\d+)?";
const std::string LexemePattern::numBinary = "[01]+";
const std::string LexemePattern::numOctal = "[0-7]+";
const std::string LexemePattern::numDecimal = "\\d+";
const std::string LexemePattern::numHex = "[[:xdigit:]]+";
const std::string LexemePattern::opCommon = "[\\+\\-\\*/]";
const std::string LexemePattern::opBitwise = "[\\+\\-\\*/\\|&\\^~%]";
const std::string LexemePattern::symFunction = "[[:alpha:]]+";
const std::string LexemePattern::parenthesis = "[\\(\\)]";
const std::string LexemePattern::space = "\\s";
