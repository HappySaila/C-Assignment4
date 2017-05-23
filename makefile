compile: 
	clear
	g++ $(SRCDIR)/*.cpp $(CPPFLAGS) -c
	g++ *.o -o $(PROGRAM)

add:
	make compile
	clear
	./$(PROGRAM) -a Lenna_hat_mask.pgm Lenna_standard.pgm  
	open Add.pgm	

sub:
	make compile
	clear
	./$(PROGRAM) -s Lenna_hat_mask.pgm Lenna_standard.pgm
	open Sub.pgm

invert:
	make compile
	clear
	./$(PROGRAM) -i Lenna_standard.pgm
	open Invert.pgm

thresh:
	make compile
	clear
	./$(PROGRAM) -t Lenna_standard.pgm 125
	open Thresh.pgm

CPPFLAGS = -std=c++11

SRCDIR = ./src
PROGRAM = main

clean :
	rm *.o
	rm $(PROGRAM)

