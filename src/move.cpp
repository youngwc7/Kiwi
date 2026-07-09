#include "move.hpp"

/*********************** LEGAL MOVE LIST STRUCT DEFINITIONS ****************************/

void LegalMoveList::addLegalMove(Move move)
{
    legalMoves[numLegalMoves++] = move;
}

int LegalMoveList::getNumLegalMoves() 
{
    return numLegalMoves;
}

void LegalMoveList::clearLegalMoveList()
{
    numLegalMoves = 0;
}

/*********************** MOVE STRUCT DEFINITIONS ****************************/

Move::Move(int srcSquare, int destSquare, 
        bool enpassant, PieceType promotionType, CastleMove castles, 
        PieceType capturedPiece, PieceType movingPiece)
{
    move =  static_cast<uint32_t>(movingPiece) <<  MOVING_PIECE_LSB         |
            static_cast<uint32_t>(capturedPiece) << CAPTURED_PIECE_LSB      |
            static_cast<uint32_t>(castles) << CASTLE_BIT_LSB                |
            static_cast<uint32_t>(promotionType) << PROMOTION_BIT_LSB       |
            static_cast<uint32_t>(enpassant) << ENPASSANT_BIT_LSB           |
            static_cast<uint32_t>(destSquare) << DEST_SQUARE_BIT_LSB        |
            static_cast<uint32_t>(srcSquare);

}

int Move::getSourceSquare() const 
{
    return (move & SOURCE_SQUARE_MASK); // >> SOURCE_SQUARE_BIT_LSB;
}

int Move::getDestSquare() const 
{
    return (move & DEST_SQUARE_MASK) >> DEST_SQUARE_BIT_LSB;
}

bool Move::isEnPassant() const 
{
    return move & ENPASSANT_MASK; // >> ENPASSANT_BIT_LSB;
}

PieceType Move::getPromotionPiece() const 
{
    return static_cast<PieceType>((move & PROMOTION_MASK) >> PROMOTION_BIT_LSB);
}

CastleMove Move::getCastleMove() const
{
    return static_cast<CastleMove>((move & CASTLE_MASK) >> CASTLE_BIT_LSB);
}

PieceType Move::getCapturedPiece() const 
{
    return static_cast<PieceType>((move & CAPTURED_PIECE_MASK) >> CAPTURED_PIECE_LSB);
}

PieceType Move::getMovingPiece() const 
{
    return static_cast<PieceType>((move & MOVING_PIECE_MASK) >> MOVING_PIECE_LSB);
}
