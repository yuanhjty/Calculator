#ifndef CONVERTER_H
#define CONVERTER_H

#include "Calculator.h"
#include "UnitTable.h"
#include "TableParser.h"
#include "NumeralFormat.h"


//
class Converter : public Calculator {
public:
    Converter();
    ~Converter();
    void setNumeralFormat(NumeralFormat format) override;

protected:
    UnitTable *_unitTable;
};


//
class LengthConverter : public Converter {
public:
    LengthConverter();

private:
    void initUnitTable();
};


//
class AreaConverter : public Converter {
public:
    AreaConverter();

private:
    void initUnitTable();
};


//
class VolumeConverter : public Converter {
public:
    VolumeConverter();

private:
    void initUnitTable();
};


//
class WeightConverter : public Converter {
public:
    WeightConverter();

private:
    void initUnitTable();
};


//
class TimeConverter : public Converter {
public:
    TimeConverter();

private:
    void initUnitTable();
};


//
class VelocityConverter : public Converter {
public:
    VelocityConverter();

private:
    void initUnitTable();
};


//
class PowerConverter : public Converter {
public:
    PowerConverter();

private:
    void initUnitTable();
};


//
class EnergyConverter : public Converter {
public:
    EnergyConverter();

private:
    void initUnitTable();
};


//
class PressureConverter : public Converter {
public:
    PressureConverter();

private:
    void initUnitTable();
};


//
class DataConverter : public Converter {
public:
    DataConverter();

private:
    void initUnitTable();
};


//
class AngleConverter : public Converter {
public:
    AngleConverter();

private:
    void initUnitTable();
};


#endif // CONVERTER_H
