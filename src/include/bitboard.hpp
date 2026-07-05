#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include "constants.hpp"
#include "piece.hpp"


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
    
        /**
         * @brief Get the piece at a specific square on the chessboard.
         * @param square The square index (0-63) to query.
         * @return The Piece enum value representing the piece at the specified square.
         */
        Piece getPieceAt(int square) const;

        /**
         * @brief Check if a specific square on the chessboard is occupied by any piece.
         * @param square The square index (0-63) to query.
         * @return true if the square is occupied, false otherwise.
         */
        bool isOccupiedAt(int square) const;

        /**
         * @brief Get the color of the piece at a specific square on the chessboard.
         * @param square The square index (0-63) to query.
         * @return The Color enum value representing the color of the piece at the specified square.
         * lowkey might not be useful
         */
        Color getColorAt(int square) const;

        /**
         *  @brief lookup combinedwhite piece bitboards (does not change class)
         *  @return uint64_t representing all white pieces on the board
         */ 
        uint64_t getWhiteBitboard() const;

        /**
         * @brief lookup combined black piece bitboards (does not change class)
         * @return uint64_t representing all black pieces on the board
         */
        uint64_t getBlackBitboard() const;

        /**
         * @brief lookup combined bitboards (does not change class)
         * @return uint64_t representing all pieces on the board
         */
        uint64_t getFullBitboard() const;

        /**
         * @brief lookup vacancy bitboard (does not change class)
         * @return uint64_t representing all empty squares on the board (~bitboard)
         */
        uint64_t getVacancyBitboard() const;

        /**
         * @brief Set a piece at a specific square on the chessboard.
         * @param piece The Piece enum value to set at the specified square.
         * @param square The square index (0-63) where the piece will be placed
         */
        void setPiece(Piece piece, int square);

        /**
         * @brief Remove a piece from a specific square on the chessboard.
         * @param square The square index (0-63) from which the piece will be removed.
         */
        void removePiece(int square);

        /**
         * @brief Move a piece from one square to another on the chessboard.
         * @param destSquare The destination square index (0-63).
         * @param srcSquare The source square index (0-63).
         * 
         * NOTE THAT THIS SHOULD BE LATER CAREFULLY UTILIZED
         *  TO ALLOW ENPASSANT, CASTLES, PROMOTION.
         * DO NOT SIMPLY CALL THIS FUNCTION TO MAKE A MOVE, U MUST CONSIDER THOSE CASES
         */
        void movePiece(int destSquare, int srcSquare);

        /**
         * @brief Convert the bitboard to a chessboard string representation FOR GUI. Guiboard::chessboardString
         * @param chessboardString string representing the chessboard (should be Guiboard::chessboardString).
         */
        void bitboardToChessboardString(std::string chessboardString[RANK_NUM][FILE_NUM]) const;

        /************* DEBUG *************/

        // void printBitboard(uint64_t bitboard) const;

        /**
         *  @brief prints bitboard into a chessboard with piece codes
         */
        void printBoard() const;

    private:
        /* COMBINED BITBOARDS*/
        uint64_t board;
        uint64_t whitePieces; 
        uint64_t blackPieces;

        /* WHITE PIECE BITBOARDS */
        uint64_t whitePawns;
        uint64_t whiteKnights;
        uint64_t whiteBishops;
        uint64_t whiteRooks;
        uint64_t whiteQueens;
        uint64_t whiteKing;

        /* BLACK PIECE BITBOARDS */
        uint64_t blackPawns;
        uint64_t blackKnights;
        uint64_t blackBishops;
        uint64_t blackRooks;
        uint64_t blackQueens;
        uint64_t blackKing;

        /******************* PRIVATE FUNCTIONS ********************/
        uint64_t& getBitboardFromPiece(Piece piece);
        const uint64_t& getBitboardFromPiece(Piece piece) const;

};

#endif // BITBOARD_HPP