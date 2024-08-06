#include <string>

#include "ast.h"
#include "parser/parser.h"

lowscript::internal::ast::NumericNode::NumericNode(int val) : value(val) {}

lowscript::internal::ast::CharNode::CharNode(char character) : character(character) {}

lowscript::internal::ast::StringNode::StringNode(std::string string) : string(string) {}

lowscript::internal::ast::IdentifierNode::IdentifierNode(std::string name) : symbol(name) {}

lowscript::internal::ast::ReferenceNode::ReferenceNode(std::string name) : symbol(name) {}

lowscript::internal::ast::AST::AST(lowscript::internal::scan::Parser* p) : p(p) {
}