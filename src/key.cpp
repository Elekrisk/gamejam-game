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
