#include "asset_manager.hpp"

#include <SFML/Audio.hpp>

template <>
sf::Texture* load_asset(std::string const& path)
{
    sf::Texture *texture{new sf::Texture{}};
    texture->loadFromFile(path);
    return texture;
}

template <>
sf::SoundBuffer* load_asset(std::string const& path)
{
    sf::SoundBuffer *sound_buffer{new sf::SoundBuffer{}};
    sound_buffer->loadFromFile(path);
    return sound_buffer;
}


AssetManager asset_manager{};