#ifndef CALC_ERROR_H
#define CALC_ERROR_H

#include "CalcFlags.h"

#include <exception>
#include <stdexcept>
#include <string>


enum ErrorState {
    ERROR_FIELD = 0xff, ERROR_NOERROR = 0x10,
    ERROR_INNER = 0x02, ERROR_SYMBOL = 0x04,
    ERROR_SYNTAX = 0X08, ERROR_INCOMPLETE = 0x10,

    FILTER_FIELD = 0xff00, FILTER_NOFILTER = 0x0100,
    FILTER_IGNORE = 0x0200, FILTER_REPLACE = 0x0400,

    REPAIR_FIELD = 0xff0000, REPAIR_NOREPAIR = 0x010000,
    REPAIR_BACK = 0x020000, REPAIR_APPEND = 0x040000
};

typedef CalcFlags<ErrorState> ErrorFlags;


class CalcError : public std::runtime_error {
public:
    CalcError(const std::string &msg);
    ErrorFlags errorState() const { return _errorState; }

protected:
    ErrorFlags _errorState;
};


class InnerError : public CalcError {
public:
    InnerError(const std::string &msg, ErrorFlags flags);
};


class SymbolError : public CalcError {
public:
    SymbolError(const std::string &msg, ErrorFlags flags);
};


class SyntaxError : public CalcError {
public:
    SyntaxError(const std::string &msg, ErrorFlags flags);
};


class IncompleteError : public CalcError {
public:
    IncompleteError(const std::string &msg, ErrorFlags flags);
};


#endif // CALC_ERROR_H
