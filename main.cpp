#include <SFML/Graphics.hpp>
#include <iostream>

const int CELL_SIZE = 8;
const int WIDTH = 100;
const int HEIGHT = 75;
int currentBoard[WIDTH][HEIGHT];
int nextBoard[WIDTH][HEIGHT];

bool IsOutOfBounds(int row, int col){
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

// Loops through the eight cells around the specified cell and checks if it is alive
// This function is using currentBoard
int getCellCount(int row, int col){
    int temp = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
            if (IsOutOfBounds(row + x, col + y)){continue;}
            if (currentBoard[row + x][col + y] == 1){
                temp++;
            }
		}
	}
	return temp;
}

void DrawCells(sf::RenderWindow &win, sf::RectangleShape &cell){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            // Remember this is using nextBoard
            if(nextBoard[x][y] == 1){
                cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                win.draw(cell);
            }
        }
    }
    // Updating next board
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            currentBoard[x][y] = nextBoard[x][y];
        }
    }
}

void updateCells(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            // If the current cell is dead and it has 3 alive neighbors, it becomes alive
            switch(currentBoard[x][y]){
                case 0:
                    if(getCellCount(x, y) == 3){nextBoard[x][y] = 1;}break;
                case 1:
                    if(getCellCount(x, y) <= 1 || getCellCount(x, y) >= 4){nextBoard[x][y] == 0;}break;
            }
        }
    }
}

int main()
{
    for(int x = 0; x < 50; x++){
        currentBoard[x][0] = 1;
    }
    currentBoard[4][4] = 1;

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

        updateCells();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        DrawCells(window, cell);

        // end the current frame
        window.display();
    }

    return 0;
}