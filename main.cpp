#include <SFML/Graphics.hpp>

const int CELL_SIZE = 8;
const int WIDTH = 800;
const int HEIGHT = 600;
int currentBoard[WIDTH][HEIGHT];
int nextBoard[WIDTH][HEIGHT];

int main()
{
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

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        //window.draw(circle);
        for(int x = 0; x < WIDTH; x++){
            for(int y = 0; y < HEIGHT; y++){
                if(currentBoard[x][y] == 1){
                    cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                    window.draw(cell);
                }
            }
        }

        // end the current frame
        window.display();
    }

    return 0;
}