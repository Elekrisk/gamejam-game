#pragma once

#include "sprite.hpp"

class World;

class Entity : public Sprite
{
protected:
    sf::Vector2i position;

public:
    Entity(sf::Vector2i position, sf::Texture const *texture);
    virtual ~Entity() override = default;
    void update(World& world);
    sf::Vector2i get_position() const;
    void move_to(int x, int y);
};