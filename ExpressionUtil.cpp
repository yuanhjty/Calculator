#include <algorithm>
#include "ExpressionUtil.h"


extern const std::vector<std::string> rightAssociativeOperators = {
    "u-", "sin", "cos", "tan", "asin", "acos", "atan", "^"
};

extern const std::vector<std::string> unaryOperators = {
    "u-", "sin", "cos", "tan", "asin", "acos", "atan"
};

extern const std::vector<std::string> binaryOperators = {
    "+", "-", "*", "/", "^", "="
};
// binaryOperators = { "+", "-", "*", "/", "%", "^", "=" };

static std::vector<std::string> operTmp;
static std::vector<std::string>::iterator it;

extern const std::vector<std::string> operators = {
    "+", "-", "*", "/", "%", "^", "=",
    "u-", "sin", "cos", "tan", "asin", "acos", "atan"
};

static std::string operandPattern = "\\d?\\.?\\d+|\\d+\\.?\\d?";
std::regex operandRegex(operandPattern);

extern const std::map<std::string, int> operatorPriority = {
    {"(",   0}, {"=",   1}, {"+",    4}, {"-",    4}, {"*",    5},
    {"/",   5}, /*{"%",5},*/ {"^",    6}, {"u-",   7}, {"sin",  7},
    {"cos", 7}, {"tan", 7}, {"asin", 7}, {"acos", 7}, {"atan", 7}
};

extern const std::map<std::string, OP> binaryOperatorsMap = {
    {"+", OP::PLUS}, {"-", OP::B_MIN}, {"*", OP::MUL},
    {"/", OP::DIV }, /*{"%",OP::MOD},*/ {"^", OP::POW}
};

extern const std::map<std::string, OP> unaryOperatorsMap = {
    {"u-",  OP::U_MIN}, {"sin",  OP::SIN }, {"cos",  OP::COS },
    {"tan", OP::TAN  }, {"asin", OP::ASIN}, {"acos", OP::ACOS},
    {"atan", OP::ATAN}
};
