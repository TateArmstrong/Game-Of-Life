#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>

class Board{
    public:
        const int CELL_SIZE = 8;
        const int WIDTH = 100;
        const int HEIGHT = 75;
        std::vector<std::vector<int>> currentBoard;
        std::vector<std::vector<int>> nextBoard;

        Board(){
            srand(clock());
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    if(rand() % 100 + 1 < 10){
                        currentBoard[x][y] = 1;
                    }
                    else{
                        currentBoard[x][y] = 0;
                    }
                }
            }
        }

        void UpdateCurrentBoard()
        {
            for(int x = 0; x < WIDTH; x++)
            {
                for(int y = 0; y < HEIGHT; y++)
                {
                    currentBoard[x][y] = nextBoard[x][y];
                }
            }
        }

        bool IsOutOfBounds(int row, int col)
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

        // Loops through the eight cells around the specified cell and checks if it is alive -mwindows
        // This function is using currentBoard
        int getCellCount(int row, int col){
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
            /*if(currentBoard[row - 1][col - 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row - 1][col] == 1 && !IsOutOfBounds(row - 1, col)){temp++;}
            if(currentBoard[row - 1][col + 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row][col - 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row][col + 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row + 1][col - 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row + 1][col] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}
            if(currentBoard[row + 1][col + 1] == 1 && !IsOutOfBounds(row - 1, col - 1)){temp++;}*/

            return temp;
        }

        void DrawCells(sf::RenderWindow &win, sf::RectangleShape &cell){
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    // Remember this is using nextBoard
                    if(currentBoard[x][y] == 1){
                        cell.setFillColor(sf::Color::White);
                        cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                        win.draw(cell);
                    }
                    else{
                        cell.setFillColor(sf::Color::Black);
                        cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                        win.draw(cell);
                    }
                }
            }
        }

        void updateCells(){
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    // If the current cell is dead and it has 3 alive neighbors, it becomes alive
                    int cellCount = getCellCount(x, y);
                    switch(currentBoard[x][y]){
                        case 1:
                            if(cellCount <= 1 || cellCount >= 4){nextBoard[x][y] == 0;}
                        case 0:
                            if(cellCount == 3){nextBoard[x][y] = 1;}
                    }
                }
            }
        }
};

int main()
{
    Board board;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Conway's Game of Life");

    sf::RectangleShape cell(sf::Vector2f(8.0f, 8.0f));
    cell.setFillColor(sf::Color::White);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        board.updateCells();
        //Sleep(2000);

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        board.DrawCells(window, cell);

        // end the current frame
        window.display();
        board.UpdateCurrentBoard();
    }

    return 0;
}