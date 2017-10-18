#include "CalcError.h"

CalcError::CalcError(const std::string &msg) :
    std::runtime_error(msg), _errorState(ERROR_NOERROR) { }

InnerError::InnerError(const std::string &msg, ErrorFlags flags) :
    CalcError(msg) { (_errorState |= ERROR_INNER) |= flags; }

SymbolError::SymbolError(const std::string &msg, ErrorFlags flags) :
    CalcError(msg) { (_errorState |= ERROR_SYMBOL) |= flags; }

SyntaxError::SyntaxError(const std::string &msg, ErrorFlags flags) :
    CalcError(msg) { (_errorState  |= ERROR_SYNTAX)|= flags; }

IncompleteError::IncompleteError(const std::string &msg, ErrorFlags flags) :
    CalcError(msg) { (_errorState  |= ERROR_INCOMPLETE)|= flags; }
