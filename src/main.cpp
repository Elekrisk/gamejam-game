
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "world.hpp"
#include "renderer.hpp"
#include "player.hpp"
#include "asset_manager.hpp"

int main()
{
    World world{World::load_level("assets/level1.txt")};

    Renderer renderer{};

    sf::RenderWindow &window = renderer.get_window();
    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case event.Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        renderer.render(world);
    }

    return 0;
}