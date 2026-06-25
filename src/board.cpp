#include "board.hpp"
#include "constants.hpp"
#include <stdexcept>




Board::Board(float size, float offsetX, float offsetY)
{
    // Set Board Square
    board.setSize(sf::Vector2f(size, size));
    board.setPosition(offsetX, offsetY);
    board.setFillColor(sf::Color(139, 69, 19)); 

    // Load default system font
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }

    // init test -- hello world
    label.setFont(font);
    label.setString("Hello, World!");
    label.setCharacterSize(48);
    label.setFillColor(sf::Color::White);

    // Center the text on the square
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.left + textBounds.width / 2.f,
                    textBounds.top  + textBounds.height / 2.f);
    label.setPosition(offsetX + size / 2.f, offsetY + size / 2.f);

}

Board::Board() : Board(WINDOW_SIZE * 0.8f, WINDOW_SIZE * 0.1f, WINDOW_SIZE * 0.1f)
{}



void Board::draw(sf::RenderWindow& window) {
    window.draw(board);
    window.draw(label);
}
