#ifndef UNIT_TABLE_H
#define UNIT_TABLE_H

#include <unordered_map>
#include <string>


class UnitTable {
public:
    void registerUnit(const std::string &id, double weight);
    double unitWeight(const std::string &id) const;

private:
    std::unordered_map<std::string, double> _unitTable;
};

inline void UnitTable::registerUnit(const std::string &id, double weight) {
    _unitTable[id] = weight;
}

#endif // UNIT_TABLE_H
