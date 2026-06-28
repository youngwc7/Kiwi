#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include "constants.hpp"
#include "guiboard.hpp"

#include <cstdint>
#include <string.h>

class Bitboard
{
    public:
        /** @brief Constructor for the Bitboard class 
         *         Initializes the all bitboards to the classical chess starting position.
        */
        Bitboard();

        // /** @brief Constructor for the Bitboard class 
        //  *         Initializes the bitboards with a custom chessboard string.
        //  *  
        //  *  @param startChessboardString Identical format as GuiBoard::chessboardString
        //  */
        // Bitboard(std::string startChessboardString[RANK_NUM][FILE_NUM]);
    
    private:
    /* general board information; shows occupancy, but not piece types */
        uint64_t board;
        uint64_t whitePieces; 
        uint64_t blackPieces;

        /* white pieces */
        uint64_t whitePawns;
        uint64_t whiteKnights;
        uint64_t whiteBishops;
        uint64_t whiteRooks;
        uint64_t whiteQueens;
        uint64_t whiteKing;

        /* black pieces */
        uint64_t blackPawns;
        uint64_t blackKnights;
        uint64_t blackBishops;
        uint64_t blackRooks;
        uint64_t blackQueens;
        uint64_t blackKing;

};

#endif // BITBOARD_HPP