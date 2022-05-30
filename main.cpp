#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <time.h>

// Size of the cells in pixels
const float CELL_SIZE = 8.0f;
// Initial spawn chance out of 100
const int INITIAL_SPAWN_WEIGHT = 20;
// Width and Height of the screen in CELL_SIZE. ex. if CELL_SIZE = 8 and WIDTH = 100 the width of the window
// would be 800 in pixels
const int WIDTH = 100;
const int HEIGHT = 75;
// 2D array repesenting the game board
int currentBoard[WIDTH][HEIGHT];
int nextBoard[WIDTH][HEIGHT];

// Checks to see if the specified cell coordinate is out of bounds, returns true if out of bounds
bool isOutOfBounds(int row, int col)
{
	if(row < 0 || row >= WIDTH)
		return true;
	else if(col < 0 || col >= HEIGHT)
		return true;
	else
		return false;
}

// Returns the number of alive cells around the specified cell position
int getCellCount(int row, int col)
{
    int temp = 0;
	for(int x = -1; x <= 1; x++){
	for(int y = -1; y <= 1; y++){

        if (isOutOfBounds(row + x, col + y))
            continue;
        if (x == 0 && y == 0)
            continue;
        if (currentBoard[row + x][col + y] == 1)
            temp++;
	}
	}
	return temp;
}

// Draws the cells to the screen with specified colors
void drawCells(sf::RenderWindow& win, sf::Color aliveColor, sf::Color deadColor)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
        if(currentBoard[x][y] == 1){
            cell.setFillColor(aliveColor);
            cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            win.draw(cell);
        }
        else{
            cell.setFillColor(deadColor);
            cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            win.draw(cell);
        }
        // Updating the current board
        currentBoard[x][y] = nextBoard[x][y];
    }
    }
}

// Updates the nextBoard with Game of Life rules
void updateCells()
{
    for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){

        int cellCount = getCellCount(x, y);

        switch(currentBoard[x][y]){
            // If the current cell is dead and it has 3 alive neighbors, it becomes alive
            case 0:
                if(cellCount == 3){nextBoard[x][y] = 1;}break;
            // If the current cell is alive and has less than 2 and greater than 3 neighbors, it dies.
            case 1:
                if(cellCount < 2 || cellCount > 3){nextBoard[x][y] = 0;}break;
        }
    }
    }
}

// Initalizes the boards with random alive cells
void initBoards()
{
    srand(time(0));

    for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
        if(rand() % 100 + 1 < INITIAL_SPAWN_WEIGHT){
            currentBoard[x][y] = 1;
            nextBoard[x][y] = 1;
        }
        else{
            currentBoard[x][y] = 0;
            nextBoard[x][y] = 0;
        }
    }
    }
}

int main()
{
    initBoards();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Conway's Game of Life");

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

        // clear the window with black color
        window.clear(sf::Color::Black);

            // draw everything here...
            drawCells(window, sf::Color::Blue, sf::Color::Green);

        // end the current frame
        window.display();
        updateCells();
    }

    return 0;
}