#ifndef CALC_ERROR_H
#define CALC_ERROR_H

#include "CalcFlags.h"

#include <exception>
#include <stdexcept>
#include <string>


enum ErrorState {
    ERROR_FIELD = 0xff, ERROR_NOERROR = 0x10,
    ERROR_INNER = 0x02, ERROR_SYMBOL = 0x04,
    ERROR_SYNTAX = 0X08,

    REPAIR_FIELD = 0xff00, REPAIR_NOREPAIR = 0x0100,
    REPAIR_IGNORE = 0x0200, REPAIR_REPLACE = 0x0400,
    REPAIR_APPEND = 0x0800
};

typedef CalcFlags<ErrorState> ErrorFlags;


class CalcError : public std::runtime_error {
public:
    CalcError(const std::string &msg, ErrorFlags flg);
    ErrorFlags errorState() const { return _errorState; }

protected:
    ErrorFlags _errorState;
};


class InnerError : public CalcError {
public:
    InnerError(const std::string &msg);
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
