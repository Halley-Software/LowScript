#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>

#include "lang/scope.h"
#include "lang/commons.h"
#include "lang/expressions.h"

namespace lowscript {
namespace lang {

/**
 * Represents a variable
 */
class LowVar : public Entity {
private:
    // true for constants, false for simple variables
    bool type;
    Expression assign;

public:
    LowVar(std::string name, bool type, Expression assign);
};

/**
 * Modules is a container which stores multiple entities which _implements_ the `Nameable` concept
 */
class LowModule : public Entity {
private:
    // TODO: implements body
    const Scope scope;

public:
    const std::string name;
};

} // lang
} // lowscript

#endif // ENTITIES_H