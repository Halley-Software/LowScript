#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "lang/scope.h"
#include "lang/entities.h"
#include "lang/expressions.h"

using namespace std;
using namespace lowscript::lang;

int main() {
    Scope s = Scope(nullptr, "main");

    LowVar new_named = LowVar("myVar", true, Expression{});
    LowVar new_named2 = LowVar("myVar2", false, Expression{});

    try {
        s.add_entry(new_named.symbol, new_named);
    } catch (const string message) {
        fprintf(stderr, "Error declaring variable: %s\n", message.c_str());
        exit(1);
    }

    try {
        std::cout << s.get(new_named.symbol).symbol << std::endl;
        std::cout << s.get(new_named2.symbol).symbol << std::endl;
    } catch (const string message) {
        fprintf(stderr, "Reference error: %s\n", message.c_str());
        exit(1);
    }

    return 0;
}