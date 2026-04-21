#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Tile {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int adjacentMines = 0;

    int row = 0;
    int col = 0;

    sf::Sprite sprite;
    // Neighbors tiles vector
    std::vector<Tile*> neighbors;
};