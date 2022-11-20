#include "mimic.hpp"
#include "asset_manager.hpp"
#include <iostream>

sf::Texture const EMPTY{};

Mimic::Mimic(sf::Vector2i position)
: Entity(position, &EMPTY)
{
    sf::Texture *texture{asset_manager.load<sf::Texture>("assets/chest.png")};
    sprite.setTexture(*texture, true);
}

void Mimic::interact(std::unique_ptr<Item>& item, World& world)
{
    std::cout << "Oh noes D:\n";
}
