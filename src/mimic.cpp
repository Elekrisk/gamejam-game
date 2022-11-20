#include "mimic.hpp"
#include "asset_manager.hpp"
#include <iostream>
#include "world.hpp"

sf::Texture const EMPTY{};

Mimic::Mimic(World* world, sf::Vector2i position)
: Entity(world, position, &EMPTY)
{
    sf::Texture *texture{asset_manager.load<sf::Texture>("assets/chest.png")};
    sprite.setTexture(*texture, true);
    obstructs = true;
}

void Mimic::interact(std::unique_ptr<Item>& item)
{
    world->push_state(std::make_unique<World>(World::load_level("assets/you_died.txt")), true);
}
