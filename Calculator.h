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
    virtual void scanInput(const std::string& input) = 0;
    virtual void evaluate() = 0;
    virtual void reset() = 0;

    std::string getResult() const;
    virtual std::string getMessage() const = 0;
};

inline std::string Calculator::getResult() const {
    return m_result;
}


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
    ScientificCalculator() = default;
    ScientificCalculator(
            const std::shared_ptr<Scanner>& scanner,
            const std::shared_ptr<Parser>& parser,
            const std::shared_ptr<Expression>& expression
            );

    // setter
    void setScanner(std::shared_ptr<Scanner> scanner);
    void setParser(std::shared_ptr<Parser> parser);
    void setExpression(std::shared_ptr<Expression> expression);

    // initializer
    void init() override;

    // functional metheds
    void scanInput(const std::string& input) override;
    void evaluate() override;
    void reset() override;

    // send some messages to users when necessary
    std::string getMessage() const override;

private:
    void buildExpression();
};

inline void ScientificCalculator::setScanner(std::shared_ptr<Scanner> scanner) {
    m_scanner = scanner;
}

inline void ScientificCalculator::setParser(std::shared_ptr<Parser> parser) {
    m_parser = parser;
}

inline void ScientificCalculator::setExpression(std::shared_ptr<Expression> expression) {
    m_expression = expression;
}

inline void ScientificCalculator::scanInput(const std::string &input) {
    m_infixExpression = m_scanner->scan(input);
}

inline void ScientificCalculator::reset() {
    m_infixExpression.clear();
}

inline std::string ScientificCalculator::getMessage() const {
    return m_infixExpression;
}

inline void ScientificCalculator::buildExpression() {
    m_expression = m_parser->parse(m_infixExpression);
}


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
