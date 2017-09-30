#include "Parser.h"


// destructor
Parser::~Parser() {
    if (m_expressionTree) delete m_expressionTree;
}

// parse
void Parser::parse() {
    setExpressionTree(generateExpressionTree());
    updateExpression();
}

// generateExpressionTree
ExpressionTree* Parser::generateExpressionTree() {
    return nullptr;
}

