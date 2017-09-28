#ifndef SCIENTIFIC_CALCULATOR_H
#define SCIENTIFIC_CALCULATOR_H


#include "Calculator.h"
#include "ExpressionTree.h"
#include "Scanner.h"
#include "Parser.h"
#include "Util.h"

#include <string>
#include <memory>


//
// Define class ScientificCalculator
//
class ScientificCalculator : public Calculator {
protected:
    std::shared_ptr<Expression> m_Expression;
    std::shared_ptr<Scanner> m_scanner;
    std::shared_ptr<Parser> m_parser;

public:
    ScientificCalculator();
    void scanInput(const std::shared_ptr<std::string>& input) override;
    void evaluate() override;

protected:
    void configureLexemePattern(const std::string& lexemePattern) override;
    void configureScanner();
    void configureParser();
    void updateResult() override;
};


//
// Implement methods
//
inline void ScientificCalculator::scanInput(const std::shared_ptr<std::string>& input) {
    m_scanner->scan(input);
}

// updateResult
inline void ScientificCalculator::updateResult() {
    *m_result = Util::toString(m_Expression->value());
}


#endif // SCIENTIFIC_CALCULATOR_H
