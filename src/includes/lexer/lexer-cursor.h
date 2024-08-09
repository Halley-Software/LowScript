#ifndef LEXER_CURSOR_H
#define LEXER_CURSOR_H

#include <string>

#include "cursor.h"

namespace lowscript {
namespace internal {
namespace scan {

class LexerCursor : scan::Cursor<std::string, char> {

public:
    char& current_tok;

    LexerCursor(std::string source);

    /**
     * Returns the next char in the source
     */
    const char& next() override;

    /**
     * Returns the previous char in the source
     */
    const char& previous() override;

    /**
     * Checks if `current_tok` is equal to the last character in the source
     */
    bool is_eof() const override;

    /**
     * Returns true if the next char in the source is equal to `possibleChar`, false oterhwise
     * 
     * This method deoes not advance the cursor to the next position
     */
    bool check_next(char posisible_next_token) const override;
};

} // scan
} // internal

} // lowscript

#endif // LEXER_CURSOR_H