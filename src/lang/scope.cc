#include <format>
#include <memory>
#include <string>
#include <utility>

#include "lang/scope.h"

// The inclusion of commons helps the compiler to find the full declaration of `Entity` class
#include "lang/commons.h"

namespace lowscript {
namespace lang {

using Nameable = Entity;

Scope::Scope(std::unique_ptr<Scope> parent, std::string owner):
    parent_scope(std::move(parent)),
    belongs_to(owner),
    variables(std::map<std::string, Nameable>()) {}

void Scope::add_entry(std::string name, Nameable value) {
    if (has(name))
        throw std::format("Entry '{}' already exists", name);

    variables.insert(std::pair<std::string, Nameable>(name, value));
}

const Nameable* Scope::search(std::string name) const {
    std::map<std::string, Nameable>::const_iterator entry = variables.find(name);

    if (entry != variables.end())
        return &entry->second;
    else if (parent_scope != nullptr)
        return search(name);
    else
        return nullptr;
}

bool Scope::has(std::string name) const {
    const Nameable* entry = search(name);

    return entry == nullptr ? false : true;
}

const Nameable* Scope::get(std::string name) const {
    return search(name);
}

// ----- ReferenceException what redefinition -----
ReferenceException::ReferenceException(const char* message): reason(message) {}

const char* ReferenceException::what() const noexcept {
    return reason;
}

} // lang
} // lowscript