#ifndef AST_H
#define AST_H

#include <string>

#include "parser/parser.h"

namespace lowscript {
namespace internal {
namespace ast {

class ASTNode {};

/**
 * Represents a numeric value
 */
class NumericNode : ASTNode {
private:
    int value;

public:
    NumericNode(int val);
    int getNum() { return this->value; }
};

/**
 * Represents a single character
 */
class CharNode : ASTNode {
private:
    char character;

public:
    CharNode(char character);
    char getCharacter() { return this->character; }
};

/**
 * Represents a character sequence, also called String xd
 */
class StringNode : ASTNode {
private:
    std::string string;

public:
    StringNode(std::string string);
    std::string getString() { return this->string; }
};

/**
 * Represents an identifier in the source code
 * for example a referenced variable, parameter name, etc
 */
class IdentifierNode : ASTNode {
private:
    std::string symbol;

public:
    IdentifierNode(std::string name);
    std::string getSymbol() { return this->symbol; }
};

class ReferenceNode : ASTNode {
private:
    std::string symbol;

public:
    ReferenceNode(std::string name);
    std::string getSymbol() { return this->symbol; }
};

class AST {
private:
    scan::Parser* p;

public:
    AST(scan::Parser* p);

    void insert(ASTNode node);
};

} // ast
} // internal
} // lowscript

#endif // AST_H