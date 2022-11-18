#pragma once

#include <SFML/Window.hpp>
#include "world.hpp"

class Renderer
{
    sf::RenderWindow window;
public:
    Renderer();

    sf::RenderWindow& get_window();
    void render(World& world);
};