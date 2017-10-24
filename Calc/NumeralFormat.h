#ifndef NUMERAL_FORMAT_H
#define NUMERAL_FORMAT_H

#include "CalcFlags.h"
#include <string>
#include <cmath>


enum NumeralFormat {
    // For science calculator
    NF_ANGLE_FIELD = 0x00f,
    NF_DEGREE = 0x001, NF_RADIAN = 0x002,   // angle unit

    NF_NOTATION_FIELD = 0x0f0,
    NF_DEFAULT = 0x010, NF_FIXED = 0x020, NF_SCIENTIFIC = 0x040,  // number notation method

    // For programmer calculator
    NF_NUMERAL_FIELD = 0xf00,
    NF_HEX = 0x100, NF_DECIMAL = 0x200,
    NF_OCTAL = 0x400, NF_BINARY = 0x800 // numeral system
};


class NumeralConverter {
    // For integer and float conversion of integer only operators
public:
    static bool isDblToLLongValid(double dValue);
    static bool isLLongToDblValid(long long llValue);
    static long long toInteger(double value);
    static double toFloat(long long value);

    // For degree and radian conversion
    static double degToRad(double degValue);
    static double radToDeg(double radValue);
    static double noConversion(double value);
    static double (*toRad)(double);
    static double (*toDeg)(double);

    // For string and value conversion of science calculator
    static std::string valueToDefaultString(double value);
    static std::string valueToFixedString(double value);
    static std::string valueToScientificString(double value);
    static double defaultStringToValue(const std::string &token);

    // For string and value conversion of programmer claculator
    static std::string vlaueToIntegerString(double value, int base);
    static std::string valueTobinaryString(double value);
    static std::string valueTobinaryString(double value, const std::string &delim);
    static std::string valueToOctalString(double value);
    static std::string valueToDecimalString(double value);
    static std::string valueToHexString(double value);

    static double integerStringToValue(const std::string &token, int base);
    static double binaryStringToValue(const std::string &token);
    static double octalStringToValue(const std::string &token);
    static double decimalStringToValue(const std::string &token);
    static double hexStringToValue(const std::string &token);

private:
    static std::string hexToBinMap[16];
};


inline bool NumeralConverter::isDblToLLongValid(double dValue) {
    return ((double)((long long)dValue) == dValue);
}

inline bool NumeralConverter::isLLongToDblValid(long long llValue) {
    return ((long long)((double)llValue)) == llValue;
}


#endif // NUMERAL_FORMAT_H
