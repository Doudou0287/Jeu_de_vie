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


ifeq (TEXTE,$(MODE))
main: main.o libjeu.a io.o
	$(CC) $(CFLAGS) -o $@ $(OPATH)main.o $(OPATH)jeu.o $(OPATH)grille.o $(OPATH)io.o $(LDFLAGS)
	mkdir -p bin
	mv main bin/

check: lavie
	@./test/test_gol_execution.sh

main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
io.o: io.c io.h
jeu.o: jeu.c jeu.h


%.o:
	mkdir -p $(OPATH)
	@$(CC) $(CFLAGS) -c $< $(IFLAGS) $(CPPFLAGS)
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mv libjeu.a lib/

else
main : main2.o libjeu.a cairo.o
	$(CC) $(CFLAGS) -o $@ $(OPATH)main2.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)cairo.o $(LDFLAGS)
	mkdir -p bin
	mv main bin/
	
main2.o: main2.c grille.h io.h jeu.h 
grille.o: grille.c grille.h
cairo.o: cairo.c io.h	
jeu.o: jeu.c jeu.h

%.o: 
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -c $<  $(CPPFLAGS)
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	mkdir -p lib
	ranlib libjeu.a
	mv libjeu.a lib/

endif

dist: 
	tar -cvJ -f alkebsi_sundus_Gol_version1.tar.xz makefile Doxyfile

.PHONY: clean mrproper

doc:
	$(DOXGEN)
clean:
	@rm -rf obj/* bin/* 
        

