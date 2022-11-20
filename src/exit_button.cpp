#include "exit_button.hpp"
#include "asset_manager.hpp"
#include "world.hpp"

ExitButton::ExitButton(World *world, sf::Vector2i position) : Entity{world, position, asset_manager.load<sf::Texture>("assets/exit.png")}
{
    obstructs = true;
}

void ExitButton::interact(std::unique_ptr<Item> &)
{
    world->do_exit();
}