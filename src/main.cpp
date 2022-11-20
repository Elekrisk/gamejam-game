
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "world.hpp"
#include "renderer.hpp"
#include "player.hpp"
#include "asset_manager.hpp"
#include "geiger.hpp"
#include "item_entity.hpp"

#include "state_stack.hpp"

int main()
{
    StateStack stack{};
    PushState{std::make_unique<World>(World::load_level("assets/main_menu.txt"))}.execute(stack);

    Renderer renderer{};
    stack.run(renderer);

    return 0;
}