#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

/* Chess board features */
inline constexpr int NUM_SQUARES = 64;
inline constexpr int NUM_COLORS = 2;
inline constexpr int WHITE_INDEX = 0;
inline constexpr int BLACK_INDEX = 1;

/* The maximum number of legal moves possible is proven to be 218 */
inline constexpr int THEORETICAL_MAX_LEGAL_MOVES    = 218;

/* GUI width (square) side length */
inline constexpr unsigned int DEFAULT_WINDOW_WIDTH = 1200;
inline constexpr unsigned int DEFAULT_WINDOW_HEIGHT = 800;
inline constexpr unsigned int DEFAULT_WINDOW_WIDTH_OFFSET = 400;
inline constexpr unsigned int DEFAULT_WINDOW_HEIGHT_OFFSET = 80;

/* Chess Board Consts */
inline constexpr int RANK_NUM = 8;
inline constexpr int FILE_NUM = 8;
inline constexpr int SQUARE_NUM = RANK_NUM * FILE_NUM;

/* GUI Board colors */
static const sf::Color LIGHT(240, 217, 181);
static const sf::Color DARK(181, 136, 99);

/* Highlight colors */

// for piece selection highlights
static const sf::Color GREEN_HIGHLIGHT(144, 238, 144, 128);
// for previous move highlights
static const sf::Color BLUE_HIGHLIGHT(173, 216, 230, 128);
// for in check king highlights; NOT IMPLEMENTED
static const sf::Color RED_HIGHLIGHT(255, 0, 0, 128);

static const sf::Color MOVE_HIGHLIGHT(255, 255, 0, 150); 

/* Bit masks useful for move generation */
inline constexpr uint64_t A_FILE_MASK = 0x0101010101010101;
inline constexpr uint64_t B_FILE_MASK = 0x0202020202020202;
inline constexpr uint64_t G_FILE_MASK = 0x4040404040404040;
inline constexpr uint64_t H_FILE_MASK = 0x8080808080808080;

inline constexpr uint64_t A_AND_B_FILE_MASK = A_FILE_MASK | B_FILE_MASK;
inline constexpr uint64_t G_AND_H_FILE_MASK = G_FILE_MASK | H_FILE_MASK;

inline constexpr uint64_t NOT_A_FILE_MASK = ~A_FILE_MASK;
inline constexpr uint64_t NOT_B_FILE_MASK = ~B_FILE_MASK;
inline constexpr uint64_t NOT_G_FILE_MASK = ~G_FILE_MASK;
inline constexpr uint64_t NOT_H_FILE_MASK = ~H_FILE_MASK;

inline constexpr uint64_t NOT_A_AND_B_FILE_MASK = ~A_AND_B_FILE_MASK;
inline constexpr uint64_t NOT_G_AND_H_FILE_MASK = ~G_AND_H_FILE_MASK;

inline constexpr uint64_t RANK_4_MASK = 0x00000000FF000000ULL;
inline constexpr uint64_t RANK_5_MASK = 0x000000FF00000000ULL;

/* Useful enums that can be treated like constants */

enum File : int
{
    A_FILE = 0,
    B_FILE = 1,
    C_FILE = 2,
    D_FILE = 3,
    E_FILE = 4,
    F_FILE = 5,
    G_FILE = 6,
    H_FILE = 7
};

enum Rank : int
{
    RANK_1 = 0,
    RANK_2 = 1,
    RANK_3 = 2,
    RANK_4 = 3,
    RANK_5 = 4,
    RANK_6 = 5,
    RANK_7 = 6,
    RANK_8 = 7
};

#endif // CONSTANTS_HPP