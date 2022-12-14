#pragma once

#include "entity.hpp"
#include "item.hpp"

class Item_Entity : public Entity
{
    std::unique_ptr<Item> item;
public:
    Item_Entity(World* world, sf::Vector2i position, std::unique_ptr<Item> item);
    std::unique_ptr<Item> steal_item();
};