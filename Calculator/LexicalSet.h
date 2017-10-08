#ifndef LEXICALSET_H
#define LEXICALSET_H


#include <string>


class LexicalSet {
private:
public:
    static const std::string numReal;
    static const std::string numBinary;
    static const std::string numOctal;
    static const std::string numDecimal;
    static const std::string numHex;

    static const std::string opReal;
    static const std::string opInteger;

    static const std::string symbol;
    static const std::string parenthesis;
    static const std::string space;

    static const std::string calCommon;
    static const std::string realCalCommon;
    static const std::string integerCalCommon;

public:
    static std::string getRealExprLexicalSet() {
        return numReal + "|" + realCalCommon;
    }

    static std::string getBinaryExprLexicalSet() {
        return numBinary + "|" + integerCalCommon;
    }

    static std::string getOctalExprLexicalSet() {
        return numOctal + "|" + integerCalCommon;
    }

    static std::string getDecimalExprLexicalSet() {
        return numDecimal + "|" + integerCalCommon;
    }

    static std::string getHexExprLexicalSet() {
        return numHex + "|" + integerCalCommon;
    }
};


#endif // LEXICALSET_H
