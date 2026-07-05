#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <string>

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
    BLACK = 0b10000000,
    NO_COLOR = 0b00000000
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

inline bool isEmptyPiece(Piece p)  { return p == NONE; }

inline PieceType getType(Piece p) { return static_cast<PieceType>(p & 0b00111111); }

/* Convert a Piece enum to its string representation */

/**
 * @brief Converts a Piece enum to its corresponding chess notation string.
 * This chess string is primarily used in GUI. 
 * Utilized in a loop to convert bitboard to Guiboard::chessboardString
 * 
 * @param p The Piece enum to convert.
 * @return A string representing the chess piece, e.g: wP or bN; "" for empty square.
 */
inline std::string pieceToChessString(Piece p)
{
    switch (p)
    {
        case WHITE_PAWN:   return "wP";
        case WHITE_KNIGHT: return "wN";
        case WHITE_BISHOP: return "wB";
        case WHITE_ROOK:   return "wR";
        case WHITE_QUEEN:  return "wQ";
        case WHITE_KING:   return "wK";

        case BLACK_PAWN:   return "bP";
        case BLACK_KNIGHT: return "bN";
        case BLACK_BISHOP: return "bB";
        case BLACK_ROOK:   return "bR";
        case BLACK_QUEEN:  return "bQ";
        case BLACK_KING:   return "bK";

        default:           return "";
    }
}
#endif // PIECE_HPP 