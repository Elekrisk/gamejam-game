#pragma once

#include "entity.hpp"
#include "item.hpp"

class Item_Entity : public Entity
{
    std::unique_ptr<Item> item;
public:
    Item_Entity(sf::Vector2i position, Item* item);
};