#include "Calculator.h"

Calculator::Calculator(Parser *parser, std::string (*toString)(double)) :
    _scanner(new Scanner),
    _resultHandler(new ResultHandler),
    _parser(parser),
    _toString(toString) { }

Calculator::~Calculator() {
    delete _parser;
    _parser = nullptr;

    delete _resultHandler;
    _resultHandler = nullptr;

    delete _scanner;
    _scanner = nullptr;
}

void Calculator::evaluate(const std::string &userExpression) {
    try {
        _scanner->scan(userExpression);
        _parser->parse(_scanner->formattedExpression());
        _resultHandler->setCurrentResult(
                    _scanner->formattedExpression(),
                    _toString(_parser->evalueate()));
        _resultHandler->setErrorState(ERROR_NOERROR);
    } catch (const CalcError &e) {
        _resultHandler->setCurrentResult(
                    _scanner->formattedExpression(), e.what());
        _resultHandler->setErrorState(e.errorState());
    }
}




