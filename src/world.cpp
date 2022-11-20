#include "world.hpp"
#include "player.hpp"
#include "item_entity.hpp"
#include "geiger.hpp"
#include "mimic.hpp"
#include "chest.hpp"
#include "key.hpp"
#include "treasure.hpp"
#include "lever.hpp"
#include "gate.hpp"
#include "level_parser.hpp"
#include "render_constants.hpp"

#include <fstream>
#include <sstream>

World::World() : entities{}, walls{}, player{}, camera{} {}

World::~World()
{
    for (Entity *ent : entities)
    {
        delete ent;
    }
}

void World::add_entity(Entity *entity)
{
    Player *player_entity = dynamic_cast<Player *>(entity);
    if (player_entity != nullptr)
    {
        player = player_entity;
    }
    entities.push_back(entity);
}

void World::kill_entity(Entity *entity)
{
    for (auto it{entities.begin()}; it < entities.end(); ++it)
    {
        if (*it == entity)
        {
            delete *it;
            entities.erase(it);
        }
    }
}

std::vector<Entity *> const &World::get_entities() const
{
    return entities;
}

std::vector<Wall> const &World::get_walls() const
{
    return walls;
}

Player *World::get_player() const
{
    return player;
}

Camera &World::get_camera()
{
    return camera;
}

sf::Vector2i World::get_size() const
{
    return size;
}

bool World::can_move(sf::Vector2i pos, Wall::Direction dir) const
{
    sf::Vector2i target{pos};
    switch (dir)
    {
    case Wall::Direction::North:
        target.y -= 1;
        break;
    case Wall::Direction::South:
        target.y += 1;
        break;
    case Wall::Direction::East:
        target.x += 1;
        break;
    case Wall::Direction::West:
        target.x -= 1;
        break;
    }
    for (Wall const &wall : walls)
    {
        Wall::Direction blocking_dir;
        if (wall.position == pos)
        {
            blocking_dir = dir;
        }
        else if (wall.position == target)
        {
            blocking_dir = opposite(dir);
        }
        else
        {
            continue;
        }

        if (wall.direction == blocking_dir)
        {
            return false;
        }
    }
    for (Entity *ent : entities)
    {
        sf::Vector2i ent_pos = ent->get_position();
        if (ent_pos == pos || ent_pos == target)
        {
            Gate *gate = dynamic_cast<Gate *>(ent);
            if (gate != nullptr && !gate->is_open())
            {
                Wall::Direction blocking_dir;
                if (ent_pos == pos)
                {
                    blocking_dir = dir;
                }
                else if (ent_pos == target)
                {
                    blocking_dir = opposite(dir);
                }
                else
                {
                    throw 0;
                }

                if (gate->get_direction() == blocking_dir)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

std::unique_ptr<Item> create_item(File::Object &obj)
{
    std::string &name = obj.name;
    if (name == "Key")
    {
        return std::make_unique<Key>();
    }
    else if (name == "Geiger")
    {
        return std::make_unique<Geiger>();
    }
    else if (name == "Treasure")
    {
        return std::make_unique<Treasure>();
    }
    else
    {
        throw "what";
    }
}

std::unique_ptr<Item> create_item(File::Object &&obj)
{
    return create_item(obj);
}
Entity *create_object(File::Object &obj)
{
    int x = obj.params[0].int_val;
    int y = obj.params[1].int_val;
    std::string &name = obj.name;
    if (name == "Player")
    {
        return new Player{{x, y}};
    }
    else if (name == "Geiger")
    {
        return new Item_Entity{{x, y}, create_item({"Geiger", {}})};
    }
    else if (name == "Mimic")
    {
        return new Mimic{{x, y}};
    }
    else if (name == "Key")
    {
        return new Item_Entity{{x, y}, create_item({"Key", {}})};
    }
    else if (name == "Chest")
    {
        return new Chest{{x, y}, create_item(*obj.params[2].object_val)};
    }
    else if (name == "Lever")
    {
        return new Lever({x, y}, obj.params[2].int_val);
    }
    else if (name == "Gate")
    {
        Wall::Direction dir;
        if (obj.params[2].kind == File::Value::Kind::Integer)
        {
            dir = static_cast<Wall::Direction>(obj.params[2].int_val);
        }
        else
        {
            std::string &str = obj.params[2].object_val->name;
            if (str == "North")
            {
                dir = Wall::Direction::North;
            }
            else if (str == "East")
            {
                dir = Wall::Direction::East;
            }
            else if (str == "South")
            {
                dir = Wall::Direction::South;
            }
            else if (str == "West")
            {
                dir = Wall::Direction::West;
            }
            else
            {
                throw "what";
            }
        }
        int circuit_id = obj.params[3].int_val;
        bool open;
        if (obj.params[4].kind == File::Value::Kind::Integer)
        {
            open = obj.params[4].int_val != 0;
        }
        else
        {
            std::string &str = obj.params[4].object_val->name;
            if (str == "Open")
            {
                open = true;
            }
            else if (str == "Closed")
            {
                open = false;
            }
            else
            {
                throw "what";
            }
        }
        return new Gate{{x, y}, dir, circuit_id, open};
    }
    else
    {
        throw "what";
    }
}
Entity *create_object(File::Object &&obj)
{
    return create_object(obj);
}

World World::load_level(std::string const &path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    World world{};

    Lexer lexer{buffer.str()};
    std::vector<Token> tokens = lexer.lex_all();
    Parser parser{tokens};
    File file_obj;
    if (!parser.parse_file(file_obj))
    {
        throw "Cannot parse level file";
    }
    int width{-1};
    int height{-1};
    for (File::Part &part : file_obj.parts)
    {
        if (part.title == "Meta")
        {
            width = part.properties["Width"].int_val;
            height = part.properties["Height"].int_val;
            world.size = {width, height};
        }
        if (part.title == "Walls")
        {
            if (part.properties.contains("Diagram"))
            {
                std::vector<File::Value> &list{part.properties.at("Diagram").list_val};
                for (int i{0}; i < list.size(); ++i)
                {
                    int x = i % width;
                    int y = i / width;
                    if (list[i].int_val & 1)
                    {
                        world.walls.push_back(Wall{{x, y}, Wall::Direction::East});
                    }
                    if (list[i].int_val & 2)
                    {
                        world.walls.push_back(Wall{{x, y}, Wall::Direction::South});
                    }
                    if (list[i].int_val & 4)
                    {
                        world.walls.push_back(Wall{{x, y}, Wall::Direction::West});
                    }
                    if (list[i].int_val & 8)
                    {
                        world.walls.push_back(Wall{{x, y}, Wall::Direction::North});
                    }
                }
            }
            for (File::Object &obj : part.objects)
            {
                if (obj.name == "Wall")
                {
                    world.walls.push_back(Wall{{obj.params[0].int_val, obj.params[1].int_val}, static_cast<Wall::Direction>(obj.params[2].int_val)});
                }
                else
                {
                    throw "Invalid object in Walls part";
                }
            }
        }
        if (part.title == "Entities")
        {
            for (File::Object &obj : part.objects)
            {
                world.add_entity(create_object(obj));
            }
        }
    }

    world.camera.position.x = width / 2.0;
    world.camera.position.y = height / 2.0;
    float tw = WIDTH / TILE_SIZE;
    float th = HEIGHT / TILE_SIZE;
    float aspect = static_cast<float>(WIDTH) / HEIGHT;
    if (width * aspect > height * aspect)
    {
        world.camera.zoom = tw / width;
    }
    else
    {
        world.camera.zoom = th / height;
    }

    return world;
}