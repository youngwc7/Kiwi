#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Board
{
    public:

        Board();
        Board(float size, float offsetX, float offsetY);

        void draw(sf::RenderWindow& window);

    private:
        float   size;
        float   offsetX;
        float   offsetY;

        sf::RectangleShape  board;
        sf::Font            font;
        sf::Text            label;

};


#endif // BOARD_HPP