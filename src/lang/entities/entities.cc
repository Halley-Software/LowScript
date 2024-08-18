#include "lang/commons.h"
#include "lang/expressions.h"
#include "lang/entities/entities.h"

namespace lowscript {
namespace lang {

Entity::Entity(std::string name): symbol(name) {}

LowVar::LowVar(std::string name, bool type, Expression assign):
    Entity(name),
    type(type),
    assign(assign) {}

} // lang
} // lowscript