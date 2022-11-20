#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class World;


class Renderer
{
    sf::Sprite background;
    sf::RenderWindow window;

public:
    Renderer();

    sf::RenderWindow &get_window();
    void render(World &world);
};