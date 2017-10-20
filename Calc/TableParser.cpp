#include "TableParser.h"
#include "CalcError.h"

#include <sstream>
#include <vector>


TableParser::TableParser() :
    _unitTable(nullptr), _srcUnitWeight(0),
    _dstUnitWeight(0), _srcValue(0) {
    setToValue(NumeralConverter::defaultStringToValue);
}

void TableParser::parse(const std::string &expr) {
    std::istringstream is(expr);
    std::string token;
    std::vector<std::string> exprNodes;
    exprNodes.reserve(4);

    while (is >> token)
        exprNodes.push_back(token);

    // Expr format should be like "2.3 m to mm".
    if (exprNodes.size() != 4 || exprNodes[2] != "to")
        throw SyntaxError("syntax error", REPAIR_NOREPAIR);

    _srcValue = _toValue(exprNodes[0]);

    if (0 == (_srcUnitWeight = _unitTable->unitWeight(exprNodes[1])))
        throw SymbolError("undefined unit: " + exprNodes[1], FILTER_IGNORE);

    if (0 == (_dstUnitWeight = _unitTable->unitWeight(exprNodes[3])))
        throw SymbolError("undefined unit: " + exprNodes[3], FILTER_IGNORE);
}
