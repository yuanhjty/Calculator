#include "Util.h"


// LexemePattern
const std::string LexemePattern::numReal = "\\d+(\\.\\d*)?(e\\d+)?";
const std::string LexemePattern::numBinary = "[01]+";
const std::string LexemePattern::numOctal = "[0-7]+";
const std::string LexemePattern::numDecimal = "\\d+";
const std::string LexemePattern::numHex = "[[:xdigit:]]+";

const std::string LexemePattern::opCommon = "[\\+\\-\\*/\\^!]|mod";
const std::string LexemePattern::opBitwise = "[\\+\\-\\*/]|or|and|xor|not";

const std::string LexemePattern::symbol = "[[:alpha:]]+";

const std::string LexemePattern::parenthesis = "[\\(\\)]";
const std::string LexemePattern::space = "\\s";


const std::string LexemePattern::scientificReal =
        LexemePattern::numReal + "|" + LexemePattern::opCommon
        + "|" + LexemePattern::symbol + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;

const std::string LexemePattern::programmerBinary =
        LexemePattern::numBinary + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symbol + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerOctal =
        LexemePattern::numOctal + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symbol + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerDecimal =
        LexemePattern::numDecimal + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symbol + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
const std::string LexemePattern::programmerHex =
        LexemePattern::numHex + "|" + LexemePattern::opBitwise
        + "|" + LexemePattern::symbol + "|" + LexemePattern::parenthesis
        + "|" + LexemePattern::space;
