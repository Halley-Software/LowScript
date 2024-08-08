#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>

namespace lowscript {
namespace lang {

class Expression {};

class LowReassignment : Expression {
private:
    Expression lhs;
    Expression rhs;
    const std::string op;
};

/**
 * Represents a function call
 */
class LowCall : Expression {
private:
    const std::string caller;
    const std::string called;
    const std::vector<Expression> args;

public:
    LowCall(std::string caller, std::string called, std::vector<Expression> args);
};

} // lang
} // lowscript

#endif // EXPRESSION_H