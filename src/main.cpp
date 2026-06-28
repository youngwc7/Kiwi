#include "guiboard.hpp"
#include "constants.hpp"

int main(void) 
{
    sf::RenderWindow window(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), 
                            "Kiwi Chess",
                            sf::Style::Titlebar | sf::Style::Close);


    window.setFramerateLimit(60);

    GuiBoard guiboard;
    
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