main: main.o tools.o
	gcc -o main.exe main.o tools.o

main.o: main.c tools.h
	gcc -c main.c
 
tools.o: tools.c tools.h
	gcc -c tools.c