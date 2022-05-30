#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <time.h>

const float CELL_SIZE = 64.0f;
const int WIDTH = 10;
const int HEIGHT = 10;
int currentBoard[WIDTH][HEIGHT];
int nextBoard[WIDTH][HEIGHT];

bool isOutOfBounds(int row, int col){
	if(row < 0 || row >= WIDTH){
		return true;
	}
	else if(col < 0 || col >= HEIGHT){
		return true;
	}
	else{
		return false;
	}
}

// Loops through the eight cells around the specified cell and checks if it is alive -mwindows
// This function is using currentBoard
int getCellCount(int row, int col){
    int temp = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
            if (isOutOfBounds(row + x, col + y)){continue;}
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

void drawCells(sf::RenderWindow& win)
{
    sf::CircleShape cell(32.0f);

    for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
        if(currentBoard[x][y] == 1){
            cell.setFillColor(sf::Color::Blue);
            cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            win.draw(cell);
        }
        else{
            cell.setFillColor(sf::Color::Green);
            cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            win.draw(cell);
        }
        // Updating the current board
        currentBoard[x][y] = nextBoard[x][y];
    }
    }
}

void updateCells()
{
    for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
        int cellCount = getCellCount(x, y);
        switch(currentBoard[x][y]){
            // If the current cell is dead and it has 3 alive neighbors, it becomes alive
            case 0:
                if(cellCount == 3){nextBoard[x][y] = 1;}
            // If the current cell is alive 
            case 1:
                if(cellCount < 2 || cellCount > 3){nextBoard[x][y] = 0;}
        }
    }
    }
}

void printBoard()
{
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            if(currentBoard[x][y] == 1){
                std::cout << (char)178 << ' ';
            }
            else{
                std::cout << (char)176 << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "====================" <<std::endl;
}

int main()
{
    srand(time(0));

    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            if(rand() % 100 + 1 < 20){
                currentBoard[x][y] = 1;
            }
            else{
                currentBoard[x][y] = 0;
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(640, 640), "Conway's Game of Life");

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
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
        
        //UpdateCurrentBoard();
        //updateCells();
        //Sleep(2000);
        printBoard();
        std::cin.get();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        //DrawCells(window, cell);
        drawCells(window);

        // end the current frame
        window.display();
        updateCells();
    }

    printBoard();
    std::cin.get();

    return 0;
}