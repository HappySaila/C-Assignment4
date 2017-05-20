run : 
	g++ $(SRCDIR)/*.cpp $(CPPFLAGS) -c
	g++ *.o -o $(PROGRAM)
	./$(PROGRAM)



CPPFLAGS = -std=c++11

SRCDIR = ./src
PROGRAM = main

clean :
	rm $(SRCDIR)/*.o

