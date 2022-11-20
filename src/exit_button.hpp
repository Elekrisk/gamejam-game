#pragma once

#include "entity.hpp"

class ExitButton : public Entity
{
public:
    ExitButton(World* world, sf::Vector2i position);

    virtual void interact(std::unique_ptr<Item>&);
};
