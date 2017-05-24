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
	mv $(PROGRAM) $(BINDIR)

sub:
	make compile
	clear
	./$(PROGRAM) -s Lenna_hat_mask.pgm Lenna_standard.pgm
	mv Sub.pgm CreatedImages	
	cd CreatedImages && open Sub.pgm
	mv $(PROGRAM) $(BINDIR)

invert:
	make compile
	clear
	./$(PROGRAM) -i Lenna_standard.pgm
	mv Invert.pgm CreatedImages
	cd CreatedImages && open Invert.pgm
	mv $(PROGRAM) $(BINDIR)

thresh:
	make compile
	clear
	./$(PROGRAM) -t Lenna_standard.pgm 125
	mv Thresh.pgm CreatedImages	
	cd CreatedImages && open Thresh.pgm
	mv $(PROGRAM) $(BINDIR)

mask:
	make compile
	clear
	./$(PROGRAM) -l Lenna_hat_mask.pgm Lenna_standard.pgm
	mv Mask.pgm CreatedImages	
	cd CreatedImages && open Mask.pgm
	mv $(PROGRAM) $(BINDIR)

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
	mv *.o $(BINDIR)
	make clean

CPPFLAGS = -std=c++11

SRCDIR = ./src
BINDIR = ./bin
SRCIMG = ./SourceImages
PROGRAM = main

clean :
	cd $(BINDIR) && rm *
	cd CreatedImages && rm *

