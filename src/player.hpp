#pragma once

#include "entity.hpp"
#include "item.hpp"

class Player : public Entity
{
    std::unique_ptr<Item> item;

    Player(World* world, sf::Vector2i position, sf::Texture&& texture);

    float closest_mimic();

public:
    Player(World *world, sf::Vector2i position);
    ~Player() = default;

    void pick_up();
    void put_down();
    void interact();

    void destroy_item();

    virtual void draw(RenderView& view) override;
    void move_to(sf::Vector2i target) override;
};