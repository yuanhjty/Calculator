#include "Util.h"


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
