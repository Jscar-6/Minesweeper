#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

void TextureManager::loadAll(){
    textureMap["mine"].loadFromFile("images/mine.png");
    textureMap["tile_hidden"].loadFromFile("images/tile_hidden.png");
    textureMap["tile_revealed"].loadFromFile("images/tile_revealed.png");
    textureMap["flag"].loadFromFile("images/flag.png");
    textureMap["number_1"].loadFromFile("images/number_1.png");
    textureMap["number_2"].loadFromFile("images/number_2.png");
    textureMap["number_3"].loadFromFile("images/number_3.png");
    textureMap["number_4"].loadFromFile("images/number_4.png");
    textureMap["number_5"].loadFromFile("images/number_5.png");
    textureMap["number_6"].loadFromFile("images/number_6.png");
    textureMap["number_7"].loadFromFile("images/number_7.png");
    textureMap["number_8"].loadFromFile("images/number_8.png");
    textureMap["face_happy"].loadFromFile("images/face_happy.png");
    textureMap["face_win"].loadFromFile("images/face_win.png");
    textureMap["face_lose"].loadFromFile("images/face_lose.png");
    textureMap["digits"].loadFromFile("images/digits.png");
    textureMap["debug"].loadFromFile("images/debug.png");
    textureMap["test_1"].loadFromFile("images/test_1.png");
    textureMap["test_2"].loadFromFile("images/test_2.png");
    textureMap["test_3"].loadFromFile("images/test_3.png");
};

sf::Texture& TextureManager::getTexture(const string& name){
    return textureMap[name];
}