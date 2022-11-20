#pragma once
#include "entity.hpp"

class LevelButton : public Entity
{
    int level;
public:
    LevelButton(World* world, sf::Vector2i position, int level);

    virtual void interact(std::unique_ptr<Item>&) override;
};
