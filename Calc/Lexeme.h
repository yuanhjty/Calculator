#ifndef LEXEME_H
#define LEXEME_H

#include <string>


class Lexeme {
private:
    static const std::string numReal;
    static const std::string numBinary;
    static const std::string numOctal;
    static const std::string numDecimal;
    static const std::string numHex;

    static const std::string opReal;
    static const std::string opInteger;

    static const std::string unit;

    static const std::string symbol;
    static const std::string bracket;
    static const std::string space;

    static const std::string calCommon;
    static const std::string realCalCommon;
    static const std::string integerCalCommon;

public:
    static std::string realExprLexeme() {
        return numReal + "|" + realCalCommon;
    }

    static std::string binaryExprLexeme() {
        return numBinary + "|" + integerCalCommon;
    }

    static std::string octalExprLexeme() {
        return numOctal + "|" + integerCalCommon;
    }

    static std::string decimalExprLexeme() {
        return numDecimal + "|" + integerCalCommon;
    }

    static std::string hexExprLexeme() {
        return  "And|" + numHex + "|" + integerCalCommon;
    }

    static std::string convertLexeme() {
        return numReal + "|" + unit + "|" + space;
    }
};


#endif // LEXEME_H
