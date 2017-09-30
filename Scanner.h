#ifndef SCANNER_H
#define SCANNER_H

#include "Util.h"

#include <string>
#include <memory>
#include <regex>


// The class Scanner
class Scanner {
private:
    StringPtr m_lexemePattern;
    StringPtr m_scannedExpression;

public:
    void setLexemePattern(const StringPtr& lexemePattern);
    void setScannedExpression(const StringPtr& infixExpression);
    void scan(const StringPtr& input);
};


// setLexemePattern
inline void Scanner::setLexemePattern(const StringPtr& lexemePattern) {
    m_lexemePattern = lexemePattern;
}

// setExpression
inline void Scanner::setScannedExpression(const StringPtr& infixExpression) {
    m_scannedExpression = infixExpression;
}


#endif // SCANNER_H
