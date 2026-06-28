#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

/* GUI width (square) side length */
inline constexpr unsigned int DEFAULT_WINDOW_WIDTH = 1200;
inline constexpr unsigned int DEFAULT_WINDOW_HEIGHT = 800;
inline constexpr unsigned int DEFAULT_WINDOW_WIDTH_OFFSET = 400;
inline constexpr unsigned int DEFAULT_WINDOW_HEIGHT_OFFSET = 80;

/* Chess Board Consts */
inline constexpr int RANK_NUM = 8;
inline constexpr int FILE_NUM = 8;
inline constexpr int SQUARE_NUM = RANK_NUM * FILE_NUM;

/* Board colors */
static const sf::Color LIGHT(240, 217, 181);
static const sf::Color DARK(181, 136, 99);

/* Highlight colors */

// for piece selection highlights
static const sf::Color GREEN_HIGHLIGHT(144, 238, 144, 128);
// for previous move highlights
static const sf::Color BLUE_HIGHLIGHT(173, 216, 230, 128);
// for in check king highlights; NOT IMPLEMENTED
static const sf::Color RED_HIGHLIGHT(255, 0, 0, 128);


#endif // CONSTANTS_HPP