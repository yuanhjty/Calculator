#include "Parser.h"


// destructor
Parser::~Parser() {
    if (m_expressionTree) delete m_expressionTree;
}

// parse
void Parser::parse(const std::string &infixExpression) {
    m_infixExpression = infixExpression;
}
