#include "attack_map.hpp"
#include <iostream>

/* MAGNITUDE OF GENERAL DIRECTIONS */
static constexpr int NORTH  = 8;
static constexpr int EAST   = 1;
static constexpr int WEST   = 1;
static constexpr int SOUTH  = 8;

static constexpr int NORTH_EAST     = 9;
static constexpr int NORTH_WEST     = 7;
static constexpr int SOUTH_EAST     = 7;
static constexpr int SOUTH_WEST     = 9;

/* MAGNITUDE OF KNIGHT DIRECTIONS */
static constexpr int NORTH_NORTH_EAST   = 17;
static constexpr int NORTH_NORTH_WEST   = 15;
static constexpr int NORTH_EAST_EAST    = 10;
static constexpr int NORTH_WEST_WEST    = 6;
static constexpr int SOUTH_EAST_EAST    = 6;
static constexpr int SOUTH_WEST_WEST    = 10;
static constexpr int SOUTH_SOUTH_EAST   = 15;
static constexpr int SOUTH_SOUTH_WEST   = 17;

/* cannot use WHITE/BLACK for colors for indexing as that is a bit mask. Use new name */
static constexpr int WHITE_COLOR = 0;
static constexpr int BLACK_COLOR = 1;

void AttackMap::initAttackMap()
{
    initPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initRayTables();
}

/*********************** PRIVATE HELPERS ********************************/

void AttackMap::initPawnAttacks()
{
    /* These pawn attacks only handle the basic forward movement */

    /* Both Colors; start iterating from the second rank; end before eighth rank */
    /* White goes North, black goes south */
    for (int square = RANK_2 * FILE_NUM; square < RANK_8 * FILE_NUM; ++square)
    {
        uint64_t srcSquareMask = 1ULL << square;

        /* WHITE PAWN ATTACKS */
        /* NORTH_EAST pawn attack (cannot attack A file) */
        pawnAttackMap[WHITE_COLOR][square] |= NOT_A_FILE_MASK & (srcSquareMask << NORTH_EAST);

        /* NORTH_WEST pawn attack (cannot attack H file) */
        pawnAttackMap[WHITE_COLOR][square] |= NOT_H_FILE_MASK & (srcSquareMask << NORTH_WEST);

        /* BLACK PAWN ATTACKS */

        /* BLACK PAWN ATTACKS */
        /* SOUTH_EAST pawn attacks (cannot attack A file) */
        pawnAttackMap[BLACK_COLOR][square] |= NOT_A_FILE_MASK & (srcSquareMask >> SOUTH_EAST);

        /* SOUTH_WEST pawn attacks (cannot attack H file) */
        pawnAttackMap[BLACK_COLOR][square] |= NOT_H_FILE_MASK & (srcSquareMask >> SOUTH_WEST);
    }
}

void AttackMap::initKnightAttacks()
{
    for (int square = 0; square < NUM_SQUARES; ++square)
    {
        uint64_t tmpAttackMap = 0;
        uint64_t srcSquareMask = 1ULL << square;

        /* N + N + E direction */
        /* destination square can lie on all files except the A file. (no wrap arounds)*/
        tmpAttackMap |= NOT_A_FILE_MASK & (srcSquareMask << NORTH_NORTH_EAST);

        /* N + N + W direction */
        /* destination square cannot lie on the H file */
        tmpAttackMap |= NOT_H_FILE_MASK & (srcSquareMask << NORTH_NORTH_WEST);

        /* N + E + E direction */
        /* destination square cannot lie on the A and B files */
        tmpAttackMap |= NOT_A_AND_B_FILE_MASK & (srcSquareMask << NORTH_EAST_EAST);

        /* N + W + W direction */
        /* destination square cannot lie on the G and H files */
        tmpAttackMap |= NOT_G_AND_H_FILE_MASK & (srcSquareMask << NORTH_WEST_WEST);

        /* S + E + E direction */
        /* cannot lie on the A and B files */
        tmpAttackMap |= NOT_A_AND_B_FILE_MASK & (srcSquareMask >> SOUTH_EAST_EAST);

        /* S + W + W direction */
        /* cannot lie on the G and H files */
        tmpAttackMap |= NOT_G_AND_H_FILE_MASK & (srcSquareMask >> SOUTH_WEST_WEST);

        /* S + S + E direction */
        /* cannot lie on the A file */
        tmpAttackMap |= NOT_A_FILE_MASK & (srcSquareMask >> SOUTH_SOUTH_EAST);

        /* S + S + W direction */
        /* cannot lie on the H file */
        tmpAttackMap |= NOT_H_FILE_MASK & (srcSquareMask >> SOUTH_SOUTH_WEST);
    
        knightAttackMap[square] = tmpAttackMap;
    }
}

void AttackMap::initKingAttacks()
{
    for (int square = 0; square < NUM_SQUARES; ++square)
    {
        uint64_t tmpAttackMap = 0;
        uint64_t srcSquareMask = 1ULL << square;

        /* N direction (no wrap arounds possible) */
        tmpAttackMap |= srcSquareMask << NORTH;

        /* EAST direction (destination cannot lie on A file) */
        tmpAttackMap |= NOT_A_FILE_MASK & (srcSquareMask << EAST);

        /* WEST direction (destination cannot lie on H file) */
        tmpAttackMap |= NOT_H_FILE_MASK & (srcSquareMask >> WEST);

        /* SOUTH direction (no wrap arounds possible) */
        tmpAttackMap |= srcSquareMask >> SOUTH;

        /* NORTH_EAST direction (destination cannot lie on A file ) */
        tmpAttackMap |= NOT_A_FILE_MASK & (srcSquareMask << NORTH_EAST);

        /* NORTH_WEST direction (destination cannot lie on H file) */
        tmpAttackMap |= NOT_H_FILE_MASK & (srcSquareMask << NORTH_WEST);

        /* SOUTH_EAST direction (destination cannot lie on A file) */
        tmpAttackMap |= NOT_A_FILE_MASK & (srcSquareMask >> SOUTH_EAST);

        /* SOUTH_WEST direction (destination cannot lie on H file) */
        tmpAttackMap |= NOT_H_FILE_MASK & (srcSquareMask >> SOUTH_WEST);

        kingAttackMap[square] = tmpAttackMap;
    }
}

void AttackMap::initRayTables()
{
    for (int square = 0; square < NUM_SQUARES; ++square)
    {
        uint64_t srcSquareMask = 1ULL << square;
        uint64_t tmpRay = 0ULL;

        /* NORTH ray */
        tmpRay = 0ULL;
        uint64_t tmpSquareMask = srcSquareMask;

        while (tmpSquareMask <<= NORTH)
            tmpRay |= tmpSquareMask;

        rayN[square] = tmpRay;

        /* SOUTH ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while (tmpSquareMask >>= SOUTH)
            tmpRay |= tmpSquareMask;

        rayS[square] = tmpRay;

        /* EAST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask << EAST) & NOT_A_FILE_MASK))
            tmpRay |= tmpSquareMask;

        rayE[square] = tmpRay;

        /* WEST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask >> WEST) & NOT_H_FILE_MASK))
            tmpRay |= tmpSquareMask;

        rayW[square] = tmpRay;

        /* NORTH_EAST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask << NORTH_EAST) & NOT_A_FILE_MASK))
            tmpRay |= tmpSquareMask;

        rayNE[square] = tmpRay;

        /* NORTH_WEST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask << NORTH_WEST) & NOT_H_FILE_MASK))
            tmpRay |= tmpSquareMask;

        rayNW[square] = tmpRay;

        /* SOUTH_EAST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask >> SOUTH_EAST) & NOT_A_FILE_MASK))
            tmpRay |= tmpSquareMask;

        raySE[square] = tmpRay;

        /* SOUTH_WEST ray */
        tmpRay = 0ULL;
        tmpSquareMask = srcSquareMask;

        while ((tmpSquareMask = (tmpSquareMask >> SOUTH_WEST) & NOT_H_FILE_MASK))
            tmpRay |= tmpSquareMask;

        raySW[square] = tmpRay;
    }
}

void AttackMap::printBitboard(uint64_t bb)
{
    for (int rank = 7; rank >= 0; --rank)
    {
        std::cout << (rank + 1) << "  ";
        for (int file = 0; file < 8; ++file)
        {
            int square = rank * 8 + file;
            std::cout << ((bb >> square) & 1ULL) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n   a b c d e f g h\n\n";
}
