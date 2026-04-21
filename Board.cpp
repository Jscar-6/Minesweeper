#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
using namespace std;


Board::Board(int rows, int cols, int mineCount, TextureManager& textures)
    : rows(rows), cols(cols), mineCount(mineCount), textures(textures), rng(std::random_device{}()) {
        grid.resize(rows, vector<Tile>(cols));
        
        for (int r = 0; r < rows; r++){ //settnig up the tiles n sprite w/ position and texture/position of texture
            for (int c = 0; c < cols; c++){
                grid[r][c].row = r;
                grid[r][c].col = c;

                grid[r][c].sprite.setTexture(textures.getTexture("tile_hidden"));
                grid[r][c].sprite.setPosition(c * 32.f, r * 32.f);
            }
        }
        this->placeMines();
        this->findAdjacents();
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
    Tile& tile = grid[row][col];
    if (tile.isMine) {
        tile.sprite.setTexture(textures.getTexture("mine"));
    } else if (tile.adjacentMines > 0) {
        tile.sprite.setTexture(textures.getTexture("number_" + std::to_string(tile.adjacentMines)));
    } else {
        tile.sprite.setTexture(textures.getTexture("tile_revealed"));
    }
}

void Board::placeMines() {
    std::uniform_int_distribution<int> rowDist(0, this->rows - 1);
    std::uniform_int_distribution<int> colDist(0, this->cols - 1);
    int placed = 0;
    while (placed < mineCount) {
        int row = rowDist(rng);
        int col = colDist(rng);
        if (!grid[row][col].isMine) {
            grid[row][col].isMine = true;
            placed++;
        }
    }
}

void Board::findAdjacents() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c].isMine) continue; 
            int count = 0;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;  
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;  
                    if (grid[nr][nc].isMine) count++;
                }
            }
            grid[r][c].adjacentMines = count;
        }
    }
}