#pragma once

#include "entity.hpp"
#include "item.hpp"

class Player : public Entity
{
    std::unique_ptr<Item> item;
    World* world;

    Player(sf::Vector2i position, sf::Texture&& texture);

    float closest_mimic(World* world);

public:
    Player(sf::Vector2i position, World* world);
    ~Player() = default;

    void pick_up(World& world);
    void put_down(World& world);
    void interact(World& world);

    void destroy_item();

    virtual void draw(RenderView& view) override;
    void move_to(sf::Vector2i target) override;
};