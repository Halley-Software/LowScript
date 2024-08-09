#include <format>
#include <map>
#include <string>

#include "lang/scope.h"
#include "lang/commons.h"

namespace lowscript {
namespace lang {

//ReferenceException::ReferenceException(std::string message): reason(message) {};

Scope::Scope(Scope* parent, std::string owner):
    parent_scope(parent),
    belongs_to(owner) {
    variables = std::map<std::string, Entity>();
}

bool Scope::has(std::string name) const {
    return variables.find(name) != variables.end();
}

void Scope::add_entry(std::string name, Entity value) {
    if (has(name))
        throw std::format("Entry '{}' already exists", name);

    variables.insert(std::pair<std::string, Entity>(name, value));
}

Entity Scope::get(std::string name) {
    if (!has(name))
        throw std::format("Entry '{}' does not exists", name);

    return (variables.find(name))->second;
}

} // lang
} // lowscript