#include <string>

#include "lang/scope.h"
#include "lang/expressions.h"

namespace lowscript {
namespace lang {

//ReferenceException::ReferenceException(std::string message): reason(message) {};

Scope::Scope(Scope* parent, std::string owner):
    parent_scope(parent),
    belongs_to(owner) {
        variables = std::set<std::string, lang::Expression>();
    }

lowscript::internal::Scope::add_entry() {
    
}