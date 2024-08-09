#ifndef PARSER_CURSOR_H
#define PARSER_CURSOR_H

#include "cursor.h"
#include "lexer/lexer.h"
#include "token.h"

class ParserCursor : lowscript::internal::scan::Cursor<lowscript::internal::scan::Lexer, struct Token> {
public:
    struct Token& current_tok;

    ParserCursor(lowscript::internal::scan::Lexer source);

    /**
     * Returns the next char in the source
     */
    struct Token& next() override;

    /**
     * Returns the previous char in the source
     */
    struct Token& previous() override;

    /**
     * Returns true if the next char in the source is equal to `possibleChar`, false oterhwise
     */
    bool check_next(const struct Token& posisible_next_token) const override;
};

#endif // PARSER_CURSOR_H