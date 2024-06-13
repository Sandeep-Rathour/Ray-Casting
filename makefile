all: link compile run

link: 
	g++ -c main.cpp -I/home/documents/SFML.2.6.1/include/SFML

compile: 
	g++ main.o -o main -lsfml-system -lsfml-window -lsfml-graphics

run:
	./main

c: 
	rm main.o main -f