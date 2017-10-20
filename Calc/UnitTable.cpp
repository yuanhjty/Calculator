#include "UnitTable.h"

double UnitTable::unitWeight(const std::string &id) const {
    const auto it = _unitTable.find(id);
    if (it == _unitTable.cend())
        return 0;
    return it->second;
}
