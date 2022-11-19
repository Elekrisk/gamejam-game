#include "geiger.hpp"
#include "asset_manager.hpp"

Geiger::Geiger() : Item{asset_manager.load<sf::Texture>("assets/geiger.png")} {}

void Geiger::use_item(Entity* target, World& world) {}