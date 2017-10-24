#include "Scanner.h"
#include "CalcError.h"


void Scanner::scan(const std::string &userExpression) {
    _formattedExpression.clear();

    if (userExpression.empty())
        return;

    std::sregex_token_iterator pos(userExpression.cbegin(),
                                   userExpression.cend(),
                                   _lexeme, {-1, 0});
    std::sregex_token_iterator end;

    std::string delimiter;
    std::string token;

    while (pos != end) {
        delimiter = pos++->str();   // delimiter
        if (!delimiter.empty())     // Delimiters should be empty since spaces's included in lexemes.
            throw SymbolError("invalid symbol: " + delimiter, REPAIR_IGNORE);

        token = pos++->str();       // token
        if (" " != token && "\t" != token)          // Ignore space tokens.
            _formattedExpression.append(token + " ");  // Separate non-space tokens with a space
    }

    // Remove the space at the end.
    _formattedExpression.pop_back();
}
