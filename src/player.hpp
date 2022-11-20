#pragma once

#include "entity.hpp"
#include "item.hpp"

class Player : public Entity
{
    std::unique_ptr<Item> item;

    Player(sf::Vector2i position, sf::Texture&& texture);

public:
    Player(sf::Vector2i position);
    ~Player() = default;

    void pick_up(World& world);
    void put_down(World& world);
    void interact(World& world);

    void destroy_item();

    virtual void draw(RenderView& view) override;
};