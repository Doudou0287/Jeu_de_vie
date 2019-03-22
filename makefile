CC=gcc
CFLAGS=-g -Wall 
EXEC=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
DOXGEN=doxygen 
#WARNFLAGS := -Wall -Wpedantic -Wextra -Waddress -Waggressive-loop-optimizations \
#  -Wcast-qual -Wcast-align -Wmissing-declarations \
#  -Wdouble-promotion -Wuninitialized -Winit-self \
#  -Wstrict-aliasing -Wsuggest-attribute=const -Wtrampolines -Wfloat-equal \
#  -Wshadow -Wunsafe-loop-optimizations -Wlogical-op \
#  -Wdisabled-optimization -Wconversion -Wunused-result

#all:lavie
#lavie:
	#echo "#!/bin/sh" > $@ && echo "true" >> $@ && chmod u+x $@
#clean:
#	@$(RM) -f lavie *.o
#	@echo Clean!

all:$(EXEC)
main:$(OBJ)
	@$(CC) -o $@ $^ 

check: lavie
	@./test/test_gol_execution.sh

main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
io.o: io.c io.h
jeu.o: jeu.c jeu.h


%.o: %.c
	@$(CC) $(WARNFLAGS) -o $@ -c $< $(CFLAGS)


dist: 
	tar -cvJ -f alkebsi_sundus_Gol_version1.tar.xz makefile Doxyfile

.PHONY: clean mrproper

doc:
	$(DOXGEN)
clean:
	@rm -rf *.o main core

mrproper: clean
	@rm -rf $(EXEC)
        

