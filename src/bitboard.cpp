#include "bitboard.hpp"

 
/* Definition for the default constructor */
Bitboard::Bitboard()
{
    board = 0xFFFF00000000FFFF; 
    whitePieces = 0x000000000000FFFF; 
    blackPieces = 0xFFFF000000000000; 

    whitePawns = 0x000000000000FF00;
    whiteKnights = 0x0000000000000042;
    whiteBishops = 0x0000000000000024;
    whiteRooks = 0x0000000000000081;
    whiteQueens = 0x0000000000000010;
    whiteKing = 0x0000000000000080;

    blackPawns = 0x00FF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks = 0x8100000000000000;
    blackQueens = 0x10000000000000;
    blackKing = 0x80000000000000;
}

