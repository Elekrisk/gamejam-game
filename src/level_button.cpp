#include "level_button.hpp"
#include "asset_manager.hpp"
#include <sstream>
#include "world.hpp"
#include "concat.hpp"



LevelButton::LevelButton(World *world, sf::Vector2i position, int level) : Entity{world, position, asset_manager.load<sf::Texture>(concat("assets/level", level, ".png"))}, level{level}
{
    obstructs = true;
}

void LevelButton::interact(std::unique_ptr<Item> &)
{
    world->push_state(std::make_unique<World>(World::load_level(concat("assets/level", level, ".txt"))), false);
}