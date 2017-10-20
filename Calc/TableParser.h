#ifndef TABLE_PARSER_H
#define TABLE_PARSER_H

#include "Parser.h"
#include "UnitTable.h"
#include "NumeralFormat.h"


class TableParser : public Parser {
public:
    TableParser();
    void setUnitTable(UnitTable *unitTable);
    void parse(const std::string &expr) override;
    ValueType evalueate() override;

private:
    UnitTable *_unitTable;
    double _srcUnitWeight;
    double _dstUnitWeight;
    ValueType _srcValue;
};


inline void TableParser::setUnitTable(UnitTable *unitTable) {
    _unitTable = unitTable;
}

inline Parser::ValueType TableParser::evalueate() {
    return _value = _srcValue * _dstUnitWeight / _srcUnitWeight;
}


#endif // TABLEPARSER_H
