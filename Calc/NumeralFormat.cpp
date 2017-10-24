#include "NumeralFormat.h"
#include "CalcError.h"

#include <sstream>
#include <iomanip>
#include <stack>
#include <cmath>


// For integer and float conversion of integer only operators
long long NumeralConverter::toInteger(double value) {
    double roundValue = value < 0 ? std::ceil(value) : std::floor(value);
    if (!isDblToLLongValid(roundValue))
        throw InnerError("integer overflow");
    return (long long)roundValue;
}

double NumeralConverter::toFloat(long long value) {
    if (!isLLongToDblValid(value))
        throw InnerError("integer overflow");
    return (double)value;
}


// For degree and radian conversion
double NumeralConverter::degToRad(double degValue) {
    return degValue / 57.2957795130823;
}

double NumeralConverter::radToDeg(double radValue) {
    return radValue * 57.2957795130823;
}

double NumeralConverter::noConversion(double value) {
    return value;
}

double (*NumeralConverter::toRad)(double) = NumeralConverter::noConversion;

double (*NumeralConverter::toDeg)(double) = NumeralConverter::noConversion;


// For string and value conversion of science calculator
std::string NumeralConverter::valueToDefaultString(double value) {
    std::ostringstream os;
    os << std::setprecision(13) << value;
    return os.str();
}

std::string NumeralConverter::valueToFixedString(double value) {
    std::ostringstream os;
    if (isDblToLLongValid(value)) {
        os << std::setprecision(0) << std::fixed << value;
        return os.str();
    } else {
        int decimalPlaces = 14 - std::floor(std::log10(std::abs(value)));
        os << std::setprecision(decimalPlaces) << std::fixed << value;
        std::string str = os.str();
        auto endPos = str.size() - 1;
        for (; 0 < endPos && ('0' == str[endPos] || '.' == str[endPos]); --endPos)
            str.pop_back();
        return str;
    }
}

std::string NumeralConverter::valueToScientificString(double value) {
    std::ostringstream os;
    int decimalPlaces = 14 - std::floor(std::log10(std::abs(value)));
    os << std::setprecision(decimalPlaces) << std::fixed << value;

    std::string str = os.str();
    size_t endPos = str.size() - 1;
    size_t begPos = 0;
    for (; begPos < endPos && ('0' == str[endPos] || '.' == str[endPos]); --endPos);
    for (; begPos < endPos && ('0' == str[begPos] || '.' == str[begPos]); ++begPos);

    decimalPlaces = endPos - begPos;
    if (std::string::npos != str.substr(begPos, decimalPlaces + 1).find('.'))
         --decimalPlaces;
    decimalPlaces = decimalPlaces >= 1 ? decimalPlaces : 1;

    os.str("");
    os << std::setprecision(decimalPlaces) << std::scientific << value;
    return os.str();
}

double NumeralConverter::defaultStringToValue(const std::string &token) {
    double value = 0;
    try {
        value = std::stod(token);
    } catch (std::invalid_argument) {
        throw SymbolError("undefined symbol: " + token, REPAIR_APPEND);
    } catch (std::out_of_range) {
        throw InnerError("floating point number overflow");
    }
    return value;
}


// For string and value conversion of programmer claculator
std::string NumeralConverter::vlaueToIntegerString(double value, int base) {
    std::ostringstream os;
    os.setf(std::ios::uppercase);
    os << std::setbase(base);
    os << NumeralConverter::toInteger(value);
    return os.str();
}

std::string NumeralConverter::valueTobinaryString(double value) {
    return valueTobinaryString(value, " ");
}

std::string NumeralConverter::valueTobinaryString(double value, const std::string &delim) {
    std::string hexStr = vlaueToIntegerString(value, 16);
    std::string binStr;
    for (std::size_t i = 0; i < hexStr.size(); ++i) {
        char dgt = hexStr[i];
        int idx = ('0' <= dgt && dgt <= '9') ? (dgt - '0') : (dgt - 'A' + 10);
        binStr.append(hexToBinMap[idx] + delim);
    }
    binStr.pop_back();
    return binStr;
}

std::string NumeralConverter::valueToOctalString(double value) {
    return vlaueToIntegerString(value, 8);
}

std::string NumeralConverter::valueToDecimalString(double value) {
    return vlaueToIntegerString(value, 10);
}

std::string NumeralConverter::valueToHexString(double value) {
    return vlaueToIntegerString(value, 16);
}

double NumeralConverter::integerStringToValue(const std::string &token, int base) {
    long long value = 0;
    try {
        value = std::stoll(token, nullptr, base);
    } catch (std::invalid_argument) {
        throw SymbolError("undefined symbol: " + token, REPAIR_APPEND);
    } catch (std::out_of_range) {
        throw InnerError("integer overflow");
    }
    return toFloat(value);

}

double NumeralConverter::binaryStringToValue(const std::string &token) {
    return integerStringToValue(token, 2);
}

double NumeralConverter::octalStringToValue(const std::string &token) {
    return integerStringToValue(token, 8);
}

double NumeralConverter::decimalStringToValue(const std::string &token) {
    return integerStringToValue(token, 10);
}

double NumeralConverter::hexStringToValue(const std::string &token) {
    return integerStringToValue(token, 16);
}

std::string NumeralConverter::hexToBinMap[16] = {
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};
