#pragma once

#include "entity.hpp"
#include "wall.hpp"

class Gate : public Entity
{
    int circuit_id;
    bool open;
    Wall::Direction direction;

public:
    Gate(sf::Vector2i position, Wall::Direction direction, int circuit_id, bool open);

    Wall::Direction get_direction() const;
    bool is_open() const;

    virtual void toggle_circuit(int circuit_id) override;
    virtual void draw(RenderView& view) override;
};
