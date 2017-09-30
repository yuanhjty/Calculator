#include "Util.h"


// Util
// trimEndsSpaces
std::string Util::trimEndsSpaces(const std::string &str) {
    auto first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return str.substr(0, 0);

    auto last = str.find_last_not_of(" \t");
    auto n = last == std::string::npos ? str.size() - first : last - first + 1;

    return str.substr(first, n);
}

// LexemePattern
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


const std::string LexemePattern::scientificReal =
        LexemePattern::numReal + "|" + LexemePattern::opCommon
        + "|" + LexemePattern::symFunction + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;

const std::string LexemePattern::programmerBinary =
        LexemePattern::numBinary + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symFunction + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerOctal =
        LexemePattern::numOctal + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symFunction + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerDecimal =
        LexemePattern::numDecimal + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symFunction + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerHex =
        LexemePattern::numHex + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symFunction + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
