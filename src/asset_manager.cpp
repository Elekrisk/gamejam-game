#include "asset_manager.hpp"

template <>
sf::Texture* load_asset(std::string const& path)
{
    sf::Texture *texture{new sf::Texture{}};
    texture->loadFromFile(path);
    return texture;
}


AssetManager asset_manager{};