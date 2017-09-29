#ifndef UTIL_H
#define UTIL_H


#include <string>
#include <iostream>
#include <memory>
#include <climits>

//
// Define class Util
//
class Util {
public:
    static std::string trimEndsSpaces(const std::string& str);

//    static void printResult(const std::string& expression, const std::string& result);
//    static void printWelcome();
//    static void printHelp();

    static std::string toString(double value);

    static bool isDblToLLongValid(double dValue) {
        return ((long)dValue == dValue);
    }
};


//
// Define class LexemePattern
//
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
};


#endif // UTIL_H
