#ifndef LEXER_H
#define LEXER_H

#include <cstddef>
#include <string>
#include <vector>

#include "lexer-cursor.h"
#include "token.h"

namespace lowscript {
namespace internal {
namespace scan {
/**
 * The lexer class contains basic utilities to iterate over the source
 */
class Lexer {
private:
    size_t line;
    LexerCursor* cursor;
    size_t tokens;

    std::string identifier;
    std::string numeric_identifier;

    /**
     * Ignore the numeric separators (underscores)
     * 
     * @throws throws an error if there are multiple consecutive numeric separators or if a separator is before or after a dot
     */
    void check_numeric_separators();

    struct Token init_operator_scan();
    struct Token scan_adjust_operator();
    struct Token scan_operational_assign();

public:
    char& current_tok;

    Lexer(std::string source);

    /**
     * Reset to default values the members of the `this` object
     * This is used to scan other files, for example whe using `import` statements
     */
    void restart(std::string new_src);

    /**
     * Analize the source and returns the tokens encountered on that source
     */
    std::vector<struct Token> collect();

    /**
     * Returns the number of tokens that has been readed
     */
    size_t length() const;

    /**
     * Performs that the cursor advance one position in the source
     * returning a `Token`
     */
    const struct Token next_token();

    /**
     * Calls `Cursor::is_eof()` to checks if all the source was scanned
     */
    bool has_end();
};
} // scan
} // internal

} // lowscript

#endif // LEXER_H
