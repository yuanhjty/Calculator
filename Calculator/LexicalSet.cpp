#include "LexicalSet.h"


const std::string LexicalSet::numReal = "\\d+(\\.\\d*)?(e[\\+\\-]?\\d+)?";
const std::string LexicalSet::numBinary = "[01]+";
const std::string LexicalSet::numOctal = "[0-7]+";
const std::string LexicalSet::numDecimal = "\\d+(e\\d+)?";
const std::string LexicalSet::numHex = "[[:xdigit:]]+";

const std::string LexicalSet::opReal = "[%/\\+\\-\\^\\*]";
const std::string LexicalSet::opInteger = "[%/\\+\\-\\*]|or|and|xor|not";

const std::string LexicalSet::symbol = "[[:alpha:]]+";
const std::string LexicalSet::bracket = "[\\(\\)]";
const std::string LexicalSet::space = "\\s";

const std::string LexicalSet::calCommon =
        LexicalSet::symbol + "|" + LexicalSet::bracket + "|" + LexicalSet::space;
const std::string LexicalSet::realCalCommon =
        LexicalSet::opReal + "|" + LexicalSet::calCommon;
const std::string LexicalSet::integerCalCommon =
        LexicalSet::opInteger + "|" + LexicalSet::calCommon;

