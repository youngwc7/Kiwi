#ifndef CHESS_STATE_HPP
#define CHESS_STATE_HPP

#include "bitboard.hpp"

class ChessState 
{
    public:
        /* Bitboard class instance */
        Bitboard& bitboard;

        /* flags for game state (utilized by engine/legal logic) */

        /**
         * @brief combined castling right flags (white and black); 1 if true.
         * bit 0: white kingside flag
         * bit 1: white queenside flag
         * bit 2: black kingside flag
         * bit 3: black queenside flag
         */
        uint8_t castlingRights;
        /* 
            If true value (> 0), enPassantSquare will hold square index where the 
            pawn's destination for enpassant 
         */
        uint8_t enPassantSquare;
        /* 
            half move count
         */
        uint8_t plyCount;
        /* 
            color to move 
         */
        Color   sideToMove;
         
        /**
         * @brief Constructor for standard start chess position 
         */ 
        ChessState(Bitboard& bitboard);

};

#endif /* CHESS_STATE_HPP */