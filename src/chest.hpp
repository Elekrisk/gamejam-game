#pragma once

#include "entity.hpp"
#include "item.hpp"

class Chest : public Entity
{
    std::unique_ptr<Item> contents;
    bool open_;

public:
    Chest(sf::Vector2i position, std::unique_ptr<Item> contents);
    
    void open(World& world);
};