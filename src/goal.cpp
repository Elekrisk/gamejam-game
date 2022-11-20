#include "goal.hpp"
#include "treasure.hpp"
#include "asset_manager.hpp"

#include <iostream>

Goal::Goal(World *world, sf::Vector2i position) : Entity{world, position, asset_manager.load<sf::Texture>("assets/goal.png")} {}

void Goal::interact(std::unique_ptr<Item> &item, World &world)
{
    Treasure *treasure = dynamic_cast<Treasure *>(&*item);
    if (treasure != nullptr)
    {
        std::cout << "You win! :D\n";
    }
}
