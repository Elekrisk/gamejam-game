#pragma once

#include "entity.hpp"

class Lever : public Entity
{
    int circuit_id;
public:
    Lever(World* world, sf::Vector2i position, int circuit_id);

    virtual void interact(std::unique_ptr<Item>&) override;
};