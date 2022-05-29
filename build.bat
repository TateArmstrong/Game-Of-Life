g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o
g++ -IC:\SFML-2.5.1\include -c Board.cpp
g++ -LC:\SFML-2.5.1\lib -static .\Board.o .\main.o -o GameOfLife.exe -lsfml-graphics -lsfml-window -lsfml-system -mwindows
#del main.o Board.o
GameOfLife.exe