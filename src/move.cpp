#include "move.hpp"

int Move::getSourceSquare() const 
{
    return move & SOURCE_SQUARE_MASK;
}

int Move::getDestSquare() const 
{
    return move & DEST_SQUARE_MASK;
}

bool Move::isEnPassant() const 
{
    return move & ENPASSANT_MASK;
}

PieceType Move::getPromotionPiece() const 
{
    return static_cast<PieceType>(move & PROMOTION_MASK);
}

CastleMove Move::getCastleMove() const
{
    return static_cast<CastleMove>(move & CASTLE_MASK);
}

PieceType Move::getCapturedPiece() const 
{
    return static_cast<PieceType>(move & CAPTURED_PIECE_MASK);
}

PieceType Move::getMovingPiece() const 
{
    return static_cast<PieceType>(move & MOVING_PIECE_MASK);
}

