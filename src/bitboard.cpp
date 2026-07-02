#include "bitboard.hpp"
#include <stdexcept>
#include <cassert>
 
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
    whiteQueens = 0x0000000000000008;
    whiteKing = 0x0000000000000010;

    blackPawns = 0x00FF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks = 0x8100000000000000;
    blackQueens = 0x0800000000000000;
    blackKing = 0x1000000000000000;
}

uint64_t Bitboard::getWhiteBitboard() const
{
    return whitePieces;
}

uint64_t Bitboard::getBlackBitboard() const
{
    return blackPieces;
}

uint64_t Bitboard::getFullBitboard() const
{
    return board;
}

uint64_t Bitboard::vacancyBitboard() const
{
    return ~board;
}


/***************************** Bitboard Piece Manipulations ************************************/

void Bitboard::setPiece(Piece piece, int square)
{
    // square to bit mask
    uint64_t bitmask = (1ULL << square);

    // function can only be called on valid indices && empty squares
    assert(square >= 0 && square < 64 && "Square index must be between 0 and 63");
    assert(~board & bitmask && "Square is already occupied; possible wrong logic");
    
    // corresponding bitboard reference
    uint64_t& pieceBitboard = getBitboardFromPiece(piece);
    pieceBitboard |= bitmask;
    
    if (isWhite(piece)) whitePieces |= bitmask;
    else                blackPieces |= bitmask;

    board |= bitmask;   
}

void Bitboard::removePiece(int square)
{
    // function can only be called on valid indices 
    assert (square >= 0 && square < 64 && "Square index must be between 0 and 63");

    // square to bit mask 
    uint64_t bitmask = (1ULL << square);
    assert(board & bitmask && "Square is already empty; possible wrong logic");

    // remove piece from corresponding bitboard
    Piece deadPiece = getPieceAt(square);
    uint64_t& pieceBitboard = getBitboardFromPiece(deadPiece);

    if (isWhite(deadPiece)) whitePieces &= ~bitmask;
    else                    blackPieces &= ~bitmask;

    pieceBitboard &= ~bitmask;
    board &= ~bitmask;
}

void Bitboard::movePiece(int destSquare, int srcSquare)
{
    // function can only be called on valid indices 
    assert(destSquare >= 0 && destSquare < 64 && "Destination square index must be between 0 and 63");
    assert(srcSquare >= 0 && srcSquare < 64 && "Source square index must be between 0 and 63");

    Piece movingPiece = getPieceAt(srcSquare);

    if (isEmptyPiece(movingPiece)) 
        throw std::invalid_argument("Source square has no piece to move");
   
    removePiece(srcSquare);
    
    // capture piece condition
    if (isOccupiedAt(destSquare)) removePiece(destSquare);
    
    setPiece(movingPiece, destSquare);
}

void Bitboard::bitboardToChessboardString(std::string chessboardString[RANK_NUM][FILE_NUM]) const
{
    for (int rank = 0; rank < RANK_NUM; ++rank)
    {
        for (int file = 0; file < FILE_NUM; ++file)
        {
            int square = rank * FILE_NUM + file;
            Piece piece = getPieceAt(square);
            chessboardString[rank][file] = pieceToChessString(piece);
        }
    }
}

/***************************** PRIVATE ****************************/
uint64_t& Bitboard::getBitboardFromPiece(Piece piece)
{
    switch (piece)
    {
        case WHITE_PAWN:   return whitePawns;
        case WHITE_KNIGHT: return whiteKnights;
        case WHITE_BISHOP: return whiteBishops;
        case WHITE_ROOK:   return whiteRooks;
        case WHITE_QUEEN:  return whiteQueens;
        case WHITE_KING:   return whiteKing;

        case BLACK_PAWN:   return blackPawns;
        case BLACK_KNIGHT: return blackKnights;
        case BLACK_BISHOP: return blackBishops;
        case BLACK_ROOK:   return blackRooks;
        case BLACK_QUEEN:  return blackQueens;
        case BLACK_KING:   return blackKing;

        default:
            throw std::invalid_argument("Invalid piece type");
    }
}

const uint64_t& Bitboard::getBitboardFromPiece(Piece piece) const
{
    switch (piece)
    {
        case WHITE_PAWN:   return whitePawns;
        case WHITE_KNIGHT: return whiteKnights;
        case WHITE_BISHOP: return whiteBishops;
        case WHITE_ROOK:   return whiteRooks;
        case WHITE_QUEEN:  return whiteQueens;
        case WHITE_KING:   return whiteKing;

        case BLACK_PAWN:   return blackPawns;
        case BLACK_KNIGHT: return blackKnights;
        case BLACK_BISHOP: return blackBishops;
        case BLACK_ROOK:   return blackRooks;
        case BLACK_QUEEN:  return blackQueens;
        case BLACK_KING:   return blackKing;

        default:
            throw std::invalid_argument("Invalid piece type");
    }
}


