#pragma once

#include "entity.hpp"
#include "wall.hpp"
#include "player.hpp"

class World
{
    Player* player;
    std::vector<Entity*> entities;
    std::vector<Wall> walls;
public:
    
    World();
    ~World();
    void add_entity(Entity* entity);
    void kill_entity(Entity* entity);
    std::vector<Entity*> const& get_entities() const;
    std::vector<Wall> const& get_walls() const;
    Player* get_player() const;

    bool can_move(sf::Vector2i pos, Wall::Direction dir) const;

    static World load_level(std::string const& path);
};