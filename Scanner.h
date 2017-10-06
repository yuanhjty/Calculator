#ifndef SCANNER_H
#define SCANNER_H


#include <string>
#include <regex>


// The class Scanner
class Scanner {
private:
    std::string m_lexemePattern;
    std::string m_expression;

public:
    void setLexemePattern(const std::string &lexemePattern);
    std::string getExpression() const;
    void scan(const std::string &input);
    void reset();
};


// setLexemePattern
inline void Scanner::setLexemePattern(const std::string &lexemePattern) {
    m_lexemePattern = lexemePattern;
}

// getExpression
inline std::string Scanner::getExpression() const {
    return m_expression;
}

inline void Scanner::reset() {
    m_expression.clear();
}


#endif // SCANNER_H
