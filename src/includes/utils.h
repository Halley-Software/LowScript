#ifndef UTILS_H
#define UTILS_H

// Determines the length of an array
#define arr_len(array) sizeof(array) / sizeof(array[0])

#ifndef DEBUG
#define dbg(str)

#define curtt(str)
#else
#include <iostream>
#include <string>
#define dbg(str) std::cout << str << std::endl

#define curtt(str) std::cout << "Current tok -> " + std::string { str } << std::endl
#endif // DEBUG

#endif // UTILS_H