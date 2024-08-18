#ifndef UTILS_H
#define UTILS_H

#include <string>

// Determines the length of an array
#define arr_len(array) sizeof(array) / sizeof(array[0])

/**
 * Returns a new string containing the 'c' char as content
 */
extern std::string char_to_str(const char& c);

#ifdef DEBUG
  #include <iostream>

  #define dbg(str) std::cout << str << std::endl
  #define curtt(str) std::cout << "Current tok -> " + std::string(1, str) << std::endl
#else
  #define dbg(str)
  #define curtt(str)
#endif // DEBUG

#endif // UTILS_H