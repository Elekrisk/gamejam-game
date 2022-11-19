#include "key.hpp"
#include "asset_manager.hpp"
#include "mimic.hpp"
#include "chest.hpp"
#include "world.hpp"
#include <iostream>

Key::Key() : Item{asset_manager.load<sf::Texture>("assets/key.png")}
{
    sprite.setColor(sf::Color::White);
}

void Key::use_item(Entity *target, World &world)
{
    Mimic *mimic;
    Chest *chest;
    if ((mimic = dynamic_cast<Mimic *>(target)) != nullptr)
    {
        std::cout << "Oh noes D:\n";
    }
    else if ((chest = dynamic_cast<Chest *>(target)) != nullptr)
    {
        chest->open(world);
        world.get_player()->destroy_item(); // DESTRUCTOR WILL RUN HERE
        // `this` is now a dangling pointer
    }
}
