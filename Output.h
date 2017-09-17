#ifndef OUTPUT_H
#define OUTPUT_H


#include <string>
#include <iostream>


class Output {
public:
    Output();
    ~Output();

    void reset();
    void setInfix(const std::string& infix);
    void setResult(double result);
    std::string getInfix();
    double getResult();

private:
    double _result;
    std::string* _infixPtr;
};


inline void Output::reset() {
    _result = 0;
    _infixPtr->clear();
}

inline void Output::setInfix(const std::string& infix) {
    *_infixPtr = infix;
}

inline void Output::setResult(double result) {
    _result = result;
}

inline std::string Output::getInfix() {
    return *_infixPtr;
}

inline double Output::getResult() {
    return _result;
}


#endif // OUTPUT_H
