
CC=gcc
OPT= -c -ansi -pedantic -Wall



prog: main.o 
	$(CC) -o prog main.c func_catg.c func_empr.c -g  -Wextra -Wall
main.o: main.c head_catg.h head_empr.h
	$(CC) -o main.o main.c func_catg.c func_empr.c -g -Wextra -Wall

