all: main.o Board.o BoardTest.o
	g++ -LC:\SFML-2.5.1\lib Board.o main.o -o GameOfLife -lsfml-graphics -lsfml-window -lsfml-system -mwindows

main.o: main.cpp
	g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o

Board.o: Board.cpp
	g++ -IC:\SFML-2.5.1\include -c Board.cpp -o Board.o

BoardTest.o: BoardTest.cpp
	g++ -IC:\SFML-2.5.1\include -c BoardTest.cpp -o BoardTest.o

BoardTest:
	g++ -LC:\SFML-2.5.1\lib Board.o BoardTest.o -o BoardTest -lsfml-graphics -lsfml-window -lsfml-system -mwindows

clean:
	del *.o