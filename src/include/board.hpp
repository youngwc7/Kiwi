#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Board
{
    public:

        /**
         * Default constructor that initializes the board with default size and position.
         * The default size is set to 80% of the window size, and the position
         * is set to 10% offset from the top-left corner of the window.
         */
        Board();

        /**
         * Constructs a Board object with the specified size and position.
         * 
         * @param size The size of the board square.
         * @param offsetX The X offset for the board's position.
         * @param offsetY The Y offset for the board's position.
         */
        Board(float size, float offsetX, float offsetY);

        /**
         * Draws the board and label to the given window.
         * 
         * @param window The SFML RenderWindow to draw the board and label on.
         */
        void draw(sf::RenderWindow& window);

    private:
        float   size;
        float   squareSize;
        float   offsetX;
        float   offsetY;

        sf::RectangleShape  board;
        sf::Font            font;
        sf::Text            label;

        /* String representation of the chessboard */
        std::string chessboardString[8][8];

        /* Map to hold textures for chess pieces */ 
        std::map<std::string, sf::Texture> pieceTextures;
        /* Map to hold sprites for chess pieces */
        std::map<std::string, sf::Sprite> pieceSprites;

        void loadPieceTextures();
        void initializeChessboard();
        void drawSquares(sf::RenderWindow& window);
        void drawPieces(sf::RenderWindow& window);
};


#endif // BOARD_HPP