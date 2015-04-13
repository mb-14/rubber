#ifndef GAME_H    
#define GAME_H
#include <random>
using namespace std;
class Game{

	public:
	float x1,x2,y,angle;
	float pipe_x[3];
	float pipe_x_max;
	bool gameOver;
	int score,highscore;
	float t; //Jump time
	bool jump;
	random_device rd; 
	uniform_int_distribution<> distr; 
	const float pipe_min_diff = 220.0f;
	const float u_y = 50.0f; //Initial jump velocity
	const float g_y = 10.0f; //Gravitational acc
	void newGame();
	void update();
	bool collision(int);
	void saveHighScore();
	int getHighScore();
};

#endif
