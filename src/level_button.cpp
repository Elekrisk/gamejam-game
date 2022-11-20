#include "level_button.hpp"
#include "asset_manager.hpp"
#include <sstream>
#include "world.hpp"

std::string concat(std::string str, int level, std::string after)
{
    std::stringstream ss{};
    ss << str << level << after;
    return ss.str();
}

LevelButton::LevelButton(World *world, sf::Vector2i position, int level) : Entity{world, position, asset_manager.load<sf::Texture>(concat("assets/level", level, ".png"))}, level{level} {}

void LevelButton::interact(std::unique_ptr<Item> &)
{
    world->push_state(std::make_unique<World>(World::load_level(concat("assets/level", level, ".txt"))), false);
}