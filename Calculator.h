#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Scanner.h"
#include "Parser.h"
#include "Expression.h"

#include <string>
#include <memory>


/////////////////////////////////
// The Calculator class
class Calculator
{
public:
    virtual ~Calculator() = default;

    virtual void init() = 0;
    virtual void scanInput(const std::string& input) = 0;
    virtual void evaluate() = 0;
    virtual void reset() = 0;

    virtual std::shared_ptr<std::string> getResult() const = 0;
    virtual std::shared_ptr<std::string> getMessage() const = 0;
};


/////////////////////////////////
// The ScientificCalculator class
class ScientificCalculator : public Calculator
{
private:
    std::shared_ptr<Scanner> m_scanner;
    std::shared_ptr<Parser> m_parser;
    std::shared_ptr<Expression> m_expression;
    std::shared_ptr<std::string> m_infixExpression;

private:
    // set members
    void setScanner(const std::shared_ptr<Scanner>& scanner);
    void setParser(const std::shared_ptr<Parser>& parser);
    void setInfixExpression(const std::shared_ptr<std::string>& infixExpression);
    void setExpression(const std::shared_ptr<Expression>& expression);

public:
    // initialize object
    void init() override;

    // functional metheds
    void scanInput(const std::string& input) override;
    void evaluate() override;
    void reset() override;

    // get result and message
    std::shared_ptr<std::string> getMessage() const override;
    std::shared_ptr<std::string> getResult() const override;
};


// set members
inline void ScientificCalculator::setScanner(
        const std::shared_ptr<Scanner>& scanner) {
    m_scanner = scanner;
}

inline void ScientificCalculator::setParser(
        const std::shared_ptr<Parser>& parser) {
    m_parser = parser;
}

inline void ScientificCalculator::setInfixExpression(
        const std::shared_ptr<std::string> &infixExpression) {
    m_infixExpression = infixExpression;
}

inline void ScientificCalculator::setExpression(
        const std::shared_ptr<Expression>& expression) {
    m_expression = expression;
}


// reset infix expression
inline void ScientificCalculator::reset() {
    m_infixExpression->clear();
}


// get message
inline std::shared_ptr<std::string> ScientificCalculator::getMessage() const {
    return m_infixExpression;
}

// get result
inline std::shared_ptr<std::string> ScientificCalculator::getResult() const {
    return m_expression->showValue();
}


#endif // CALCULATOR_H
