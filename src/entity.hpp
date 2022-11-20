#pragma once

#include "sprite.hpp"
#include "renderview.hpp"
#include "item.hpp"

class World;

class Entity : public Sprite
{
protected:
    World* world;
    sf::Vector2i position;
    bool obstructs;

public:
    Entity(World* world, sf::Vector2i position, sf::Texture const *texture);
    virtual ~Entity() override = default;
    void update(World& world);
    void update_world_pointer(World* world);
    sf::Vector2i get_position() const;
    virtual void move_to(sf::Vector2i target);
    bool does_obstruct() const;
    void set_obstructs(bool obstructs);


    virtual void draw(RenderView& window);

    virtual void interact(std::unique_ptr<Item>& item);

    virtual void toggle_circuit(int id);
};