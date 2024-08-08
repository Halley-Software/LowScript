#ifndef SCOPE_H
#define SCOPE_H

#include <exception>
#include <map>
#include <string>

#include "commons.h"

namespace lowscript {
namespace lang {

class ReferenceException : public std::exception {
private:
    std::string reason;

public:
    ReferenceException(std::string message);
};

class Scope {
private:
    Scope* parent_scope;
    const std::string belongs_to;
    std::map<std::string, Entity> variables;

public:

    Scope(Scope* parent_scope, std::string owner);

    /**
     * Checks if `entry` already exists inside `this` object
     */
    bool has(std::string name) const;

    /**
     * Inserts a new entry
     */
    void add_entry(std::string name, Entity entry);

    Entity get(std::string name);
};

} // internal
} // lowscript

#endif // SCOPE_H