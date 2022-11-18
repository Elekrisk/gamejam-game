#include "world.hpp"

World::World() : entities{} {}

World::~World()
{
    for (Entity* ent : entities)
    {
        delete ent;
    }
}

void World::add_entity(Entity* entity)
{
    entities.push_back(entity);
}

std::vector<Entity*> const& World::get_entities() const
{
    return entities;
}