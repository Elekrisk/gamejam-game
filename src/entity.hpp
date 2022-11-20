#pragma once

#include "sprite.hpp"
#include "renderview.hpp"
#include "item.hpp"

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
    void move_to(sf::Vector2i target);

    virtual void draw(RenderView& window);

    virtual void interact(std::unique_ptr<Item>& item, World& world);

    virtual void toggle_circuit(int id);
};