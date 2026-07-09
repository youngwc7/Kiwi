#ifndef GENERATE_MOVES_HPP
#define GENERATE_MOVES_HPP

#include "attack_map.hpp"
#include "chess_state.hpp"
#include "move.hpp"
#include "bit_utilities.hpp"

class GenMoves
{
    public:

        /* chess position information */
        ChessState& chessGame;

        GenMoves(ChessState& game);

        /**
         * Will generate legal moves for the turn for ChessState
         */
        void generateLegalMoves(LegalMoveList& moveList);

    private:
        int kingIndex;
        bool checkFlag;
        bool doubleCheckFlag;

        uint64_t checkMask;
        uint64_t pinnedPieces;
        uint64_t enemyAttacks;
        uint64_t pinRays[64];

        void computePositionInfo();

        void generatePawnLegalMoves(LegalMoveList& moveList);

        void generateKnightLegalMoves(LegalMoveList& moveList);

        void generateBishopLegalMoves(LegalMoveList& moveList);

        void generateRookLegalMoves(LegalMoveList& moveList);

        void generateQueenLegalMoves(LegalMoveList& moveList);

        void generateKingLegalMoves(LegalMoveList& moveList);
    
};

#endif /* GENERATE_MOVES_HPP */