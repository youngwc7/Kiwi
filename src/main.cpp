#include "guiboard.hpp"
#include "constants.hpp"
#include "bitboard.hpp"
#include "attack_map.hpp"

#include <iostream>

int main(void) 
{
    sf::RenderWindow window(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), 
                            "Kiwi Chess",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);

    /* Bitboard and GUI board set to standard (default) position */
    Bitboard bitboard;
    GuiBoard guiboard(bitboard);

    bitboard.printBoard();

    AttackMap::initAttackMap();
    // test knight on e4 (square 28)
    std::cout << "Knight attacks from e4:\n";
    AttackMap::printBitboard(AttackMap::knightAttackMap[28]);

    // test king on e1 (square 4)
    std::cout << "King attacks from e1:\n";
    AttackMap::printBitboard(AttackMap::kingAttackMap[4]);

    // test north ray from e4 (square 28)
    std::cout << "North ray from e4:\n";
    AttackMap::printBitboard(AttackMap::rayN[28]);

    std::cout << "NE ray from d4: \n";
    AttackMap::printBitboard(AttackMap::rayNE[FILE_NUM * RANK_4 + D_FILE]);
    
    while (window.isOpen()) 
    {
        sf::Event event;

        // Close Window
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            /* mouse Click event */
            if (event.type == sf::Event::MouseButtonReleased && 
                event.mouseButton.button == sf::Mouse::Left)
            {
                guiboard.handleClick(window, event.mouseButton.x, event.mouseButton.y);
            }
        }

        // Render
        window.clear(sf::Color(30, 30, 30)); // Dark green background
        guiboard.draw(window);
        window.display();
    }

    return 0; 
}