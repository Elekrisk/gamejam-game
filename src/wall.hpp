#pragma once

#include <SFML/Graphics.hpp>

struct Wall
{
    enum Direction
    {
        East = 0,
        South = 1,
        West = 2,
        North = 3,
    };
    sf::Vector2i position;
    Direction direction;
};