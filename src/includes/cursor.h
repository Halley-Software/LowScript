#ifndef CURSOR_H
#define CURSOR_H

#include <concepts>
#include <cstddef>

namespace lowscript {
namespace internal {
namespace scan {
template<typename T>
concept Lengthable = requires(T t) {
    { t.length() } -> std::convertible_to<std::size_t>;
};

template<Lengthable SRCT, typename T>
class Cursor {
protected:
    SRCT source;
    size_t source_len;
    size_t position;

public:
    T current_tok;

    /**
     * Returns the next char in the source
     */
    virtual const T& next() = 0;

    /**
     * Returns the previous char in the source
     */
    virtual const T& previous() = 0;

    /**
     * Checks if `current_tok` is equal to the last character in the source
     */
    virtual bool is_eof() const = 0;

    /**
     * Returns true if the next char in the source is equal to `possibleChar`, false oterhwise
     */
    virtual bool check_next(const T& posisible_next_token) const = 0;
};
} // scan
} // internal

} // lowscript

#endif // CURSOR_H