#ifndef MOVE_HPP
#define MOVE_HPP

#include "piece.hpp"
#include <cstdint>

constexpr uint32_t SOURCE_SQUARE_MASK   = 0b00000000000000000000000000111111;
constexpr uint32_t DEST_SQUARE_MASK     = 0b00000000000000000000111111000000;
constexpr uint32_t ENPASSANT_MASK       = 0b00000000000000000001000000000000;
constexpr uint32_t PROMOTION_MASK       = 0b00000000000000001110000000000000;
constexpr uint32_t CASTLE_MASK          = 0b00000000000011110000000000000000;
constexpr uint32_t CAPTURED_PIECE_MASK  = 0b00000011111100000000000000000000;
constexpr uint32_t MOVING_PIECE_MASK    = 0b11111100000000000000000000000000;

enum CastleMove : uint8_t
{
    NO_CASTLE = 0b0000,
    WHITE_KINGSIDE = 0b0001,
    WHITE_QUEENSIDE = 0b0010,
    BLACK_KINGSIDE = 0b0100,
    BLACK_QUEENSIDE = 0b1000
};

/**
 * Encoding Move into bits  
 * [5:0] bits    : source square bits
 * [11:6] bits   : dest square bits
 * [12] bit      : enpassant flag
 * [15:13] bits  : promotion flags 
 *                (000 = no promotion, 001 = knight, 010 = bishop, 011 = rook, 100 = queen)  
 * [19:16] bits  : castling flags 
 *                 0001 = white kingside, 0010 = white queenside, 
 *                 0100 = black kingside, 1000 = black queenside 
 * [25:20] bits  : captured piece (can be decoded into PieceType enum)
 * [31:26] bits  : moving piece type (can be decoded into PieceType enum)
 */ 
struct Move 
{ 
    uint32_t move; 

    /**
     * @brief Get the source square of the move.
     */
    int getSourceSquare() const;

    /**
     * @brief Get the destination square of the move.
     */
    int getDestSquare() const;

    /**
     * @brief Obtain bool indicator for enpassant move
     */
    bool isEnPassant() const;

    /**
     * @brief Decode if the move is a promotion
     */
    bool isPromotion() const;

    /**
     * @brief Get the promotion piece type if the move is a promotion.
     * @return PieceType enum. PieceType::VOID if move is NOT a promotion
     */
    PieceType getPromotionPiece() const;

    /**
     * @brief Get the castling move type if the move is a castling move.
     * @return CastleMove enum. CastleMove::NO_CASTLE if move is NOT a castling move
     */
    CastleMove getCastleMove() const;

    /**
     * @brief Get the piece type of the captured piece.
     * @return PieceType enum. PieceType::VOID if no piece was captured.
     */
    PieceType getCapturedPiece() const;

    /**
     * @brief Get the piece type of the moving piece.
     * @return PieceType enum.
     */
    PieceType getMovingPiece() const;

};

#endif /* MOVE_HPP */