#include "LexicalSet.h"


const std::string LexicalSet::numReal = "\\d+(\\.\\d*)?(e\\d+)?";
const std::string LexicalSet::numBinary = "[01]+";
const std::string LexicalSet::numOctal = "[0-7]+";
const std::string LexicalSet::numDecimal = "\\d+";
const std::string LexicalSet::numHex = "[[:xdigit:]]+";

const std::string LexicalSet::opCommon = "[\\+\\-\\*/\\^!]|mod";
const std::string LexicalSet::opBitwise = "[\\+\\-\\*/]|or|and|xor|not";

const std::string LexicalSet::symbol = "[[:alpha:]]+";
const std::string LexicalSet::parenthesis = "[\\(\\)]";
const std::string LexicalSet::space = "\\s";

const std::string LexicalSet::calCommon =
        LexicalSet::symbol + "|" + LexicalSet::parenthesis + "|" + LexicalSet::space;
const std::string LexicalSet::progCommon =
        LexicalSet::opBitwise + "|" + LexicalSet::calCommon;

