#pragma once

#include "entity.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "state_stack.hpp"

class World : public State
{
    sf::Vector2i size;
    Camera camera;
    Player *player;
    std::vector<Entity *> entities;
    std::vector<Wall> walls;

    std::unique_ptr<State> new_state;
    bool replace_this;
    bool exit;

public:
    World();
    World(World const &world) = delete;
    World(World &&world);
    ~World();
    // World& operator=(World&& world);
    void add_entity(Entity *entity);
    void kill_entity(Entity *entity);
    std::vector<Entity *> const &get_entities() const;
    std::vector<Wall> const &get_walls() const;
    Player *get_player() const;
    Camera &get_camera();

    void push_state(std::unique_ptr<State> state, bool replace_this);
    void do_exit();

    sf::Vector2i get_size() const;

    bool can_move(sf::Vector2i pos, Wall::Direction dir) const;

    static World load_level(std::string const &path);

    virtual std::vector<std::unique_ptr<StateTransition>> run(Renderer& renderer) override;
};