#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
using namespace std;


Board::Board(int rows, int cols, int mineCount, TextureManager& textures)
    : rows(rows), cols(cols), mineCount(mineCount), textures(textures) {
        grid.resize(rows, vector<Tile>(cols));
        
        for (int r = 0; r < rows; r++){ //settnig up the tiles n sprite w/ position and texture/position of texture
            for (int c = 0; c < cols; c++){
                grid[r][c].row = r;
                grid[r][c].col = c;

                grid[r][c].sprite.setTexture(textures.getTexture("tile_hidden"));
                grid[r][c].sprite.setPosition(c * 32.f, r * 32.f);
            }
        }
    }

void Board::draw(sf::RenderWindow& window) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            window.draw(grid[r][c].sprite);
        }
    }
}

void Board::mouseClickHandle(int x, int y, bool leftClick){
    int col = x / 32;
    int row = y / 32;
    
    std::cout << "clicked tile " << row << "," << col << std::endl;
}