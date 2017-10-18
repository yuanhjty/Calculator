#include "DataConvert.h"

#include <sstream>


DataConverter::DataConverter() : _dataFormat(DF_DEFAULT) { }

void DataConverter::setDataFormat(DataFormat dataFormat) {
    _dataFormat = dataFormat;
    // Convert function pointers according to _dataFormat and dataFormat.
}

double DataConverter::degToRad(double degValue) {
    return degValue / 57.2957795130823208767981;
}

double DataConverter::radToDeg(double radValue) {
    return radValue * 57.2957795130823208767981;
}

double DataConverter::noConversion(double value) {
    return value;
}

std::string DataConverter::valueToDecimalString(double value) {
    std::ostringstream os;
    os.precision(15);
    os << value;
    return os.str();
}

double (*DataConverter::toRad)(double) = DataConverter::noConversion;
double (*DataConverter::toDeg)(double) = DataConverter::noConversion;
std::string (*DataConverter::toString)(double) = DataConverter::valueToDecimalString;
