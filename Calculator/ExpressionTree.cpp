#include "ExpressionTree.h"
#include "ExpressionException.h"


// Util
long long Util::toInteger(double value) {
    if (!isDblToLLongValid(value))
        throw NumericOverflow("integer overflow");
    return (long long)value;
}

double Util::toFloat(long long value) {
    if (!isLLongToDblValid(value))
        throw NumericOverflow("integer overflow");
    return (double)value;
}
