#include "Board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

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
        
        board.UpdateCells();
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