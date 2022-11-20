#include "treasure.hpp"
#include "asset_manager.hpp"

Treasure::Treasure() : Item{asset_manager.load<sf::Texture>("assets/blue_gem.png")} {}
