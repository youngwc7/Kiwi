#ifndef BIT_UTILITIES_HPP
#define BIT_UTILITIES_HPP

#include <cstdint>
#include <cassert>

/**
 * @brief return bit index of LSB.
 * @param mask bits to observe placement of LSB. CANNOT BE 0.
 * @return integer from 0-63
 */ 
inline int getLSB(uint64_t mask)
{
    assert(mask > 0 && "bit_utilities::getLSB(): input > 0 condition not met");
    
    return __builtin_ctzll(mask);  // count trailing zeros = index of lowest set bit
}

/**
 * @brief return bit index of LSB, AS WELL as removing LSB from bit mask.
 * @param mask bit mask to be modified and return LSB index. bit mask CANNOT BE 0.
 * @return integer from 0-63
 */ 
inline int popLSB(uint64_t& mask)
{
    assert(mask > 0 && "bit_utilities::popLSB(): input > 0 condition not met");
    
    int lsbIndex = __builtin_ctzll(mask);

    /* eliminate LSB */
    mask &= (mask - 1);

    return lsbIndex;
}

#endif /* BIT_UTILITIES_HPP */