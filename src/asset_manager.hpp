#pragma once

#include <tuple>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <typename T>
T* load_asset(std::string const& path) = delete;

template <>
sf::Texture* load_asset<sf::Texture>(std::string const& path);
template <>
sf::SoundBuffer* load_asset<sf::SoundBuffer>(std::string const& path);

template <typename... T>
class AssetManager_
{
    std::tuple<std::map<std::string, T *>...> assets;

public:
    ~AssetManager_()
    {
        auto destruct = [](auto map){ for (auto pair : map) { delete pair.second; } };
        std::apply([&destruct](auto ...map){ ((destruct(map)),...); }, assets);
    }

    template <typename V>
    V *load(std::string const &path)
    {
        std::map<std::string, V *> &map = std::get<std::map<std::string, V *>>(assets);
        if (map.contains(path))
        {
            return map.find(path)->second;
        }
        else
        {
            V* asset = load_asset<V>(path);
            map.emplace(path, asset);
            // map.insert(path, asset);
            return asset;
        }
    }
};

typedef AssetManager_<sf::Texture, sf::SoundBuffer> AssetManager;


extern AssetManager asset_manager;
