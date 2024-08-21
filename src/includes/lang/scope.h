#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <memory>
#include <string>
#include <exception>

namespace lowscript {
namespace lang {

/**
 * To avoid the issue of recursive inclusion when using the #include directive,
 * we will forward declare the `Entity` class,
 * thus avoiding the need to include the file that declares it.
 */
class Entity;

// Entity contains `name` as instance var
// so it can be consider a _Nameable_
using Nameable = Entity;

class Scope {
private:
    std::unique_ptr<Scope> parent_scope;
    const std::string belongs_to;
    std::map<std::string, Nameable> variables;

    const Nameable* search(std::string name) const;

public:

    Scope(std::unique_ptr<Scope> parent_scope, std::string owner);

    /**
     * Inserts a new entry
     */
    void add_entry(std::string name, Nameable entry);

    /**
     * Checks if `entry` already exists inside `this` object
     */
    bool has(std::string name) const;

    /**
     * Returns a pointer to the nameable entity which as `name`
     */
    const Nameable* get(std::string name) const;
};

class ReferenceException : public std::exception {
private:
    const char* reason;

public:
    explicit ReferenceException(const char* message);

    const char* what() const noexcept override;
};

} // internal
} // lowscript

#endif // SCOPE_H