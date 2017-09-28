#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <string>
#include <vector>
#include <memory>
#include <utility>


//
// Define class Calculator.
//
class Calculator {
protected:
    std::shared_ptr<std::string> m_lexemePattern;
    std::shared_ptr<std::string> m_scannedExpression;
    std::shared_ptr<std::string> m_validExpression;
    std::shared_ptr<std::string> m_result;
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> m_history;

public:
    Calculator();
    virtual ~Calculator() = default;
    void updateValidExpression();
    void updateHistory();
    void clear();
    void reset();

    std::shared_ptr<std::string> getValidExpression() const;
    std::shared_ptr<std::string> getResult() const;
    std::pair<std::string, std::string> getHistory(int index);   // index = -1, -2, -3, ...

public:
    virtual void scanInput(const std::shared_ptr<std::string>& input) = 0;
    virtual void evaluate() = 0;

protected:
    virtual void configureLexemePattern(const std::string& lexemePattern) = 0;
    virtual void updateResult() = 0;
};


//
// Implement public methods.
//
// updataValidExpression
inline void Calculator::updateValidExpression() {
    m_validExpression = m_scannedExpression;
}

// updataHistory
inline void Calculator::updateHistory() {
    m_history->push_back(std::make_pair(*m_validExpression, *m_result));
}

// getValidExpression
inline std::shared_ptr<std::string> Calculator::getValidExpression() const {
    return m_validExpression;
}

// getResult
inline std::shared_ptr<std::string> Calculator::getResult() const {
    return m_result;
}


#endif // CALCULATOR_H
