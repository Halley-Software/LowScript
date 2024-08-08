#include "lang/commons.h"
#include "lang/expressions.h"
#include "lang/scope.h"
#include "lang/values.h"

namespace lowscript {
namespace lang {

template<typename T>
class LowFunction : public Entity, Expression, LowObject {
private:
    const std::vector<Entity> body;
    const Scope scope;
    Expression return_expr;

public:
    LowFunction(std::string name, std::vector<Entity> body, Scope scope, Expression return_expr);
};

} // lang
} // lowscript