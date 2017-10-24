#include "Converter.h"

// Converter
Converter::Converter() :
    Calculator(new TableParser, NumeralConverter::valueToDefaultString),
    _unitTable(new UnitTable) {
    _scanner->setLexeme(Lexeme::convertLexeme());
    _parser->setToValue(NumeralConverter::defaultStringToValue);
}

Converter::~Converter() {
    delete _unitTable;
    _unitTable = nullptr;
}

void Converter::setNumeralFormat(NumeralFormat format) {
    switch (format) {
    case NF_DEGREE: case NF_RADIAN:
    case NF_DEFAULT: case NF_FIXED: case NF_SCIENTIFIC:
    case NF_BINARY: case NF_OCTAL: case NF_DECIMAL: case NF_HEX:
        // print prompt information
        break;

    default:
        throw InnerError("inner error: undefined numeral format");
        break;
    }
}

// LengthConverter
LengthConverter::LengthConverter() {
    _scanner->setLexeme(Lexeme::convertLexeme());
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void LengthConverter::initUnitTable() {
    _unitTable->registerUnit("nm", 1e9);
    _unitTable->registerUnit("um", 1e6);
    _unitTable->registerUnit("mm", 1e3);
    _unitTable->registerUnit("cm", 1e2);
    _unitTable->registerUnit("m", 1e0);
    _unitTable->registerUnit("km", 1e-3);
    _unitTable->registerUnit("in", 39.37008);
    _unitTable->registerUnit("ft", 3.28084);
    _unitTable->registerUnit("yd", 1.093613);
    _unitTable->registerUnit("mile", 0.000621);
    _unitTable->registerUnit("sea-mile", 0.00054);
}


// AreaConverter
AreaConverter::AreaConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void AreaConverter::initUnitTable() {
    _unitTable->registerUnit("sq-mm", 1e6);
    _unitTable->registerUnit("sq-cm", 1e4);
    _unitTable->registerUnit("sq-m", 1e0);
    _unitTable->registerUnit("ha", 1e-4);
    _unitTable->registerUnit("sq-km", 1e-6);
    _unitTable->registerUnit("sq-in", 1550.003);
    _unitTable->registerUnit("sq-ft", 10.76391);
    _unitTable->registerUnit("sq-yd", 1.19599);
    _unitTable->registerUnit("acre", 0.000247);
    _unitTable->registerUnit("sq-mile", 0.00000038610216);
}


// VolumeConverter
VolumeConverter::VolumeConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void VolumeConverter::initUnitTable() {
    _unitTable->registerUnit("mL", 1e6);
    _unitTable->registerUnit("cu-cm", 1e6);
    _unitTable->registerUnit("L", 1e3);
    _unitTable->registerUnit("cu-m", 1e0);
    _unitTable->registerUnit("cu-in", 61023.74);
    _unitTable->registerUnit("cu-ft", 35.31467);
    _unitTable->registerUnit("cu-yd", 1.307951);
    _unitTable->registerUnit("uk-pt", 1759.754);
    _unitTable->registerUnit("us-pt", 2113.376);
    _unitTable->registerUnit("uk-qt", 879.877);
    _unitTable->registerUnit("us-qt", 1056.688);
    _unitTable->registerUnit("uk-gal", 219.9692);
    _unitTable->registerUnit("us-gal", 264.1721);
    _unitTable->registerUnit("uk-fl-oz", 35195.08);
    _unitTable->registerUnit("us-fl-oz", 33814.02);
}


// WeightConverter
WeightConverter::WeightConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void WeightConverter::initUnitTable() {
    _unitTable->registerUnit("ct", 5e3);
    _unitTable->registerUnit("mg", 1e6);
    _unitTable->registerUnit("cg", 1e5);
    _unitTable->registerUnit("g", 1e3);
    _unitTable->registerUnit("kg", 1e0);
    _unitTable->registerUnit("t", 1e-3);
    _unitTable->registerUnit("oz", 35.27396);
    _unitTable->registerUnit("lb", 2.204623);
}


// TimeConverter
TimeConverter::TimeConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void TimeConverter::initUnitTable() {
    _unitTable->registerUnit("us", 3.6e9);
    _unitTable->registerUnit("ms", 3.6e6);
    _unitTable->registerUnit("s", 3.6e3);
    _unitTable->registerUnit("min", 60);
    _unitTable->registerUnit("h", 1);
    _unitTable->registerUnit("d", 0.041667);
    _unitTable->registerUnit("w", 0.005952);
    _unitTable->registerUnit("y", 0.000114);
}


// VelocityConverter
VelocityConverter::VelocityConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void VelocityConverter::initUnitTable() {
    _unitTable->registerUnit("cm-s", 100);
    _unitTable->registerUnit("in-s", 3.28084);
    _unitTable->registerUnit("m-s", 1);
    _unitTable->registerUnit("km-h", 3.6);
    _unitTable->registerUnit("ft-h", 2.237136);
    _unitTable->registerUnit("knot", 1.944012);
    _unitTable->registerUnit("Mach", 0.002939);
}


// PowerConverter
PowerConverter::PowerConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void PowerConverter::initUnitTable() {
    _unitTable->registerUnit("W", 1);
    _unitTable->registerUnit("KW", 1e-3);
    _unitTable->registerUnit("hp", 0.001341);
}


// EnergyConverter
EnergyConverter::EnergyConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void EnergyConverter::initUnitTable() {
    _unitTable->registerUnit("J", 1);
    _unitTable->registerUnit("KJ", 1e-3);
    _unitTable->registerUnit("cal", 0.239006);
}


// PressureConverter
PressureConverter::PressureConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void PressureConverter::initUnitTable() {
    _unitTable->registerUnit("atmos", 1);
    _unitTable->registerUnit("bar", 1.01325);
    _unitTable->registerUnit("kPa", 101.325);
    _unitTable->registerUnit("mmHg", 760.1275);
    _unitTable->registerUnit("Pa", 101325);
}


// DataConverter
DataConverter::DataConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void DataConverter::initUnitTable() {
    _unitTable->registerUnit("bit", 8e9);
    _unitTable->registerUnit("B", 1e9);
    _unitTable->registerUnit("Kb", 8e6);
    _unitTable->registerUnit("Kib", 7812500);
    _unitTable->registerUnit("KB", 1e6);
    _unitTable->registerUnit("KiB", 976562.5);
    _unitTable->registerUnit("Mb", 8e3);
    _unitTable->registerUnit("Mib", 7629.395);
    _unitTable->registerUnit("MB", 1e3);
    _unitTable->registerUnit("MiB", 953.6743);
    _unitTable->registerUnit("Gb", 8);
    _unitTable->registerUnit("Gib", 7.450581);
    _unitTable->registerUnit("GB", 1);
    _unitTable->registerUnit("GiB", 0.931323);
    _unitTable->registerUnit("Tb", 8e-3);
    _unitTable->registerUnit("Tib", 0.007276);
    _unitTable->registerUnit("TB", 1e-3);
    _unitTable->registerUnit("TiB", 0.000909);
    _unitTable->registerUnit("Pb", 8e-6);
    _unitTable->registerUnit("Pib", 0.000007);
    _unitTable->registerUnit("PB", 1e-6);
    _unitTable->registerUnit("PiB", 0.00000088817842);
    _unitTable->registerUnit("Eb", 8e-9);
    _unitTable->registerUnit("Eib", 0.00000000693889);
    _unitTable->registerUnit("EB", 1e-9);
    _unitTable->registerUnit("EiB", 0.00000000086736);
    _unitTable->registerUnit("Zb", 8e-12);
    _unitTable->registerUnit("Zib", 0.00000000000678);
    _unitTable->registerUnit("ZB", 1e-12);
    _unitTable->registerUnit("ZiB", 0.00000000000085);
    _unitTable->registerUnit("Yb", 8e-15);
    _unitTable->registerUnit("Yib", 6.617445e-15);
    _unitTable->registerUnit("YB", 1e-15);
    _unitTable->registerUnit("YiB", 8.271806e-16);
}


// AngleConverter
AngleConverter::AngleConverter() {
    initUnitTable();
    static_cast<TableParser *>(_parser)->setUnitTable(_unitTable);
}

void AngleConverter::initUnitTable() {
    _unitTable->registerUnit("rad", 1);
    _unitTable->registerUnit("deg", 57.29578);
}


