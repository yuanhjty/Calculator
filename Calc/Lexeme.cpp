#include "Lexeme.h"


const std::string Lexeme::numReal = "\\d+(\\.\\d*)?(e[\\+\\-]?\\d+)?";
const std::string Lexeme::numBinary = "[01]+";
const std::string Lexeme::numOctal = "[0-7]+";
const std::string Lexeme::numDecimal = "\\d+";
const std::string Lexeme::numHex = "[[:xdigit:]]+";

const std::string Lexeme::opReal = "[%/\\+\\-\\^\\*]";
const std::string Lexeme::opInteger = "or|and|xor|not|[%/\\+\\*\\-]";

const std::string Lexeme::unit = "[[:alpha:]]+(\\-[[:alpha:]]+)*";

const std::string Lexeme::symbol = "[[:alpha:]]+";
const std::string Lexeme::bracket = "[\\(\\)]";
const std::string Lexeme::space = "\\s";

const std::string Lexeme::calCommon =
        Lexeme::symbol + "|" + Lexeme::bracket + "|" + Lexeme::space;
const std::string Lexeme::realCalCommon =
        Lexeme::opReal + "|" + Lexeme::calCommon;
const std::string Lexeme::integerCalCommon =
        Lexeme::opInteger + "|" + Lexeme::calCommon;
