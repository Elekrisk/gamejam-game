
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "world.hpp"
#include "renderer.hpp"
#include "player.hpp"
#include "asset_manager.hpp"
#include "geiger.hpp"
#include "item_entity.hpp"

int main()
{
    World world{World::load_level("assets/level1.txt")};
    Player *player = world.get_player();

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
            case event.KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                {
                    sf::Vector2i pos{player->get_position()};
                    if (world.can_move(pos, Wall::Direction::North))
                    {
                        player->move_to(pos + sf::Vector2i{0, -1});
                    }
                }
                break;
                case sf::Keyboard::A:
                {
                    sf::Vector2i pos{player->get_position()};
                    if (world.can_move(pos, Wall::Direction::West))
                    {
                        player->move_to(pos + sf::Vector2i{-1, 0});
                    }
                }
                break;
                case sf::Keyboard::S:
                {
                    sf::Vector2i pos{player->get_position()};
                    if (world.can_move(pos, Wall::Direction::South))
                    {
                        player->move_to(pos + sf::Vector2i{0, 1});
                    }
                }
                break;
                case sf::Keyboard::D:
                {
                    sf::Vector2i pos{player->get_position()};
                    if (world.can_move(pos, Wall::Direction::East))
                    {
                        player->move_to(pos + sf::Vector2i{1, 0});
                    }
                }
                break;
                case sf::Keyboard::F:
                {
                    player->pick_up(world);
                }
                break;
                case sf::Keyboard::G:
                {
                    player->put_down(world);
                }
                break;
                case sf::Keyboard::E:
                {
                    player->use_item(world);
                }
                break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        renderer.render(world);
    }

    return 0;
}