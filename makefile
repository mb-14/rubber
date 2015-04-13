all:
	g++ main.cpp util.cpp game.cpp -lGL -lglut -lGLU -std=c++11 -o rubber

clean:
	rm rubber	
