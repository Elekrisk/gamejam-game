#include "lever.hpp"
#include "world.hpp"
#include "asset_manager.hpp"

#include <iostream>

Lever::Lever(World* world, sf::Vector2i position, int circuit_id) : Entity{world, position, asset_manager.load<sf::Texture>("assets/lever_right.png")}, circuit_id{circuit_id} {
    obstructs = true;
}

void Lever::interact(std::unique_ptr<Item> &)
{
    std::cout << "Lever interaction\n";
    for (Entity *ent : world->get_entities())
    {
        ent->toggle_circuit(circuit_id);
    }

    sf::Texture *left = asset_manager.load<sf::Texture>("assets/lever_left.png");
    sf::Texture *right = asset_manager.load<sf::Texture>("assets/lever_right.png");
    if (sprite.getTexture() == left)
    {
        sprite.setTexture(*right, true);
    }
    else
    {
        sprite.setTexture(*left, true);
    }
}
