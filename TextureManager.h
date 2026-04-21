#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager {
    std::map<std::string, sf::Texture> textureMap;

public:
    void loadAll();
    sf::Texture& getTexture(const std::string& name);
};
