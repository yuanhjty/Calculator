#ifndef SCANNER_H
#define SCANNER_H

#include "Util.h"

#include <string>
#include <memory>
#include <regex>


//
// Define class Scanner
//
class Scanner {
private:
    std::shared_ptr<std::string> m_lexemePattern;
    std::shared_ptr<std::string> m_expression;

public:
    void setLexemePattern(const std::shared_ptr<std::string>& lexemePattern);
    void setExpression(const std::shared_ptr<std::string>& infixExpression);
    void scan(const std::shared_ptr<std::string>& input);
};


//
// Implement methods
//
// setLexemePattern
inline void Scanner::setLexemePattern(const std::shared_ptr<std::string>& lexemePattern) {
    m_lexemePattern = lexemePattern;
}

// setExpression
inline void Scanner::setExpression(const std::shared_ptr<std::string>& infixExpression) {
    m_expression = infixExpression;
}


#endif // SCANNER_H
