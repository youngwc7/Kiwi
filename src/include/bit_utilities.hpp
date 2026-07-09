#include <cstdint>

inline int getLSB(uint64_t bb)
{
    return __builtin_ctzll(bb);  // count trailing zeros = index of lowest set bit
}