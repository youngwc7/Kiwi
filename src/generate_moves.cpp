#include "generate_moves.hpp"
#include <cassert>
#include <cstring>

GenMoves::GenMoves(ChessState& game) :  chessGame(game), moveColor(NO_COLOR),
                                        whiteKingIndex(-1), whiteCheckFlag(false), 
                                        whiteDoubleCheckFlag(false), whiteCheckMask(0), 
                                        whitePinnedPieces(0), whiteAttacks(0), 
                                        whitePawnAttacks(0), whiteKnightAttacks(0), 
                                        whiteBishopAttacks(0), whiteRookAttacks(0), 
                                        whiteQueenAttacks(0), whiteKingAttacks(0), 
                                        whitePinRays{},

                                        blackKingIndex(-1), blackCheckFlag(false), 
                                        blackDoubleCheckFlag(false), blackCheckMask(0),
                                        blackPinnedPieces(0), blackAttacks(0),
                                        blackPawnAttacks(0), blackKnightAttacks(0),
                                        blackBishopAttacks(0), blackRookAttacks(0),
                                        blackQueenAttacks(0), blackKingAttacks(0), 
                                        blackPinRays{}
{}

void GenMoves::generateLegalMoves(LegalMoveList& moveList)
{
    moveList.clearLegalMoveList();
    
    computePositionFeatures();
    /* requires fixing */
    assert(whiteKingIndex >= 0 && whiteKingIndex < 64);
    
    generateAttacks(moveColor);
    generatePawnLegalMoves(moveList);
    generateKnightLegalMoves(moveList);
    generateBishopLegalMoves(moveList);
    generateRookLegalMoves(moveList);
    generateQueenLegalMoves(moveList);
    generateKingLegalMoves(moveList);
}

void GenMoves::resetWhiteAttacks()
{
    whiteAttacks = whitePawnAttacks = whiteKnightAttacks           = 
    whiteBishopAttacks = whiteRookAttacks = whiteQueenAttacks      = 
    whiteKingAttacks                                               = 0;
}

void GenMoves::resetBlackAttacks()
{
    blackAttacks = blackPawnAttacks = blackKnightAttacks        = 
    blackBishopAttacks = blackRookAttacks = blackQueenAttacks   = 
    blackKingAttacks                                            = 0;
}

void GenMoves::resetWhiteMasks()
{
    whiteCheckMask = whitePinnedPieces = 0;
    memset(whitePinRays, 0, sizeof(whitePinRays));

    whiteCheckFlag = whiteDoubleCheckFlag = false;
}

void GenMoves::resetBlackMasks()
{
    blackCheckMask = blackPinnedPieces = 0;
    memset(blackPinRays, 0, sizeof(blackPinRays));
    
    blackCheckFlag = blackDoubleCheckFlag = false;
}

void GenMoves::resetAll()
{
    resetWhiteAttacks();
    resetWhiteMasks();
    resetBlackAttacks();
    resetBlackMasks();
}

void GenMoves::computePositionFeatures()
{
    moveColor = chessGame.sideToMove;
    uint64_t whiteKingBitboard = chessGame.bitboard.whiteKing;
    uint64_t blackKingBitboard = chessGame.bitboard.blackKing;

    /* requires fixing */
    whiteKingIndex = getLSB(whiteKingBitboard);
    blackKingIndex = getLSB(blackKingBitboard);
}

void GenMoves::generateAttacks(Color color)
{
    /* Compile all attacked squares by the color */
    if (color == BLACK) 
    {
        resetBlackAttacks();

        uint64_t blackPawnsBitboard = chessGame.bitboard.blackPawns;
        uint64_t blackKnightsBitboard = chessGame.bitboard.blackKnights;
        uint64_t blackKingBitboard = chessGame.bitboard.blackKing;
        
        while (blackPawnsBitboard)
        {
            int blackPawnSquareIndex = popLSB(blackPawnsBitboard);

            blackPawnAttacks |= AttackMap::pawnAttackMap[BLACK_INDEX][blackPawnSquareIndex];
        }
        while (blackKnightsBitboard)
        {
            int blackKnightSquareIndex = popLSB(blackKnightsBitboard);

            blackKnightAttacks |= AttackMap::knightAttackMap[blackKnightSquareIndex];
        }
        /* bishop attacks yet to be implemented */
        /* rook attacks yet to be implemented */
        /* queen attacks yet to be implemented */
        blackKingIndex = popLSB(blackKingBitboard);

        blackKingAttacks = AttackMap::kingAttackMap[blackKingIndex];
        blackAttacks =  blackPawnAttacks | blackKnightAttacks | blackBishopAttacks |
                        blackRookAttacks | blackQueenAttacks | blackKingAttacks;
    }
    else 
    {
        resetWhiteAttacks();

        uint64_t whitePawnsBitboard = chessGame.bitboard.whitePawns;
        uint64_t whiteKnightsBitboard = chessGame.bitboard.whiteKnights;
        uint64_t whiteKingBitboard = chessGame.bitboard.whiteKing;

        while (whitePawnsBitboard)
        {
            int whitePawnSquareIndex = popLSB(whitePawnsBitboard);

            whitePawnAttacks |= AttackMap::pawnAttackMap[WHITE_INDEX][whitePawnSquareIndex];
        }

        while (whiteKnightsBitboard)
        {
            int whiteKnightSquareIndex = popLSB(whiteKnightsBitboard);

            whiteKnightAttacks |= AttackMap::knightAttackMap[whiteKnightSquareIndex];
        }
        /* bishop to be implemented */
        /* rook to be implemented */
        /* queen to be implemented */
        whiteKingIndex = popLSB(whiteKingBitboard);

        whiteKingAttacks = AttackMap::kingAttackMap[whiteKingIndex];
        whiteAttacks =  whitePawnAttacks | whiteKnightAttacks | whiteBishopAttacks |        
                        whiteRookAttacks | whiteQueenAttacks | whiteKingAttacks;
    }
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
