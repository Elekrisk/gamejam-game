#include "renderer.hpp"

Renderer::Renderer()
{
    new (&window) sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

sf::RenderWindow& Renderer::get_window()
{
    return window;
}

void Renderer::render(World& world)
{
    window.clear();
    for (Entity* ent : world.get_entities())
    {
        sf::Sprite& sprite = ent->get_sprite();
        sf::Vector2f pos = static_cast<sf::Vector2f>(ent->get_position());
        sprite.setPosition(pos * 16.0f);
        
        sf::Texture test{};
        test.loadFromFile("assets/player.png");
        sf::Sprite sh{test};
        
        window.draw(sprite);
    }
    window.display();
}
