#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class TextureManager {
    map<std::string, sf::Texture> textureMap;

public:
    void loadAll();
    sf::Texture& getName(const string& name);
};
