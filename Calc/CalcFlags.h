#ifndef CALC_FLAGS_H
#define CALC_FLAGS_H

#include <type_traits>


// Parts of QFlags' source code.
template <typename Enum>
class CalcFlags {
    static_assert((sizeof(Enum) <= sizeof(int)),
                  "CalcFlags uses an int as storage, so an enum with underlying "
                  "long long will overflow.");
    static_assert((std::is_enum<Enum>::value), "CalcFlags is only usable on enumeration types.");

public:
    typedef typename std::conditional<
    std::is_unsigned<typename std::underlying_type<Enum>::type>::value,
    unsigned int,
    signed int
    >::type Int;

public:
    CalcFlags(int value = 0) : _value(value) { }
    CalcFlags(const CalcFlags &other) : _value(other._value) { }
    CalcFlags(Enum f) : _value((Int)f) { }
    CalcFlags &operator=(const CalcFlags &other) { _value = other._value; return *this; }
    CalcFlags &operator=(Enum f) { _value = (Int)f; return *this; }
    CalcFlags &operator|=(CalcFlags f) { _value |= f._value; return *this; }
    CalcFlags &operator|=(Enum f) { _value |= (Int)f; return *this; }
    CalcFlags operator|(CalcFlags f) const { return _value | f._value; }
    CalcFlags operator|(Enum f) const { return _value | (Int)f ; }
    CalcFlags operator&(CalcFlags f) const { return _value & f._value; }
    CalcFlags operator&(Enum f) const { return _value & (Int)f; }
    explicit operator Enum() const { return (Enum)_value; }
    bool operator==(CalcFlags f) const { return _value == f._value; }
    bool operator==(Enum f) const { return _value == (Int)f; }
    bool operator!=(CalcFlags f) const { return _value != f._value; }
    bool operator!=(Enum f) const { return _value != (Int)f; }

private:
    Int _value;
};


#endif // CALC_FLAGS_H
