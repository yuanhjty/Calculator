#ifndef SCIENTIFIC_CALCULATOR_H
#define SCIENTIFIC_CALCULATOR_H


#include "Calculator.h"
#include "Expression.h"
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

protected:
    void configureScanner();
    void configureParser();

public:
    void scanInput(const std::shared_ptr<std::string>& input) override;
    void evaluate() override;
    std::string showResult() const override;
    std::string showHistory(int index) const override;  // index = -1, -2, -3, ...

protected:
    void configureLexemePattern(const std::string& lexemePattern) override;
    void updateResult(const std::string& value) override;
    std::string formatResult(const std::pair<std::string, std::string>& result) const;
};


//
// override methods
//
// scanInput
inline void ScientificCalculator::scanInput(const std::shared_ptr<std::string>& input) {
    m_scanner->scan(input);
}

// showResult
inline std::string ScientificCalculator::showResult() const {
    return formatResult(*m_result);
}


#endif // SCIENTIFIC_CALCULATOR_H
