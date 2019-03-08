CC=gcc
CFLAGS=-g -Wall 
EXEC=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)
main:$(OBJ)
	@$(CC) -o $@ $^ 

main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
io.o: io.c io.h
jeu.o: jeu.c jeu.h


%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

dist: 
	tar -cvJ -f archiv.tar.xz makefile Doxyfile

.PHONY: clean mrproper

clean:
	@rm -rf *.o main core

mrproper: clean
	@rm -rf $(EXEC)
        

