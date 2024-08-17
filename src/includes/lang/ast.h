#ifndef AST_H
#define AST_H

#include <concepts>
#include <string>
#include <vector>

namespace lowscript {
namespace internal {
namespace ast {

enum class NodeType {
    Function,
    Variable,
    Numeric,
    String,
    Char,
    Reference,

    If,
    While,
    For,

    BinExpr,
    Identifier
};

template<typename T>
concept Nodeable = requires(T t) {
    { t.value } -> std::convertible_to<T>;
};

struct Param {
    std::string name;
    std::string type;
};

class ASTNode {
public:
    NodeType type;
    
    ASTNode(NodeType type);
};

/**
 * Represents a numeric value
 */
class NumericNode : public ASTNode {
public:
    const int num;

    NumericNode(int num);
}; 

class VarNode : public ASTNode {
public:
    const std::string name;
    const bool is_constant;
    const ASTNode expr;

    VarNode(std::string name, bool is_constant, ASTNode expr);
};

/**
 * Represents a single character
 */
class CharNode : public ASTNode {
public:
    const char value;

    CharNode(char value);
};

/**
 * Represents a character sequence, also called String xd
 */
class StringNode : public ASTNode {
public:
    const std::string value;

    StringNode(std::string value);
};

/**
 * Represents an identifier in the source code
 * for example a referenced variable, parameter name, etc
 */
class IdentifierNode : public ASTNode {
public:
    NodeType type;
    const std::string symbol;

    IdentifierNode(std::string symbol);
};

class ReferenceNode : public ASTNode {
public:
    const std::string symbol;

    ReferenceNode(std::string symbol);
};

class BinOpNode : public ASTNode {
public:
    const ASTNode* lhs;
    const ASTNode* rhs;
    const char op;

    BinOpNode(ASTNode* lhs, ASTNode* rhs, char op);
};

class FunctionNode : public ASTNode {
public:
    const std::string name;
    std::vector<struct Param> params;
    std::vector<ASTNode> body;
    const ASTNode return_expr;

    FunctionNode(std::string name, std::vector<struct Param> params, std::vector<ASTNode> body, ASTNode return_expr);
};

class AST {
private:
    std::vector<ASTNode> program;

public:
    AST(std::vector<ASTNode> program);

    void insert(ASTNode node);

    void drop();
};

} // ast
} // internal
} // lowscript

#endif // AST_H