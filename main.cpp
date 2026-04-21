#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Board.h"


int main(){
    
    TextureManager textures;
    textures.loadAll();

    int cols = 25;
    int rows = 16;
    int mines = 50;

    sf::RenderWindow window(sf::VideoMode(cols * 32, rows * 32 + 100), "Proj3");
    
    Board board(rows, cols, mines, textures);

    while (window.isOpen()){
       sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                bool isLeft = (event.mouseButton.button == sf::Mouse::Left);
                board.mouseClickHandle(x, y, isLeft);
            }
            
        }

        window.clear(sf::Color::White);
        board.draw(window);
        window.display();
    }
}