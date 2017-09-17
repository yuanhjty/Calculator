#include "Output.h"


Output::Output() : _result(0), _infixPtr(new std::string) {}

Output::~Output() {
    if (_infixPtr) delete _infixPtr;
}


