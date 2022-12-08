main: main.o tools.o
	gcc -g -o main.exe main.o tools.o -lm

main.o: main.c tools.h
	gcc -c main.c
 
tools.o: tools.c tools.h
	gcc -c tools.c