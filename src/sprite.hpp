#pragma once

#include <SFML/Graphics.hpp>

class Sprite
{
protected:
    sf::Sprite sprite;
public:
    Sprite(sf::Texture&& texture);
    virtual ~Sprite() = default;

    sf::Sprite& get_sprite();
};
