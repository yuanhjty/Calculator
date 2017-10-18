#include "Calculator.h"

Calculator::Calculator(
        Parser *parser, DataConverter *dataConvert) :
    _scanner(new Scanner),
    _resultHandler(new ResultHandler),
    _parser(parser),
    _dataConvert(dataConvert) { }

Calculator::~Calculator() {
    if (_dataConvert) {
        delete _dataConvert;
        _dataConvert = nullptr;
    }

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
                    DataConverter::toString(_parser->evalueate()));
    } catch (const CalcError &e) {
        _resultHandler->setCurrentResult(
                    _scanner->formattedExpression(), e.what());
        _resultHandler->setErrorState(e.errorState());
    }
}


