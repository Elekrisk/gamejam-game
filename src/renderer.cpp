#include "renderer.hpp"
#include "asset_manager.hpp"
#include <iostream>
#include "renderview.hpp"

Renderer::Renderer() : background{}
{
    new (&window) sf::RenderWindow(sf::VideoMode(800, 600), "Game");
    sf::Texture *tile_texture = asset_manager.load<sf::Texture>("assets/tile.png");
    tile_texture->setRepeated(true);
    background.setTexture(*tile_texture, true);
    background.setScale({SCALE, SCALE});
    background.setTextureRect(sf::IntRect{0, 0, static_cast<int>(800 / SCALE), static_cast<int>(600 / SCALE)});
}

sf::RenderWindow &Renderer::get_window()
{
    return window;
}

bool once = true;

void Renderer::render(World &world)
{
    window.clear();
    window.draw(background);
    RenderView view{window};
    for (Entity *ent : world.get_entities())
    {
        // sf::Sprite &sprite = ent->get_sprite();
        // sf::Vector2f pos = static_cast<sf::Vector2f>(ent->get_position());
        // sprite.setPosition(pos * TILE_SIZE * SCALE);
        // sprite.setScale({SCALE, SCALE});

        // window.draw(sprite);
        ent->draw(view);
    }
    for (Wall const &wall : world.get_walls())
    {
        sf::RectangleShape rect{{TILE_SIZE / 8.0, TILE_SIZE}};
        rect.setPosition((sf::Vector2f{wall.position} * TILE_SIZE + sf::Vector2f{TILE_SIZE / 2.0, TILE_SIZE / 2.0}) * SCALE);
        rect.setScale({SCALE, SCALE});
        rect.setOrigin({TILE_SIZE / 2.0 + 1.0, TILE_SIZE / 2.0});
        switch (wall.direction)
        {
        case Wall::Direction::North:
            rect.setRotation(90);
            break;
        case Wall::Direction::East:
            rect.setRotation(180);
            break;
        case Wall::Direction::South:
            rect.setRotation(270);
            break;
        case Wall::Direction::West:
            break;
        }
        rect.setFillColor(sf::Color::Black);
        if (once)
        {
            auto pos = rect.getPosition();
            std::cout << pos.x << ", " << pos.y << std::endl;
        }

        window.draw(rect);
    }
    once = false;
    window.display();
}
