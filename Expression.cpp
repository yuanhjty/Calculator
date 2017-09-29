#include "Expression.h"
#include "Util.h"


Expression::~Expression() {
    if (m_expressionTree) delete m_expressionTree;
}

std::string Expression::evaluate() {
    return Util::toString(m_expressionTree->evaluate());
}
