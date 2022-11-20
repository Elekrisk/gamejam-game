#include "goal.hpp"
#include "treasure.hpp"
#include "asset_manager.hpp"
#include "world.hpp"

#include <iostream>

Goal::Goal(World *world, sf::Vector2i position) : Entity{world, position, asset_manager.load<sf::Texture>("assets/goal.png")} {
    obstructs = true;
}

void Goal::interact(std::unique_ptr<Item> &item)
{
    Treasure *treasure = dynamic_cast<Treasure *>(&*item);
    if (treasure != nullptr)
    {
        std::cout << "You win! :D\n";
        item = nullptr;
        world->push_state(std::make_unique<World>(World::load_level("assets/you_win.txt")), true);
    }
}
