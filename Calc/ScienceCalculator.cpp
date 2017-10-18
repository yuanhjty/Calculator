#include "ScienceCalculator.h"

ScienceCalculator::ScienceCalculator() :
    Calculator(new TreeParser),
    _symbolTable(new SymbolTable) {

    _scanner->setLexeme(Lexeme::realExprLexeme());

    initSymbolTable();
    static_cast<TreeParser *>(_parser)->setSymbolTable(_symbolTable);
}

ScienceCalculator::~ScienceCalculator() {
    delete _symbolTable;
    _symbolTable = nullptr;
}

void ScienceCalculator::initSymbolTable() {
    // binary operaetors
    _symbolTable->registerSymbol("+", new Plus);
    _symbolTable->registerSymbol("-", new BMinus);
    _symbolTable->registerSymbol("*", new Multi);
    _symbolTable->registerSymbol("/", new Divide);
    _symbolTable->registerSymbol("%", new Modulo);
    _symbolTable->registerSymbol("^", new Power);

    // unary operators
    _symbolTable->registerSymbol("u-", new UMinus);
    _symbolTable->registerSymbol("sin", new Sin);
    _symbolTable->registerSymbol("cos", new Cos);
    _symbolTable->registerSymbol("tan", new Tan);
    _symbolTable->registerSymbol("asin", new Asin);
    _symbolTable->registerSymbol("acos", new Acos);
    _symbolTable->registerSymbol("atan", new Atan);
    _symbolTable->registerSymbol("lg", new Lg);
    _symbolTable->registerSymbol("ln", new Ln);
    _symbolTable->registerSymbol("sqrt", new Sqrt);
    // not implemented yet
    // m_symbolTable->registerSymbol("!", new Fact);

    // constants
    _symbolTable->registerSymbol("pi", new ConstPi);
    _symbolTable->registerSymbol("e", new ConstE);
}

