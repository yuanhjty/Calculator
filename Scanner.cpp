#include "Scanner.h"

#include <exception>


// scan
void Scanner::scan(const std::string &input) {
    std::regex rLexeme(m_lexemePattern);
    std::regex rSpace("//s");

    std::sregex_token_iterator pos(input.cbegin(), input.cend(), rLexeme, {-1, 0});
    std::sregex_token_iterator end;

    std::string delimiter;
    std::string token;

    while (pos != end) {
        delimiter = pos++->str();   // delimiter
        if (!token.empty())         // Delimiters should be empty since spaces's included in lexemes.
            throw std::invalid_argument("Invalid Symbol: " + token);

        token = pos++->str();       // token
        if (!std::regex_match(token, rSpace))   // Ignore space tokens.
            m_expression.append(token + " ");   // Separate non space tokens with a space
    }
}
