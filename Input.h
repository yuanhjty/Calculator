#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <iostream>


class Input {
public:
    Input();
    ~Input();

    void reset();
    void setInput(const std::string& input);
    std::string getInput();

private:
    std::string* _input;
};

inline void Input::reset() {
    _input->clear();
}

inline void Input::setInput(const std::string& input) {
    _input->append(input);
}

inline std::string Input::getInput() {
    return *_input;
}


#endif // INPUT_H
