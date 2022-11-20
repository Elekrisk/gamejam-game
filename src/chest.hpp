#pragma once

#include "entity.hpp"
#include "item.hpp"

class Chest : public Entity
{
    std::unique_ptr<Item> contents;
    bool open_;

public:
    Chest(World* world, sf::Vector2i position, std::unique_ptr<Item> contents);
    
    void open();

    virtual void interact(std::unique_ptr<Item>& item) override;
};