#include "ExprCalculator.h"
#include "RealOperator.h"
#include "BitwiseOperator.h"
#include "Operand.h"

ExprCalculator::ExprCalculator(std::string (*toString)(double)) :
    Calculator(new TreeParser, toString),
    _symbolTable(new SymbolTable) {
}

ExprCalculator::~ExprCalculator() {
    delete _symbolTable;
    _symbolTable = nullptr;
}


ScienceCalculator::ScienceCalculator() :
    ExprCalculator(NumeralConverter::valueToDefaultString) {
    _scanner->setLexeme(Lexeme::realExprLexeme());
    _parser->setToValue(NumeralConverter::defaultStringToValue);
    initSymbolTable();
    static_cast<TreeParser *>(_parser)->setSymbolTable(_symbolTable);
}

void ScienceCalculator::setNumeralFormat(NumeralFormat format) {
    switch (format) {
    case NF_DEGREE:
        NumeralConverter::toRad = NumeralConverter::degToRad;
        NumeralConverter::toDeg = NumeralConverter::radToDeg;
        break;
    case NF_RADIAN:
        NumeralConverter::toRad = NumeralConverter::noConversion;
        NumeralConverter::toDeg = NumeralConverter::noConversion;
        break;

    case NF_DEFAULT:
        _toString = NumeralConverter::valueToDefaultString;
        break;
    case NF_FIXED:
        _toString = NumeralConverter::valueToFixedString;
        break;
    case NF_SCIENTIFIC:
        _toString = NumeralConverter::valueToScientificString;
        break;

    case NF_BINARY: case NF_OCTAL: case NF_DECIMAL: case NF_HEX:
        // print prompt information
        break;

    default:
        throw InnerError("inner error: undefined numeral format");
        break;
    }

    if ((_resultHandler->errorState() & ERROR_FIELD) == ERROR_NOERROR)
        _resultHandler->updateCurrentValue(_toString(currentValue()));
}

void ScienceCalculator::initSymbolTable() {
    // binary operaetors
    _symbolTable->registerSymbol("+", new Plus);
    _symbolTable->registerSymbol("-", new BMinus);
    _symbolTable->registerSymbol("*", new Mult);
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



ProgrammerCalculator::ProgrammerCalculator() :
    ExprCalculator(NumeralConverter::valueToDecimalString) {
    _scanner->setLexeme(Lexeme::decimalExprLexeme());
    _parser->setToValue(NumeralConverter::decimalStringToValue);
    initSymbolTable();
    static_cast<TreeParser *>(_parser)->setSymbolTable(_symbolTable);
}

void ProgrammerCalculator::setNumeralFormat(NumeralFormat format) {
    switch (format) {
    case NF_BINARY:
        _scanner->setLexeme(Lexeme::binaryExprLexeme());
        _parser->setToValue(NumeralConverter::binaryStringToValue);
        _toString = NumeralConverter::valueTobinaryString;
        break;
    case NF_OCTAL:
        _scanner->setLexeme(Lexeme::octalExprLexeme());
        _parser->setToValue(NumeralConverter::octalStringToValue);
        _toString = NumeralConverter::valueToOctalString;
        break;
    case NF_DECIMAL:
        _scanner->setLexeme(Lexeme::decimalExprLexeme());
        _parser->setToValue(NumeralConverter::decimalStringToValue);
        _toString = NumeralConverter::valueToDecimalString;
        break;
    case NF_HEX:
        _scanner->setLexeme(Lexeme::hexExprLexeme());
        _parser->setToValue(NumeralConverter::hexStringToValue);
        _toString = NumeralConverter::valueToHexString;
        break;

    case NF_DEGREE: case NF_RADIAN:
    case NF_DEFAULT: case NF_FIXED: case NF_SCIENTIFIC:
        // print prompt information
        break;

    default:
        throw InnerError("inner error: undefined numeral format");
        break;
    }

    if ((_resultHandler->errorState() & ERROR_FIELD) == ERROR_NOERROR)
        _resultHandler->updateCurrentValue(_toString(currentValue()));
}

void ProgrammerCalculator::initSymbolTable() {
    // binary operaetors
    _symbolTable->registerSymbol("+", new Plus);
    _symbolTable->registerSymbol("-", new BMinus);
    _symbolTable->registerSymbol("*", new Mult);
    _symbolTable->registerSymbol("/", new Divide);
    _symbolTable->registerSymbol("Mod", new Modulo);

    _symbolTable->registerSymbol("And", new BitAnd);
    _symbolTable->registerSymbol("Or", new BitOr);
    _symbolTable->registerSymbol("Xor", new BitXor);
    _symbolTable->registerSymbol("Lsh", new Lsh);
    _symbolTable->registerSymbol("Rsh", new Rsh);

    // unary operators
    _symbolTable->registerSymbol("u-", new UMinus);
    _symbolTable->registerSymbol("Not", new BitNot);
}
