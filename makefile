run : 
	clear
	g++ $(SRCDIR)/*.cpp $(CPPFLAGS) -c
	g++ *.o -o $(PROGRAM)
	clear
	./$(PROGRAM) -a Lenna_hat_mask.pgm Lenna_standard.pgm  



CPPFLAGS = -std=c++11

SRCDIR = ./src
PROGRAM = main

clean :
	rm *.o
	rm $(PROGRAM)

