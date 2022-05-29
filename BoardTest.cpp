#include "Board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

int main()
{
    Board board;

    /*for(int x = 0; x < board.WIDTH; x++){
        for(int y = 0; y < board.HEIGHT; y++){
            std::cout << board.currentBoard[x][y] << ", ";
        }
        std::cout << std::endl;
    }*/
    for(int x = 0; x < board.currentBoard.size(); x++){
        for(int y = 0; y < board.currentBoard[x].size(); y++){
            std::cout << board.currentBoard[x][y] << ", ";
        }
        std::cout << std::endl;
    }
    std::cin.get();

    return 0;
}
