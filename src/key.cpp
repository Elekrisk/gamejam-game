#include "key.hpp"
#include "asset_manager.hpp"
#include "mimic.hpp"
#include <iostream>

Key::Key() : Item{asset_manager.load<sf::Texture>("assets/key.png")} {
    sprite.setColor(sf::Color::Black);
}

void Key::use_item(Entity* target)
{
    if (dynamic_cast<Mimic*>(target) != nullptr)
    {
        std::cout << "Oh noes D:\n";
    }
}
