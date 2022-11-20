#pragma once

#include <SFML/Graphics.hpp>
#include "render_constants.hpp"
#include "camera.hpp"

class RenderView
{
    sf::RenderWindow &window;
    Camera const &camera;

public:
    RenderView(sf::RenderWindow &window, Camera const &camera);

    template <typename T>
    void draw(T &drawable)
    {
        // sf::Sprite &sprite = ent->get_sprite();
        sf::Vector2f pos = drawable.getPosition();
        sf::Vector2f left_corner = camera.position * static_cast<float>(TILE_SIZE) * camera.zoom - sf::Vector2f{WIDTH / 2.0, HEIGHT / 2.0};
        sf::Vector2f new_pos = pos * static_cast<float>(TILE_SIZE) * camera.zoom - left_corner;
        drawable.setPosition(new_pos);
        sf::Vector2f before_scale = drawable.getScale();
        drawable.scale({camera.zoom, camera.zoom});
        window.draw(drawable);
        drawable.setPosition(pos);
        drawable.setScale(before_scale);
    }
};