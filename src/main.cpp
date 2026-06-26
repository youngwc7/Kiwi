#include "board.hpp"
#include "constants.hpp"

int main(void) 
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), 
                            "Kiwi Chess",
                            sf::Style::Titlebar | sf::Style::Close);


    window.setFramerateLimit(60);

    Board board;
    
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
        }
        
        // Render
        window.clear(sf::Color(30, 30, 30)); // Dark green background
        board.initDraw(window);
        window.display();
    }

    return 0; 
}