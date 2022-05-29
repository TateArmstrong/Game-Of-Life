all: main.o

main.o: main.cpp
	g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o

clean:
	del *.o
