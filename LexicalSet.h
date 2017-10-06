#ifndef LEXICALSET_H
#define LEXICALSET_H


#include <string>


class LexicalSet {
private:
    static const std::string numReal;
    static const std::string numBinary;
    static const std::string numOctal;
    static const std::string numDecimal;
    static const std::string numHex;

    static const std::string opCommon;
    static const std::string opBitwise;

    static const std::string symbol;
    static const std::string parenthesis;
    static const std::string space;

    static const std::string calCommon;
    static const std::string progCommon;

public:
    static std::string getScientificRealSet() {
        return numReal + "|" + opCommon + "|" + calCommon;
    }

    static std::string getProgrammerBinaryLSet() {
        return numBinary + "|" + progCommon;
    }

    static std::string getProgrammerOctalLSet() {
        return numOctal + "|" + progCommon;
    }

    static std::string getProgrammerDecimalLSet() {
        return numDecimal + "|" + progCommon;
    }

    static std::string getProgrammerHexLSet() {
        return numHex + "|" + progCommon;
    }
};


#endif // LEXICALSET_H
