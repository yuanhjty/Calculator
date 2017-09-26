#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression
{
protected:
    std::string m_result;

public:
    Expression();

    void init();
    void evaluate();

    std::string getResult() const {
        return m_result;
    }
};

#endif // EXPRESSION_H
