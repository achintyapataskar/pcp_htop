test: test.o process.o display.o
	gcc -o test process.o test.o display.o -lncurses
process.o: process.h process.c
	gcc -c process.c
test.o: test.c
	gcc -c test.c
display.o: display.c display.h
	gcc -c display.c 
