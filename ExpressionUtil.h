#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
#include <regex>
#include <exception>


enum class OP {
    PLUS,  B_MIN, MUL, DIV, /*MOD,*/  POW,
    U_MIN, SIN,   COS, TAN, ASIN, ACOS, ATAN
};


extern const std::vector<std::string> unaryOperators;
extern const std::vector<std::string> binaryOperators;
extern const std::vector<std::string> operators;
extern const std::map<std::string, int> operatorPriority;
extern std::regex operandRegex;
extern const std::map<std::string, OP> binaryOperatorsMap;
extern const std::map<std::string, OP> unaryOperatorsMap;


inline bool isUnaryOperator(const std::string& token) {
    return std::find(unaryOperators.cbegin(), unaryOperators.cend(),
                     token) != unaryOperators.cend();
}

inline bool isBinaryOperator(const std::string& token) {
    return std::find(binaryOperators.cbegin(), binaryOperators.cend(),
                     token) != binaryOperators.cend();
}

inline bool isOperator(const std::string& token) {
    return isUnaryOperator(token) || isBinaryOperator(token);
}

inline bool isOperand(const std::string& token) {
    return std::regex_match(token, operandRegex);
}

inline bool isPrior(const std::string& token1, const std::string& token2) {
    return operatorPriority.find(token1)->second >
            operatorPriority.find(token2)->second;
}

#endif // CONSTANTS_H
