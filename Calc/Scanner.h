#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <regex>


class Scanner {
public:
    void scan(const std::string &userExpression);
    void setLexeme(const std::string &lexemePattern);
    std::string formattedExpression() const;

private:
    std::string _formattedExpression;
    std::regex _lexeme;
};


inline void Scanner::setLexeme(const std::string &lexemePattern) {
    _lexeme = lexemePattern;
}

inline std::string Scanner::formattedExpression() const {
    return _formattedExpression;
}

#endif // SCANNER_H
