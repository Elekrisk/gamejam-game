#pragma once

#include "entity.hpp"

class Goal : public Entity
{
public:
    Goal(World* world, sf::Vector2i position);

    virtual void interact(std::unique_ptr<Item>& item) override;
};
