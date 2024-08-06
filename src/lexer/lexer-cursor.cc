#include <string>

#include "lexer/lexer-cursor.h"

internal::scan::LexerCursor::LexerCursor(std::string source) : current_tok(source.at(0)) {
    this->source = source;
    this->source_len = source.length();
    this->position = 0;
};

const char& internal::scan::LexerCursor::next() {
    return (current_tok = source.at(position++));
}

const char& internal::scan::LexerCursor::previous() {
    return source[position];
}

bool internal::scan::LexerCursor::is_eof() const {
    return current_tok == source.back();
}

bool internal::scan::LexerCursor::check_next(char posisible_next_token) const {
    return source[position + 1] == posisible_next_token;
}