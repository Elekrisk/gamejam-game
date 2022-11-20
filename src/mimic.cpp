#include "mimic.hpp"
#include "asset_manager.hpp"
#include <iostream>

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
    std::cout << "Oh noes D:\n";
}
