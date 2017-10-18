#ifndef DATACONVERT_H
#define DATACONVERT_H

#include <string>


enum DataFormat {
    DF_DEFAULT = 0x0,

    // For science calculator
    DF_DEGREE = 0x1, DF_RADIAN = 0x2,   // angle unit
    DF_FLOAT = 0x4, DF_EXPONENT = 0x8,  // number notation method

    // For programmer calculator
    DF_HEX = 0x10, DF_DECIMAL = 0x20,
    DF_OCTAL = 0x40, DF_BINARY = 0x80 // numerical system
};


class DataConverter {
public:
    DataConverter();
    void setDataFormat(DataFormat dataFormat);

    static double degToRad(double degValue);
    static double radToDeg(double radValue);
    static double noConversion(double value);
    static std::string valueToDecimalString(double value);

public:
    static double (*toRad)(double);
    static double (*toDeg)(double);
    static std::string (*toString)(double);

private:
    DataFormat _dataFormat;
};


#endif // DATACONVERT_H
