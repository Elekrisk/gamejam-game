#pragma once

#include <SFML/Graphics.hpp>
#include "render_constants.hpp"

class RenderView
{
    sf::RenderWindow &window;

public:
    RenderView(sf::RenderWindow &window);

    template <typename T>
    void draw(T &drawable)
    {
        // sf::Sprite &sprite = ent->get_sprite();
        sf::Vector2f pos = drawable.getPosition();
        drawable.setPosition(pos * TILE_SIZE * SCALE);
        drawable.scale({SCALE, SCALE});

        window.draw(drawable);
    }
};