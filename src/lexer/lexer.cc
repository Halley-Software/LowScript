#include <cctype>
#include <string>

#include "lexer/lexer-cursor.h"
#include "token.h"
#include "lexer/lexer.h"

#include "utils.h"

lowscript::internal::scan::Lexer::Lexer(std::string source):
    cursor(new LexerCursor(source)),
    current_tok(cursor->current_tok) {
    this->line = 0;

    cursor->next(); // advance to the first position in the source
}

static struct Token create_token(enum TokenType type, std::string content) {
    return {
        type,
        content
    };
}

static struct Token resolve_identifier(std::string identifier) {
    if (KW.find(identifier) != KW.end())
        return create_token(TokenType::Keyword, identifier);

    if (identifier == "instanceof")
        return create_token(TokenType::Operator, identifier);

    return create_token(TokenType::IdentifierName, identifier);
}

struct Token lowscript::internal::scan::Lexer::scan_operational_assign() {
    if (cursor->check_next(Tokens::EQUAL))
        return create_token(TokenType::Operator, std::string {current_tok} + cursor->next());

    return create_token(TokenType::Operator, std::string {current_tok});
}

struct Token lowscript::internal::scan::Lexer::scan_adjust_operator() {
    switch (current_tok) {
      case Tokens::PLUS:
      case Tokens::MINUS: {
        if (cursor->check_next(current_tok))
          return create_token(TokenType::Operator, std::string {current_tok} + cursor->next());
      }
    }

    return scan_operational_assign();
}

struct Token lowscript::internal::scan::Lexer::init_operator_scan() {
    if (current_tok == Tokens::MINUS && cursor->check_next(Tokens::GREATER))
      return create_token(TokenType::Token, std::string {current_tok} + cursor->next());

    return scan_adjust_operator();
}

bool lowscript::internal::scan::Lexer::has_end() {
    return cursor->is_eof();
}

const struct Token lowscript::internal::scan::Lexer::next_token() {
    while (isspace(current_tok))
        cursor->next();

    if (current_tok == '\n' || current_tok == '\r')
        line++;

    // this routine checks for identifiers
    // like variable or function names
    if (isalpha(current_tok)) {
        identifier = "";

        // since other recognizers, tokens, identifiers, etc as of the first character
        // can contains numbers, we accept numbers after the first character too
        // example: var t12345 = 10
        do {
            identifier += current_tok;
        } while (!cursor->is_eof() && isalnum(cursor->next()));

        return resolve_identifier(identifier);
    }

    if (isdigit(current_tok)) {
        numeric_identifier = "";
        bool isFloat = false, isHexadecimalVal = false, isOctal = false, isBinary = false;

        do {
            check_numeric_separators();

            // If reachs a dot, means it is a float, but a dot can not appears in wherever
            if (current_tok == Tokens::DOT) {
                if (isFloat) // if the current lexed number, was already marked as a float
                    throw "Invalid float literal. Only a dot is permitted to separate the tens from the decimals.";

                if (isBinary || isOctal || isHexadecimalVal)
                    throw "Dots are only allowed for numeric floats.";

                isFloat = true;
            }

        } while (!cursor->is_eof() && isdigit(cursor->next()) || current_tok == Tokens::DOT || isalpha(current_tok));

        return create_token(TokenType::NumericLiteral, numeric_identifier);
    }

    switch (current_tok) {
        case Tokens::LBRACE:
        case Tokens::RBRACE:
        case Tokens::LPAREN:
        case Tokens::RPAREN:
        case Tokens::LSQRBR:
        case Tokens::RSQRBR:
        case Tokens::COMMA:
        case Tokens::AMPER:
        case Tokens::EQUAL:
        case Tokens::ESP:
        case Tokens::SEMICOLON:
        case Tokens::EXCLAMATION:
        case Tokens::INTERROGATION: {
            auto tok = create_token(TokenType::Token, std::string {current_tok});

            cursor->next(); // advance and prepare for next call, so the nex token will net be `tok`
            dbg(current_tok);

            return tok;
        } break;

        case Tokens::GREATER:
        case Tokens::LESS: break;
        case Tokens::PLUS:
        case Tokens::MINUS:
        case Tokens::STAR:
        case Tokens::SLASH: {
            if (cursor->check_next(Tokens::SLASH)) {
                do {
                    cursor->next();
                } while (current_tok != '\n' && !cursor->is_eof());
            }

            return init_operator_scan();
        } break;

        case Tokens::QUOTE: {
            identifier = cursor->next();

            if (!cursor->check_next(Tokens::QUOTE)) {
                while (cursor->next() != Tokens::QUOTE)
                    identifier += current_tok;
            }
            return create_token(TokenType::CharLiteral, identifier);
        } break;

        case Tokens::BACKSTICK: {
            identifier = cursor->next();

            if (!cursor->check_next(Tokens::BACKSTICK)) {
                while (cursor->next() != Tokens::BACKSTICK)
                    identifier += current_tok;
            }

            return create_token(TokenType::StringLiteral, identifier);
        } break;

        case Tokens::DQUOTE: {
            if (!cursor->check_next(Tokens::DQUOTE)) {
                identifier = cursor->next();

                while (cursor->next() != Tokens::DQUOTE)
                    identifier += current_tok;
            }
            
            return create_token(TokenType::StringLiteral, identifier);

        } break;

        case Tokens::COLON: {
            if (cursor->check_next(Tokens::COLON)) {
                cursor->next();

                return create_token(TokenType::Operator, "::");
            } else
                return create_token(TokenType::Token, std::string {current_tok});
        } break;

        case Tokens::DOT: {
            if (cursor->check_next(Tokens::DOT)) {
                cursor->next();

                if (current_tok == Tokens::DOT)
                    return create_token(TokenType::Token, "...");

                return create_token(TokenType::Token, "..");
            }
            
            
            cursor->next();
            return create_token(TokenType::Token, std::string {Tokens::DOT});
        } break;
    }

    return create_token(TokenType::Unknown, std::string {current_tok});
} // TODO: FIX RETURN VALUE

void lowscript::internal::scan::Lexer::check_numeric_separators() {
    if (current_tok == UNDERSCORE) {
        if (cursor->check_next(UNDERSCORE)) {}
            //throw new LexingError(this, "Multiple consecutive numeric separators are not permitted")

        /**
        * Using `isHexadecimal` because include all the possibles characters after a numeric separator
        * 
        * TODO: refactor functions name at `src/utils.ts`
        */
        /* if (!isHexadecimal(this.cursor.previous()) || !isHexadecimal(this.cursor.next()))
            throw new LexingError(this, "Numeric separators are now allowed here") */

        next_token();
    }
}