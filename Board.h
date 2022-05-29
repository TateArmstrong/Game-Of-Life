#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Board
{
    public:
        const int CELL_SIZE = 8;
        const int WIDTH = 100;
        const int HEIGHT = 75;
        std::vector<std::vector<int>> currentBoard;
        std::vector<std::vector<int>> nextBoard;

        Board();
        void UpdateCurrentBoard();
        bool IsOutOfBounds(int row, int col);
        int GetCellCount(int row, int col);
        void DrawCells(sf::RenderWindow &win, sf::RectangleShape &cell);
        void UpdateCells();
};