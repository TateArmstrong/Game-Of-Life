#include "Board.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

Board::Board()
{
    srand(clock());
    currentBoard.resize(WIDTH);
    nextBoard.resize(HEIGHT);
    for(int x = 0; x < WIDTH; x++)
    {
        currentBoard[x].resize(WIDTH);
        nextBoard[x].resize(HEIGHT);
        for(int y = 0; y < HEIGHT; y++)
        {
            if(rand() % 100 + 1 < 10)
            {
                currentBoard[x][y] = 1;
            }
            else
            {
                currentBoard[x][y] = 0;  
            }
        }
    }
}

void Board::UpdateCurrentBoard()
{
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            currentBoard[x][y] = nextBoard[x][y];
        }
    }
}

bool Board::IsOutOfBounds(int row, int col)
{
    if(row < 0 || row >= WIDTH)
    {
        return true;
    }
    else if(col < 0 || col >= HEIGHT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Board::GetCellCount(int row, int col){
    int temp = 0;

    for(int x = -1; x < 2; x++){
        for(int y = -1; y < 2; y++){
            if (IsOutOfBounds(row + x, col + y)){continue;}
            if (x == 0 && y == 0){continue;}
            if (currentBoard[row + x][col + y] == 1){
                temp++;
            }
        }
    }

    return temp;
}

void Board::DrawCells(sf::RenderWindow& win, sf::RectangleShape& cell)
{
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            // Remember this is using nextBoard
            if(currentBoard[x][y] == 1)
            {
                cell.setFillColor(sf::Color::White);
                cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                win.draw(cell);
            }
            else
            {
                cell.setFillColor(sf::Color::Black);
                cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                win.draw(cell);
            }
        }
    }
}

void Board::UpdateCells(){
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            // If the current cell is dead and it has 3 alive neighbors, it becomes alive
            int cellCount = GetCellCount(x, y);
            switch(currentBoard[x][y])
            {
                case 1:
                    if(cellCount <= 1 || cellCount >= 4){nextBoard[x][y] == 0;}
                case 0:
                    if(cellCount == 3){nextBoard[x][y] = 1;}
            }
        }
    }
}