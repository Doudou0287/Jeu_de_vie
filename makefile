CC=gcc
CFLAGS=-g -Wall 
IFLAGS=-Iinclude
CPATH= src/
OPATH=obj/
DOXGEN=doxygen 
vpath main bin
vpath %.h include
vpath %.o obj
vpath %.c src
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11


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


main: main.o grille.o jeu.o cairo.o
	$(CC) $(CFLAGS) -o $@ $(OPATH)main.o $(OPATH)jeu.o $(OPATH)grille.o $(OPATH)cairo.o $(LDFLAGS)
	mkdir -p bin
	mv main bin/

check: lavie
	@./test/test_gol_execution.sh

main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
cairo.o: cairo.c io.h
jeu.o: jeu.c jeu.h


%.o:
	mkdir -p $(OPATH)
	@$(CC) $(CFLAGS) -c $< $(IFLAGS) $(CPPFLAGS)
	mv $@ $(OPATH)

dist: 
	tar -cvJ -f alkebsi_sundus_Gol_version1.tar.xz makefile Doxyfile

.PHONY: clean mrproper

doc:
	$(DOXGEN)
clean:
	@rm -rf *.o main core

mrproper: clean
	@rm -rf $(EXEC)
        

