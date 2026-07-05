#include "chess_state.hpp"

ChessState::ChessState(Bitboard& bitboard) : 
    bitboard(bitboard), castlingRights(0b1111), enPassantSquare(0), plyCount(0), sideToMove(WHITE) 
{}