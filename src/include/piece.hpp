#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>

/* PIECE TYPES */
enum PieceType : uint8_t
{
    VOID = 0b00000000,
    PAWN = 0b00000001,
    KNIGHT = 0b00000010,
    BISHOP = 0b00000100,
    ROOK = 0b00001000,
    QUEEN = 0b00010000,
    KING = 0b00100000
};

enum Color : uint8_t
{
    WHITE = 0b01000000,
    BLACK = 0b10000000
};

// Piece combined
enum Piece : uint8_t
{
    NONE         = 0,

    WHITE_PAWN   = WHITE | PAWN,
    WHITE_KNIGHT = WHITE | KNIGHT,
    WHITE_BISHOP = WHITE | BISHOP,
    WHITE_ROOK   = WHITE | ROOK,
    WHITE_QUEEN  = WHITE | QUEEN,
    WHITE_KING   = WHITE | KING,
    
    BLACK_PAWN   = BLACK | PAWN,
    BLACK_KNIGHT = BLACK | KNIGHT,
    BLACK_BISHOP = BLACK | BISHOP,
    BLACK_ROOK   = BLACK | ROOK,
    BLACK_QUEEN  = BLACK | QUEEN,
    BLACK_KING   = BLACK | KING
};

/* Helper Comparison functions */
inline bool isWhite(Piece p)  { return (p & WHITE) != 0; }

inline bool isBlack(Piece p)  { return (p & BLACK) != 0; }

inline bool isEmpty(Piece p)  { return p == NONE; }

inline PieceType getType(Piece p) { return static_cast<PieceType>(p & 0b00111111); }

#endif // PIECE_HPP 