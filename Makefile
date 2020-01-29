main: main.o Image.o
	g++ -Wall -o3 main.o Image.o -o main

main.o: main.cpp
	g++ -c -Wall main.cpp

Image.o: Image.cpp Image.hpp
	g++ -c -Wall Image.cpp

clean:
	rm *.o main
