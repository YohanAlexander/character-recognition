main: main.o Image.o Mask.o
	g++ -Wall -o3 main.o Image.o Mask.o -o main

main.o: main.cpp
	g++ -c -Wall main.cpp

Image.o: Image.cpp Image.hpp
	g++ -c -Wall Image.cpp

Mask.o: Mask.cpp Mask.hpp
	g++ -c -Wall Mask.cpp

clean:
	rm *.o main
