#ifndef BOARD_HPP
#define BOARD_HPP

/**
 * @file board.hpp
 * @brief This file contains the declaration of the Board class, which is the GUI representation of the chessboard.
 * It strictly handles the rendering of chess pieces and squares on the board using SFML. 
 * The Board class is responsible for loading piece textures, 
 * initializing the chessboard state, and drawing the board and pieces to the window. 
 * It also handles clicks and GUI movement of pieces, BUT DOES NOT HANDLE GAME LOGIC OR RULES.
 */

#include "bitboard.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <map>


class GuiBoard
{
    public:
        Bitboard& bitboard;

        /* String representation of the chessboard */
        std::string chessboardString[8][8];

        /**
         * Default constructor that initializes the board with default size and position.
         * The default size is set to 80% of the window size, and the position
         * is set to 10% offset from the top-left corner of the window.
         */
        GuiBoard(Bitboard& board);

        /**
         * Constructs a GuiBoard object with the specified size and position.
         * 
         * @param size The size of the board square.
         * @param offsetX The X offset for the board's position.
         * @param offsetY The Y offset for the board's position.
         */
        GuiBoard(Bitboard& board, float size, float offsetX, float offsetY);

        /**
         * Draws the board and label to the given window at start of launch.
         * 
         * @param window The SFML RenderWindow to draw the board and label on.
         */
        void draw(sf::RenderWindow& window);

        /**
         * Draws the board and label to the given window.
         * 
         * @param window The SFML RenderWindow to draw the board and label on.
         * @param srcSquare The source square index.
         * @param destSquare The destination square index.
         */
        void moveDraw(sf::RenderWindow& window, int srcSquare, int destSquare);

        /**
         * Handles mouse click events on the board. selection, deselection, piece movement.
         * @param mouseX The X coordinate of the mouse click.
         * @param mouseY The Y coordinate of the mouse click.
         */
        void handleClick(sf::RenderWindow& window, int mouseX, int mouseY);

    private:
        float   boardSize;
        float   squareSize;
        float   offsetX;
        float   offsetY;

        /* mouse selected square (-1 if none) */
        int     selectedSquare;
        /* highlight of the most recent move made by opponent (-1 if start of game) */
        int     prevDestSquare;

        /* board square shape */
        sf::RectangleShape  board;
        /* idk if ill use */
        sf::Font            font;
        /* idk if ill use */
        sf::Text            label;

        /* Map to hold textures for chess pieces */ 
        std::map<std::string, sf::Texture> pieceTextures;
        /* Map to hold sprites for chess pieces */
        std::map<std::string, sf::Sprite> pieceSprites;

        /* invoked by Board::Board() */
        void loadPieceTextures();
        /* invoked by Board::Board() */
        void initializeChessboard();

        /* helper function for Board::draw() */
        void drawSquares(sf::RenderWindow& window);
    /* helper function for Board::draw() */
        void drawPieces(sf::RenderWindow& window);

        /* draws pale green highlight on square */
        void highlightSquare(sf::RenderWindow& window, sf::Color highlightColor, int squareIndex);

        /* translates pixel coordinates to square indices */
        int pixelToSquare(int pixelX, int pixelY);
};


#endif // BOARD_HPP