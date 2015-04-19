CFLAGS =-std=c++11
LDFLAGS=-lopenal -lalut -lGL -lglut -lGLU -pthread
all:
	g++ $(CFLAGS) main.cpp util.cpp game.cpp $(LDFLAGS) -o rubber 

clean:
	rm rubber	
