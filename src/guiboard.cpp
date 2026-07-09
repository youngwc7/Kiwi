#include "guiboard.hpp"
#include "constants.hpp"

#include <stdexcept>
#include <array>
#include <cassert>
/* debug */
#include <iostream>

GuiBoard::GuiBoard(Bitboard& board, float boardSize, float offsetX, float offsetY) 
    : bitboard(board), boardSize(boardSize), offsetX(offsetX), offsetY(offsetY), selectedSquare(-1), prevDestSquare(-1)
{
    squareSize = boardSize / RANK_NUM;
    loadPieceTextures();
    initializeChessboard();

}

GuiBoard::GuiBoard(Bitboard& board) : GuiBoard(board, DEFAULT_WINDOW_HEIGHT * 0.8f, DEFAULT_WINDOW_WIDTH_OFFSET, DEFAULT_WINDOW_HEIGHT_OFFSET)
{}


void GuiBoard::loadPieceTextures()
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

void GuiBoard::initializeChessboard()
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

void GuiBoard::drawSquares(sf::RenderWindow& window)
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

void GuiBoard::drawPieces(sf::RenderWindow& window)
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

int GuiBoard::pixelToSquare(int pixelX, int pixelY)
{
    /* Check if the pixel coordinates are within the board's bounds */
    if (pixelX < offsetX || pixelX >= offsetX + boardSize || pixelY < offsetY || pixelY >= offsetY + boardSize)
    {
        return -1; // Out of bounds
    }

    /* Calculate the file and rank based on pixel coordinates */
    int file = (pixelX - offsetX) / squareSize;
    int rank = (pixelY - offsetY) / squareSize;

    /* Convert to square index */
    return rank * FILE_NUM + file;

}

void GuiBoard::highlightSquare(sf::RenderWindow& window, sf::Color highlightColor, int squareIndex)
{
    assert(squareIndex >=0 && squareIndex < SQUARE_NUM && "highlightSquare: square index out of bounds");

    const int rank = squareIndex / FILE_NUM;
    const int file = squareIndex % FILE_NUM;

    sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
    highlight.setPosition(offsetX + file * squareSize, offsetY + rank * squareSize);
    highlight.setFillColor(highlightColor);

    window.draw(highlight);
}

/*---------------------------------- PUBLIC MEMBER FUNCTIONS-------------------------------------------*/

void GuiBoard::draw(sf::RenderWindow& window) 
{
    drawSquares(window);

    /* Highlight Squares */
    if (selectedSquare != -1) highlightSquare(window, GREEN_HIGHLIGHT, selectedSquare);
    if (prevDestSquare != -1) highlightSquare(window, BLUE_HIGHLIGHT, prevDestSquare);

    drawPieces(window); 
}

void GuiBoard::moveDraw(sf::RenderWindow& window, int srcSquare, int destSquare) 
{
    /* Resolve src and dest square indices */
    const int srcRank = srcSquare / FILE_NUM;
    const int srcFile = srcSquare % FILE_NUM;
    const int destRank = destSquare / FILE_NUM;
    const int destFile = destSquare % FILE_NUM;

    /* Update sprite positions */
    const std::string& srcPiece = chessboardString[srcRank][srcFile];

    if (srcPiece.empty())
    {
        throw std::runtime_error("No piece at source square.");
    }

    chessboardString[destRank][destFile] = srcPiece;
    chessboardString[srcRank][srcFile] = "";
    this->prevDestSquare = destSquare; 

    // once piece is moved, selected piece should be deselected
    this->selectedSquare = -1;
    // draw(window);
}

void GuiBoard::handleClick(sf::RenderWindow& window, int mouseX, int mouseY)
{
    int clickedSquare = pixelToSquare(mouseX, mouseY);



    /* out of bounds click, deselect the square */
    if (clickedSquare == -1) 
    {
        selectedSquare = -1; // Deselect any selected square
        return; 
    } 

    /* clicked within board, check if valid piece */
    if (selectedSquare == -1) 
    {
        /* No square selected yet */
        const int rank = clickedSquare / FILE_NUM;
        const int file = clickedSquare % FILE_NUM;

        if (!chessboardString[rank][file].empty()) 
        {
            selectedSquare = clickedSquare;
            // highlightSquare(window, selectedSquare);
        }
    } 
    /* a piece has already been selected, check if destination square or if deselect */
    else 
    {
        /* deselect square case */
        if (clickedSquare == selectedSquare)
        {
            selectedSquare = -1;
            return;
        }

        /* insert legal logic here. */

        /* bitboard sync logic; bitboard rank orientation is inverted from gui board rank orientation */
        int clickedBitboardRank = 7 - (int) (clickedSquare / RANK_NUM);
        int clickedBitboardFile = clickedSquare % FILE_NUM;
        int selectedBitboardRank = 7 - (int) (selectedSquare / RANK_NUM);
        int selectedBitboardFile = selectedSquare % FILE_NUM;

        int clickedBitboardSquare = clickedBitboardRank * FILE_NUM + clickedBitboardFile;
        int selectedBitboardSquare = selectedBitboardRank * FILE_NUM + selectedBitboardFile;
        
        /* test move encoding */
        PieceType moving   = getType(bitboard.getPieceAt(selectedBitboardSquare));
        PieceType captured = getType(bitboard.getPieceAt(clickedBitboardSquare));

        Move testMove(selectedBitboardSquare, clickedBitboardSquare,
                    false, VOID, NO_CASTLE,
                    captured, moving);

        std::cout << "--- Move Encoding Test ---\n";
        std::cout << "src:      " << testMove.getSourceSquare() << "\n";
        std::cout << "dest:     " << testMove.getDestSquare()   << "\n";
        std::cout << "moving:   " << (int) bitboard.getColorAt(selectedBitboardSquare) << ", type: " << (int) testMove.getMovingPiece() << "\n";
        
if (bitboard.isOccupiedAt(clickedBitboardSquare))
    std::cout << "captured: color=" << (int)bitboard.getColorAt(clickedBitboardSquare) 
              << " type=" << (int)testMove.getCapturedPiece() << "\n";
else
    std::cout << "captured: none\n";
        std::cout << "enpassant:" << testMove.isEnPassant()     << "\n";
        std::cout << "--------------------------\n"; 

        bitboard.movePiece(clickedBitboardSquare, selectedBitboardSquare);

        /* The destination square is selected */
        moveDraw(window, selectedSquare, clickedSquare);
        // prevDestSquare = clickedSquare; // Update the previous destination square
        // selectedSquare = -1; // Deselect after moving

        bitboard.printBoard();
    }
}