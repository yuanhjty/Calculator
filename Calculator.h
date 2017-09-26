#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Scanner.h"
#include "Parser.h"
#include "Expression.h"

#include <string>
#include <memory>

///
/// \brief The Calculator class
///
class Calculator
{
protected:
    std::string m_result;

public:
    virtual ~Calculator() = default;

    virtual void init() = 0;
    virtual std::string scanInput(const std::string& input) = 0;
    virtual void evaluate() = 0;
    virtual void reset() = 0;

    std::string getResult() const {
        return m_result;
    }
};


///
/// \brief The ScientificCalculator class
///
class ScientificCalculator : public Calculator
{
private:
    std::shared_ptr<Scanner> m_scanner;
    std::shared_ptr<Parser> m_parser;
    std::shared_ptr<Expression> m_expression;
    std::string m_infixExpression;

public:
    ScientificCalculator(
            const std::shared_ptr<Scanner>& scanner,
            const std::shared_ptr<Parser>& parser,
            const std::shared_ptr<Expression>& expression
            );

    // setter
    void setScanner(std::shared_ptr<Scanner> scanner) {
        m_scanner = scanner;
    }

    void setParser(std::shared_ptr<Parser> parser) {
        m_parser = parser;
    }

    void setExpression(std::shared_ptr<Expression> expression) {
        m_expression = expression;
    }

    // initializer
    void init() override;

    // functional metheds
    void scanInput(const std::string& input) override {
        m_infixExpression = m_scanner->scan(input);
    }

    void evaluate() override;

    void reset() override {
        m_infixExpression.clear();
    }

private:
    void buildExpression() {
        m_expression = m_parser->parse(m_infixExpression);
    }
};


///
/// \brief The ConversionCalculator class
///
class ConversionCalculator : public Calculator
{
public:
    void init();
    void evaluate() override;
};


#endif // CALCULATOR_H
