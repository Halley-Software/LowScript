#ifndef COMMONS_H
#define COMMONS_H

#include <string>

namespace lowscript {
namespace lang {

class Entity {
public:
    const std::string symbol;

    Entity(std::string name);
};


} // lang
} // lowscript

#endif