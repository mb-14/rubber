all:
	g++ main.cpp util.cpp game.cpp -lopenal -lalut -lGL -lglut -lGLU -pthread -std=c++11 -o rubber

clean:
	rm rubber	
