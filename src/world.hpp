#pragma once

#include "entity.hpp"
#include "wall.hpp"

class World
{
    std::vector<Entity*> entities;
    std::vector<Wall> walls;
public:
    
    World();
    ~World();
    void add_entity(Entity* entity);
    void kill_entity(Entity* entity);
    std::vector<Entity*> const& get_entities() const;

    bool can_move(sf::Vector2i pos, Wall::Direction dir) const;

    static World load_level(std::string const& path);
};