#pragma once

#include "entity.hpp"

class SpriteEntity : public Entity
{
public:
    SpriteEntity(World* world, sf::Vector2i position, std::string const& name);
};