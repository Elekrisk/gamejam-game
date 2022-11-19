#include "world.hpp"
#include "player.hpp"

#include <fstream>
#include <sstream>

World::World() : entities{} {}

World::~World()
{
    for (Entity *ent : entities)
    {
        delete ent;
    }
}

void World::add_entity(Entity *entity)
{
    entities.push_back(entity);
}

std::vector<Entity *> const &World::get_entities() const
{
    return entities;
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
    return true;
}

enum TokenKind
{
    Integer,
    Word,
    LBracket,
    RBracket,
    LParen,
    RParen,
    Comma,
    Colon,
    Eof,
};

struct Token
{
    TokenKind kind;
    int int_val;
    std::string string_val;

    Token(TokenKind kind, int val) : kind{kind}, int_val{val} {}
    Token(TokenKind kind, std::string val) : kind{kind}, string_val{val} {}
};

class Lexer
{
    std::string all;
    size_t index;

public:
    Lexer(std::string const &all) : all{all}, index{0} {}

    class Exception : public std::exception
    {
        char ch;
        std::string msg;

    public:
        Exception(char ch) : ch{ch}
        {
            std::stringstream ss{};
            ss << "Unexpected character '" << ch << "'.";
        }
        virtual char const *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
        {
            return msg.data();
        }
    };

    Token lex()
    {
        if (index >= all.length())
        {
            return {TokenKind::Eof, 0};
        }
        char c = all[index++];
        switch (c)
        {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return lex();
        case '[':
            return {TokenKind::LBracket, 0};
        case ']':
            return {TokenKind::RBracket, 0};
        case '(':
            return {TokenKind::LParen, 0};
        case ')':
            return {TokenKind::RParen, 0};
        case ',':
            return {TokenKind::Comma, 0};
        case ':':
            return {TokenKind::Colon, 0};
        default:
            break;
        }
        auto int_test = [](char c)
        { return c >= '0' && c <= '9'; };
        if (int_test(c))
        {
            std::string buffer{};
            buffer += c;
            while (index + 1 < all.length() && int_test(all[index]))
            {
                buffer += all[index++];
            }
            return {TokenKind::Integer, std::stoi(buffer)};
        }
        auto ident_test = [](char c)
        { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); };
        if (ident_test(c))
        {
            std::string buffer{};
            buffer += c;
            while (index + 1 < all.length() && ident_test(all[index]))
            {
                buffer += all[index++];
            }
            return {TokenKind::Word, std::move(buffer)};
        }
        throw Exception(c);
    }

    std::vector<Token> lex_all()
    {
        std::vector<Token> tokens{};
        while (true)
        {
            Token tok = lex();
            tokens.push_back(tok);
            if (tok.kind == TokenKind::Eof)
            {
                return tokens;
            }
        }
    }
};

struct File
{
    struct Object
    {
        std::string name;
        std::vector<int> params;
    };

    struct Property
    {
        std::string name;
        int value;
    };

    struct Line
    {
        enum Kind
        {
            Property,
            Object,
        };

        Kind kind;
        union
        {
            File::Property prop;
            File::Object obj;
        };
    };

    struct Part
    {
        std::string title;
        std::vector<Object> objects;
        std::map<std::string, int> properties;
    };

    std::vector<Part> parts;
};

class Parser
{
    std::vector<Token> tokens;
    int index;

public:
    Parser(std::vector<Token> const &tokens) : tokens{tokens}, index{0} {}

    bool parse_object(File::Object &obj)
    {
        std::string name;
        std::vector<int> params;
        int start = index;
        if (tokens[index].kind != TokenKind::Word)
        {
            index = start;
            return false;
        }
        name = tokens[index++].string_val;
        if (tokens[index++].kind != TokenKind::LParen)
        {
            index = start;
            return false;
        }
        while (tokens[index].kind != TokenKind::RParen)
        {
            if (tokens[index].kind != TokenKind::Integer)
            {
                index = start;
                return false;
            }
            params.push_back(tokens[index++].int_val);
            if (tokens[index].kind == TokenKind::Comma)
            {
                index++;
            }
        }
        index++;
        obj.name = std::move(name);
        obj.params = std::move(params);
        return true;
    }
    bool parse_property(File::Property &prop)
    {
        std::string name;
        int val;
        int start = index;
        if (tokens[index].kind != TokenKind::Word)
        {
            index = start;
            return false;
        }
        name = tokens[index++].string_val;
        if (tokens[index++].kind != TokenKind::Colon)
        {
            index = start;
            return false;
        }
        if (tokens[index].kind != TokenKind::Integer)
        {
            index = start;
            return false;
        }
        val = tokens[index++].int_val;
        prop.name = std::move(name);
        prop.value = val;
        return true;
    }

    bool parse_line(File::Part &current_part)
    {
        File::Object obj;
        if (parse_object(obj))
        {
            current_part.objects.push_back(std::move(obj));
            return true;
        }
        File::Property prop;
        if (parse_property(prop))
        {
            current_part.properties.emplace(prop.name, prop.value);
            return true;
        }
        return false;
    }

    bool parse_part(File::Part &part)
    {
        int start = index;
        if (tokens[index++].kind != TokenKind::LBracket)
        {
            index = start;
            return false;
        }
        if (tokens[index].kind != TokenKind::Word)
        {
            index = start;
            return false;
        }
        part.title = tokens[index++].string_val;
        if (tokens[index++].kind != TokenKind::RBracket)
        {
            index = start;
            return false;
        }

        while (parse_line(part))
        {
        }
        return true;
    }

    bool parse_file(File &file)
    {
        File::Part part;
        while (parse_part(part))
        {
            file.parts.push_back(std::move(part));
        }
        return tokens[index].kind == TokenKind::Eof;
    }
};

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
            width = part.properties["Width"];
            height = part.properties["Height"];
        }
        if (part.title == "Walls")
        {
            for (File::Object &obj : part.objects)
            {
                if (obj.name == "Wall")
                {
                    world.walls.push_back(Wall{{obj.params[0], obj.params[1]}, static_cast<Wall::Direction>(obj.params[2])});
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
                int x = obj.params[0];
                int y = obj.params[1];
                std::string &name = obj.name;
                if (name == "Player")
                {
                    world.add_entity(new Player{{x, y}});
                }
            }
        }
    }
    return world;
}