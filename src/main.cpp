
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "world.hpp"
#include "renderer.hpp"
#include "player.hpp"
#include "asset_manager.hpp"

int main()
{
    World world{};
    world.add_entity(new Player{sf::Vector2i{1, 0}});

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