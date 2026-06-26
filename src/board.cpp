#include "board.hpp"
#include "constants.hpp"

#include <stdexcept>
#include <array>

Board::Board(float size, float offsetX, float offsetY) 
    : size(size), offsetX(offsetX), offsetY(offsetY)
{
    squareSize = size / RANK_NUM;
    loadPieceTextures();
    initializeChessboard();

}

Board::Board() : Board(WINDOW_SIZE * 0.8f, WINDOW_SIZE * 0.1f, WINDOW_SIZE * 0.1f)
{}


void Board::loadPieceTextures()
{
    const std::array<std::string, 12> pieces = {"wP", "wN", "wB", "wR", "wQ", "wK",
                                                "bP", "bN", "bB", "bR", "bQ", "bK"};
    
    for (const auto& piece : pieces)
    {
        /* Create textures for each piece*/
        sf::Texture texture;
        std::string imgPath = "images/" + piece + ".png";

        if (!texture.loadFromFile(imgPath))
        {
            throw std::runtime_error("Failed to load texture: " + imgPath);
        }

        texture.setSmooth(true);
        pieceTextures[piece] = texture;

        /* Create sprite for each piece */
        sf::Sprite sprite(pieceTextures[piece]);

        /* Scale the sprite to fit within the square */
        float scaleX = squareSize / sprite.getLocalBounds().width;
        float scaleY = squareSize / sprite.getLocalBounds().height;
        
        sprite.setScale(scaleX, scaleY);
        pieceSprites[piece] = sprite;
    }
}

void Board::initializeChessboard()
{
    /* Initialize piece string */
    std::string backRankLetters[] = {"R", "N", "B", "Q", "K", "B", "N", "R"};

    /* self reminder that [0][0] is top left of chessboard (a8 square) */
    for (int f = 0; f < FILE_NUM; ++f)
    {
        chessboardString[0][f] = "b" + backRankLetters[f];
        chessboardString[7][f] = "w" + backRankLetters[f];

        chessboardString[1][f] = "bP";
        chessboardString[6][f] = "wP";

        /* Initialize empty squares */
        for (int r = 2; r < 6; ++r) chessboardString[r][f] = "";   
    }
}

void Board::initDrawSquares(sf::RenderWindow& window)
{
    /* square entity */
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

    /* draw 64 squares; draws starting from a8 square */
    for (int r = 0; r < RANK_NUM; ++r)
    {
        for (int f = 0; f < FILE_NUM; ++f)
        {
            square.setPosition(offsetX + f * squareSize, offsetY + r * squareSize);
            square.setFillColor((r + f) % 2 == 0 ? LIGHT : DARK);
            window.draw(square);
        }
    }
}

void Board::initDrawPieces(sf::RenderWindow& window)
{
    for (int r = 0; r < RANK_NUM; ++r)
    {
        for (int f = 0; f < FILE_NUM; ++f)
        {
            const std::string& piece = chessboardString[r][f];
            
            if (piece.empty()) continue;
            
            /* draw sprite */
            sf::Sprite& sprite = pieceSprites[piece];
            sprite.setPosition(offsetX + f * squareSize, offsetY + r * squareSize);
            window.draw(sprite);   
        }
    }
}

/*---------------------------------- PUBLIC MEMBER FUNCTIONS-------------------------------------------*/

void Board::initDraw(sf::RenderWindow& window) 
{
    initDrawSquares(window);
    initDrawPieces(window); 
}
