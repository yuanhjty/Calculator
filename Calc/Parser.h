#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser {
public:
    typedef double ValueType;

public:
    Parser();
    virtual ~Parser() = default;
    virtual void parse(const std::string &formattedExpression) = 0;
    virtual ValueType evalueate() = 0;
    ValueType value() const;
    void setToValue(double (*toValue)(const std::string &));

protected:
    double (*_toValue)(const std::string &);
    ValueType _value;
};

inline Parser::Parser() : _toValue(nullptr), _value(0) { }

inline Parser::ValueType Parser::value() const {
    return _value;
}

inline void Parser::setToValue(double (*toValue)(const std::string &)) {
    _toValue = toValue;
}


#endif // PARSER_H
