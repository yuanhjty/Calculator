#include "Scanner.h"
#include "LexicalSet.h"
#include "ExpressionException.h"



// scan
void Scanner::scan(const std::string &input) {
    m_expression.clear();

    std::regex rSpace("\\s");
    std::regex rLexeme(m_lexemePattern);

    std::sregex_token_iterator pos(input.cbegin(), input.cend(), rLexeme, {-1, 0});
    std::sregex_token_iterator end;

    std::string delimiter;
    std::string token;

    while (pos != end) {
        delimiter = pos++->str();   // delimiter
        if (!delimiter.empty())     // Delimiters should be empty since spaces's included in lexemes.
            throw SymbolError("invalid symbol: " + delimiter);

        token = pos++->str();       // token
        if (!std::regex_match(token, rSpace))   // Ignore space tokens.
            m_expression.append(token + " ");   // Separate non space tokens with a space
    }

    // Remove the space at the end.
    m_expression.pop_back();
}
