#ifndef ATTACK_MAP_HPP
#define ATTACK_MAP_HPP

/**
 * This file will store pseudo legal moves for knights, pawns, kings
 * Format will be an array of uint64_t bitboards
 */

#include "constants.hpp"

struct AttackMap
{
    static uint64_t pawnAttackMap[NUM_COLORS][NUM_SQUARES];
    static uint64_t knightAttackMap[NUM_SQUARES];
    static uint64_t kingAttackMap[NUM_SQUARES];

    static uint64_t rayN[NUM_SQUARES];
    static uint64_t rayS[NUM_SQUARES];
    static uint64_t rayE[NUM_SQUARES];
    static uint64_t rayW[NUM_SQUARES];

    static uint64_t rayNE[NUM_SQUARES];
    static uint64_t rayNW[NUM_SQUARES];
    static uint64_t raySE[NUM_SQUARES];
    static uint64_t raySW[NUM_SQUARES];

    /** 
     * @brief acts as the constructor for this struct. Initializes members.
     */
    static void initAttackMap();
    
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