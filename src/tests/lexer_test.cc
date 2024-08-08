#include <iostream>
#include <ostream>
#include <string>

#include "lexer/lexer.h"

// only for testing purposes, the rest of the project doesnt use `using` nor `using namespace`
using namespace lowscript::internal::scan;

static std::string advance(Lexer* lex) {
    return lex->next_token().content;
}

int main() {
    std::string source =
    "fn main() { console.log(\"bruh\") }";

    Lexer lex = Lexer(source);

    

    while (!lex.has_end()) {
        std::cout << advance(&lex) << std::endl;
    }

    return 0;
}