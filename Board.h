#pragma once
#include <vector>
#include "Tile.h"
#include "TextureManager.h"


struct Board {
    int rows;
    int cols;
    int mineCount;
    std::vector<std::vector<Tile>> grid;   // 2D grid

    TextureManager& textures;

    Board(int rows, int cols, int mineCount, TextureManager& textures);

    void reset();               
    void placeMines();          
    void computeAdjacency();   
    void linkNeighbors();      

    void draw(sf::RenderWindow& window); 
    void mouseClickHandle(int x, int y, bool leftClick);
};