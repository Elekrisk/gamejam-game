#pragma once

#include "sprite.hpp"

class Item : public Sprite
{
public:
    Item(sf::Texture const* texture);
    virtual ~Item() = default;
};