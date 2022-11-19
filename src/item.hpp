#pragma once

#include "sprite.hpp"
#include "entity.hpp"

class Item : public Sprite
{
public:
    Item(sf::Texture const* texture);
    virtual ~Item() = default;

    virtual void use_item(Entity* target) = 0;
};