#include <string>

#include "lexer/lexer-cursor.h"

namespace lowscript {
namespace internal {
namespace scan {
LexerCursor::LexerCursor(std::string source):
    current_tok(source.at(0)) {
    this->source = source;
    this->source_len = source.length();
    this->position = 0;
};

void LexerCursor::consume() {
    position++;
}

const char& LexerCursor::next() {
    return (current_tok = source.at(position++));
}

const char& LexerCursor::previous() {
    return source[position];
}

bool LexerCursor::is_eof() const {
    return current_tok == source.back();
}

bool LexerCursor::check_next(const char& posisible_next_token) const {
    return source[position + 1] == posisible_next_token;
}

} // scan
} // internal
} // lowscript