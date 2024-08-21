#ifndef VALUES_H
#define VALUES_H

#include <string>

#include "lang/commons.h"
#include "lang/entities/entities.h"

namespace lowscript {
namespace lang {

class LowReassignment : public LowValue {
private:
    LowVar lhs;
    LowValue rhs;
    const std::string op;
};

/**
 * Represents a function call
 */
class LowCall : public LowValue {
private:
    const std::string caller;
    const std::string called;
    const std::vector<LowValue> args;

public:
    LowCall(std::string caller, std::string called, std::vector<LowValue> args);
};


} // lang
} // lowscript

#endif // VALUES_H
