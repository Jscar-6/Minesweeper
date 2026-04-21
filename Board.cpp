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

void Board::tileReveal(int r, int c) {
  
    if (r < 0 or r >= rows or c < 0 or c >= cols) return;

    Tile& tile = grid[r][c];

    if (tile.isRevealed or tile.isFlagged) return;

    tile.isRevealed = true;

    if (tile.isMine) {
        tile.sprite.setTexture(textures.getTexture("mine"));
        // game-over Screen!
        return;
    }

    if (tile.adjacentMines > 0) {
        tile.sprite.setTexture(
            textures.getTexture("number_" + std::to_string(tile.adjacentMines))
        );
    } else {
        tile.sprite.setTexture(textures.getTexture("tile_revealed"));
        // recursive reveal
        for (int drow = -1; drow <=1; drow++){
            for (int dcol = -1; dcol <= 1; dcol++) {
                if (drow == 0 && dcol == 0){
                    continue;
                }
                tileReveal(r + drow, c + dcol);
            } 
        }
    }
}

void Board::mouseClickHandle(int x, int y, bool leftClick) {
    int col = x / 32;
    int row = y / 32;
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;

    if (leftClick) {
        tileReveal(row, col);
    } else {
        //falg
        Tile& tile = grid[row][col];
        if (tile.isRevealed) return;
        if (tile.isFlagged == false) {
            tile.isFlagged = true;
            tile.sprite.setTexture(textures.getTexture("flag"));
        } else {
            tile.isFlagged = false;
            tile.sprite.setTexture(textures.getTexture("tile_hidden"));
        }
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