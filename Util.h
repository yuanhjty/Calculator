#ifndef UTIL_H
#define UTIL_H


#include <string>
#include <iostream>
#include <memory>
#include <climits>


typedef std::shared_ptr<std::string> StringPtr;


// The class Util
class Util {
public:
    static std::string trimEndsSpaces(const std::string& str);
    static bool isDblToLLongValid(double dValue);
};

inline bool Util::isDblToLLongValid(double dValue) {
    return ((long)dValue == dValue);
}


// The class LexemePattern
class LexemePattern {
public:
    static const std::string numReal;
    static const std::string numBinary;
    static const std::string numOctal;
    static const std::string numDecimal;
    static const std::string numHex;

    static const std::string opCommon;
    static const std::string opBitwise;

    static const std::string symFunction;

    static const std::string parenthesis;
    static const std::string space;


    static const std::string scientificReal;

    static const std::string programmerBinary;
    static const std::string programmerOctal;
    static const std::string programmerDecimal;
    static const std::string programmerHex;
};


#endif // UTIL_H
