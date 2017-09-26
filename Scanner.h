#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <memory>

class Scanner
{
protected:
    std::shared_ptr<std::string> m_expression;

public:
    virtual ~Scanner() = default;
    virtual void init();
    virtual void scan(const std::string& input);

    std::shared_ptr<std::string> getExpression() const;

protected:
    void setExpression(const std::shared_ptr<std::string>& expression);
};


inline std::shared_ptr<std::string> Scanner::getExpression() const {
    return m_expression;
}

inline void Scanner::setExpression(const std::shared_ptr<std::string>& expression) {
    m_expression = expression;
}

#endif // SCANNER_H
