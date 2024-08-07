#ifndef UTILS_H
#define UTILS_H

// Determines the length of an array
#define arr_len(array) sizeof(array) / sizeof(array[0])

#ifndef DEBUG
#define dbg(str)
#else
#define dbg(str) std::cout << (str) << std::endl
#endif // DEBUG

#endif // UTILS_H