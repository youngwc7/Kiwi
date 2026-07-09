#include "generate_moves.hpp"
#include <cassert>

GenMoves::GenMoves(ChessState& game) : chessGame(game), kingIndex(-1), checkFlag(false), doubleCheckFlag(false)
{}

void GenMoves::generateLegalMoves(LegalMoveList& moveList)
{
    moveList.clearLegalMoveList();
    
    computePositionInfo();
    assert(kingIndex >= 0 && kingIndex < 64);
    
    generatePawnLegalMoves(moveList);
    generateKnightLegalMoves(moveList);
    generateBishopLegalMoves(moveList);
    generateRookLegalMoves(moveList);
    generateQueenLegalMoves(moveList);
}

void GenMoves::computePositionInfo()
{
    uint64_t kingBitboard = (chessGame.sideToMove == WHITE) ? chessGame.bitboard.whiteKing : chessGame.bitboard.blackKing;
    
    kingIndex = getLSB(kingBitboard);
}

void GenMoves::generatePawnLegalMoves(LegalMoveList& moveList)
{
    
}

void GenMoves::generateKnightLegalMoves(LegalMoveList& moveList)
{}

void GenMoves::generateBishopLegalMoves(LegalMoveList& moveList)
{}

void GenMoves::generateRookLegalMoves(LegalMoveList& moveList)
{}

void GenMoves::generateQueenLegalMoves(LegalMoveList& moveList)
{}

void GenMoves::generateKingLegalMoves(LegalMoveList& moveList)
{}
