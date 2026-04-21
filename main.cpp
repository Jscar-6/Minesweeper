#include <SFML/Graphics.hpp>
#include "TextureManager.h"


int main(){
    TextureManager textures;
    textures.loadAll();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Proj3");

    sf::Sprite testSprite;
    testSprite.setTexture(textures.getName("tile_hidden"));
    testSprite.setPosition(0.f, 0.f);

    window.clear(sf::Color::White);
    window.draw(testSprite);
    window.display();
}