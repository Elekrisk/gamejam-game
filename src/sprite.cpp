#include "sprite.hpp"

Sprite::Sprite(sf::Texture const* texture) : sprite{}
{
    if (texture != nullptr)
    {
        sprite.setTexture(*texture, true);
    }
}

sf::Sprite &Sprite::get_sprite()
{
    return sprite;
}