#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

/* GUI width (square) side length */
inline constexpr unsigned int WINDOW_SIZE = 800;

/* Chess Board Consts */
inline constexpr int RANK_NUM = 8;
inline constexpr int FILE_NUM = 8;
inline constexpr int SQUARE_NUM = RANK_NUM * FILE_NUM;

/* Board colors */
static const sf::Color LIGHT(240, 217, 181);
static const sf::Color DARK(181, 136, 99);


#endif // CONSTANTS_HPP