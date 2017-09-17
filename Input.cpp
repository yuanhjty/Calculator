#include "Input.h"


Input::Input() : _input(new std::string) {}

Input::~Input() {
    if (_input) delete _input;
}
