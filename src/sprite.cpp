#include "sprite.hpp"

Sprite::Sprite(sf::Texture &&texture) : sprite{sf::Sprite{texture}}
{
}

sf::Sprite &Sprite::get_sprite()
{
    return sprite;
}