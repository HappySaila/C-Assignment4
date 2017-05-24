compile: 
	clear
	g++ $(SRCDIR)/*.cpp $(CPPFLAGS) -c
	g++ *.o -o $(PROGRAM)
	mv *.o $(BINDIR)

add:
	make compile
	clear
	./$(PROGRAM) -a Lenna_hat_mask.pgm Lenna_standard.pgm  
	mv Add.pgm CreatedImages
	cd CreatedImages && open Add.pgm	

sub:
	make compile
	clear
	./$(PROGRAM) -s Lenna_hat_mask.pgm Lenna_standard.pgm
	mv Sub.pgm CreatedImages	
	cd CreatedImages && open Sub.pgm

invert:
	make compile
	clear
	./$(PROGRAM) -i Lenna_standard.pgm
	mv Invert.pgm CreatedImages
	cd CreatedImages && open Invert.pgm

thresh:
	make compile
	clear
	./$(PROGRAM) -t Lenna_standard.pgm 125
	mv Thresh.pgm CreatedImages	
	cd CreatedImages && open Thresh.pgm

mask:
	make compile
	clear
	./$(PROGRAM) -l Lenna_hat_mask.pgm Lenna_standard.pgm
	mv Mask.pgm CreatedImages	
	cd CreatedImages && open Mask.pgm

test:
	clear
	g++ catch.hpp test.cpp $(SRCDIR)/Image.cpp $(CPPFLAGS) -c
	g++ *.o -o testMain
	clear
	./testMain
	mv test1.pgm CreatedImages
	mv test2.pgm CreatedImages
	mv catch.hpp.gch $(BINDIR)
	rm testMain
	make clean

CPPFLAGS = -std=c++11

SRCDIR = ./src
BINDIR = ./bin
SRCIMG = ./SourceImages
PROGRAM = main

clean :
	cd CreatedImages && rm *
	cd $(BINDIR) && rm *

