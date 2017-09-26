#include "Scanner.h"


void Scanner::init()
{

}

void Scanner::scan(const std::string &input) {
    std::shared_ptr<std::string> expression(new std::string);

    expression->append(input);  // for framework test

    setExpression(expression);
}


