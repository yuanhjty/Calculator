#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H


// The class ExpressionTree
class ExpressionTree {
public:
    virtual ~ExpressionTree() = default;
    virtual double evaluate() = 0;
};


#endif // EXPRESSION_TREE_H
