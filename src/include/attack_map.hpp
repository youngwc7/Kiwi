#ifndef ATTACK_MAP_HPP
#define ATTACK_MAP_HPP

/**
 * This file will store pseudo legal moves for knights, pawns, kings
 * Format will be an array of uint64_t bitboards
 */

#include "constants.hpp"

/** 
 * Once again, credit to MaksimKorzh 
 * https://github.com/maksimKorzh/chess_programming
 */
#include "magic_constants.hpp"

struct AttackMap
{
    inline static uint64_t pawnAttackMap[NUM_COLORS][NUM_SQUARES] = {};
    inline static uint64_t knightAttackMap[NUM_SQUARES] = {};
    inline static uint64_t kingAttackMap[NUM_SQUARES] = {};

    inline static uint64_t rayN[NUM_SQUARES] = {};
    inline static uint64_t rayS[NUM_SQUARES] = {};
    inline static uint64_t rayE[NUM_SQUARES] = {};
    inline static uint64_t rayW[NUM_SQUARES] = {};

    inline static uint64_t rayNE[NUM_SQUARES] = {};
    inline static uint64_t rayNW[NUM_SQUARES] = {};
    inline static uint64_t raySE[NUM_SQUARES] = {};
    inline static uint64_t raySW[NUM_SQUARES] = {};

    /** 
     * @brief acts as the constructor for this struct. Initializes members.
     */
    static void initAttackMap();
    
    static void printBitboard(uint64_t bb);
    
private:
    
    /**
     * Helper for initAttackMap()
     */
    static void initPawnAttacks();

    /**
     * Helper for initAttackMap()
     */
    static void initKnightAttacks();

    /**
     * Helper for initAttackMap()
     */
    static void initKingAttacks();

    /**
     * Helper for initAttackMap()
     */
    static void initRayTables();

};

#endif /* ATTACK_MAP_HPP */