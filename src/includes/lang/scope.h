#ifndef SCOPE_H
#define SCOPE_H

#include <set>
#include <string>

#include "lang/expressions.h"

namespace lowscript {
namespace internal {
template<typename T>
concept Nameable = T::name;

template<Nameable T>
class Scope {
private:
    std::set<std::string, lang::Expression> variables;
    Scope* parent_scope;
    std::string belongs_to;

public:
    Scope(Scope* parent_scope, std::string owner);

    bool add_entry(std::string name, T value);
};
} // internal
} // lowscript


#endif // SCOPE_H