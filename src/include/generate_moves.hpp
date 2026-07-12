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

        uint64_t getAttackMask(int square, Piece piece) const;

        void resetWhiteAttacks();
        void resetBlackAttacks();
        void resetWhiteMasks();
        void resetBlackMasks();
        void resetAll();

    private:
        Color       moveColor;

        /* White king as a square index (bitboard -> int) */
        int         whiteKingIndex;
        /* White is in check ? */
        bool        whiteCheckFlag;
        /* White is in double check ? */
        bool        whiteDoubleCheckFlag;

        /**
         *  all squares black's checking piece is controlling, and it's own square. 
         *  If white's non-pinned piece lands on the mask, it resolves the check.
         * */
        uint64_t    whiteCheckMask;
        /* bitboard of all white's pinned pieces (cannot legally move) */
        uint64_t    whitePinnedPieces;
        /* bitboard all attacking squares white's pieces control */
        uint64_t    whiteAttacks;
        /* squares white's pawn attacks */
        uint64_t    whitePawnAttacks;
        /* squares white's knight attacks */
        uint64_t    whiteKnightAttacks;
        /* squares white's bishop attacks */
        uint64_t    whiteBishopAttacks;
        /* squares white's rook attacks */
        uint64_t    whiteRookAttacks;
        /* squares white's queen attacks */
        uint64_t    whiteQueenAttacks;
        /* squares white's king attacks */
        uint64_t    whiteKingAttacks;
        uint64_t    whitePinRays[64];

        int         blackKingIndex;
        bool        blackCheckFlag;
        bool        blackDoubleCheckFlag;

        /**
         *  all squares white's checking piece is controlling, and it's own square. 
         *  If black's non-pinned piece lands on the mask, it resolves the check.
         * */
        uint64_t    blackCheckMask;
        /* bitboard of all black's pinned pieces (legally) */
        uint64_t    blackPinnedPieces;
        /* bitboard of all black's attacking squares (black is controlling) */
        uint64_t    blackAttacks;
        /* squares black's pawn attacks */
        uint64_t    blackPawnAttacks;
        /* squares black's knight attacks */
        uint64_t    blackKnightAttacks;
        /* squares black's bishohp attacks */
        uint64_t    blackBishopAttacks;
        /* squares black's rook attacks */
        uint64_t    blackRookAttacks;
        /* squares black's queen attacks */
        uint64_t    blackQueenAttacks;
        /* squares black's king attacks */
        uint64_t    blackKingAttacks;
        uint64_t    blackPinRays[64];

        

        void computePositionFeatures();

        void generateAttacks(Color color);

        void generatePawnLegalMoves(LegalMoveList& moveList);

        void generateKnightLegalMoves(LegalMoveList& moveList);

        void generateBishopLegalMoves(LegalMoveList& moveList);

        void generateRookLegalMoves(LegalMoveList& moveList);

        void generateQueenLegalMoves(LegalMoveList& moveList);

        void generateKingLegalMoves(LegalMoveList& moveList);
    
};

#endif /* GENERATE_MOVES_HPP */