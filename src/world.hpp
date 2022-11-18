#pragma once

#include "entity.hpp"

class World
{
    std::vector<Entity*> entities;
public:
    
    World();
    ~World();
    void add_entity(Entity* entity);
    void kill_entity(Entity* entity);
    std::vector<Entity*> const& get_entities() const;

    static World load_level(std::string const& path);
};