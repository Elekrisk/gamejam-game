#pragma once

#include "entity.hpp"

class Mimic : public Entity
{
public:
    Mimic (sf::Vector2i position);

    virtual void interact(std::unique_ptr<Item>& item, World& world) override;
};