#include "CalcError.h"

CalcError::CalcError(const std::string &msg, ErrorFlags flg) :
    std::runtime_error(msg), _errorState(flg) { }

InnerError::InnerError(const std::string &msg) :
    CalcError(msg, ErrorFlags(ERROR_INNER) | REPAIR_NOREPAIR) { }

SymbolError::SymbolError(const std::string &msg, ErrorFlags flg) :
    CalcError(msg, ERROR_SYMBOL) { _errorState |= flg; }

SyntaxError::SyntaxError(const std::string &msg, ErrorFlags flg) :
    CalcError(msg, ERROR_SYNTAX) { _errorState |= flg; }
