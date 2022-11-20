#include "gate.hpp"
#include "render_constants.hpp"

Gate::Gate(World* world, sf::Vector2i position, Wall::Direction direction, int circuit_id, bool open)
    : Entity{world, position, nullptr},
      direction{direction},
      circuit_id{circuit_id},
      open{open}
{
}

Wall::Direction Gate::get_direction() const
{
    return direction;
}

bool Gate::is_open() const { return open; }

void Gate::toggle_circuit(int circuit_id)
{
    if (circuit_id == this->circuit_id)
    {
        open = !open;
    }
}

void Gate::draw(RenderView &view)
{
    if (!open)
    {
        sf::RectangleShape rect{{TILE_SIZE / 8.0, TILE_SIZE}};
        rect.setPosition(sf::Vector2f{position} + sf::Vector2f{0.5f, 0.5f});
        rect.setOrigin({TILE_SIZE / 2.0 + 1.0, TILE_SIZE / 2.0});
        switch (direction)
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
        view.draw(rect);
    }
}
