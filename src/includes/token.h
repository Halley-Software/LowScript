#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>

/**
 * Represents a single token which has a special meaning else than a token that made up an identifier or number
 */
enum Tokens {
  LPAREN        = '(',
  RPAREN        = ')',
  LBRACE        = '{',
  RBRACE        = '}',
  LSQRBR        = '[',
  RSQRBR        = ']',
  COMMA         = ',',
  DQUOTE        = '"',
  QUOTE         = '\'',
  BACKSTICK     = '`',
  PLUS          = '+',
  MINUS         = '-',
  STAR          = '*',
  SLASH         = '/',
  PERCEN        = '%',
  LESS          = '<',
  GREATER       = '>',
  DOT           = '.',
  AMPER         = '&',
  EQUAL         = '=',
  ESP           = '~',
  COLON         = ':',
  SEMICOLON     = ';',
  EXCLAMATION   = '!',
  INTERROGATION = '?',
  UNDERSCORE    = '_',
};

enum Keywords {
  FN,
  VAR,
  CONST,
  RETURN,
  IMPORT,
  FROM,
  EXPORT,
  CLASS,
  THIS,
  SUPER,
  TYPE,
  INTERFACE,
  ENUM,
  EXTENDS,
  IMPLEMENTS,
  MODULE,
  FOR,
  WHILE,
  DO,
  BREAK,
  SKIP,
  IF,
  ELSE,
  ELIF,
  MATCH,
  SWITCH,
  CASE,
  DEFAULT,
  IN,
  OF,
  AND,
  OR,
  NOT,
  TRY,
  CATCH,
  AS,
  CONSTRUCTOR,
  DESTRUCTOR,
  NEW,
  DROP,
  PUBLIC,
  PRIVATE,
  PROTECTED,
  STATIC,
  OVERRIDE,
  SETTER,
  GETTER,
  ASYNC,
  AWAIT
};

/**
 * Possible type of tokens for LowScript
 * Them represents the different type of tokens formed by reading a source code file
 *
 * For example, an `IdentifierName` is used to recognize a variable / function reference
 */
enum TokenType {
  // generic tokens
  Unknown        = -1,
  IdentifierName = 0,
  Statement      = 1,
  Keyword        = 2,
  Operator       = 3,
  Token          = 4,

  // tokens that belongs to an primitive representation of a value
  NumericLiteral = 5,
  FloatLiteral   = 6,
  BinaryLiteral  = 7,
  OctalLiteral   = 8,
  HexaLiteral    = 9,
  CharLiteral    = 10,
  StringLiteral  = 11,
  TemplateString = 12,
};

extern const std::map<std::string, enum Keywords> KW;

/**
 * Represents the main struct that `Parser` handles
 * A token consists of two members
 * which the type of the token, e.g: `IdentifierName`, `Numeric`, `Statement`, etc
 * and the content, which is the char or string value of the token
 */
struct Token {
  TokenType type;
  std::string content;
};

#endif // TOKEN_H