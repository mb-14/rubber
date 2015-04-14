#include "game.h"
using namespace std;

void Game::newGame(){
	//eng.seed(rd); 
	distr = uniform_int_distribution<>(1000,1400);
	score = 0;
	highscore = getHighScore();
	x1=0;
	x2=1000;
	y=0;
	t=0;
	gameOver = jump = false;
	angle=0;
	pipe_x[0]=1000;
	pipe_x[1]=1400;
	pipe_x_max = pipe_x[2] = 1700;
	}

void Game::loadWAVs(){
	bading = loadWAV("res/bading.wav");
	smack = loadWAV("res/smack.wav");
	flap = loadWAV("res/flap.wav");
}
	
void Game::update(){
	 
     if(x1<-1000){
     x1=990;
     score++;
     playWAV(bading,0);	
     }
    if(x2<-1000)
     {x2=990;
      score++;
      playWAV(bading,0);	
     }  
     if(angle<-360)
      angle=0; 
    
     for(int i=0;i<3;i++){
    	if(pipe_x[i]<-40){
    		do{
    	 		pipe_x[i]=distr(rd);
    		}while(pipe_x[i]-pipe_x_max<pipe_min_diff);
    		pipe_x_max = pipe_x[i];
    	}
    	if(collision(i)){
    	   playWAV(smack,1);
    	   gameOver = true;
    	   return;
    	   }
    }
    if(jump==true){
    	if(t<=0.4)
    		playWAV(flap,2);
    	t+=0.4;
    	y = u_y*t-(g_y*t*t/2);
    	if(t>=10){
    		jump=false;
    		t=0;
    		y=0;
    	}
    }
    x1-=10;
    x2-=10;
    angle-=10;
    for(int i=0;i<3;i++)
    	pipe_x[i]-=10;
   	pipe_x_max-=10;
}


bool Game::collision(int i){
	float d=0;
	if(pipe_x[i] > 100)
	 	d+=(pipe_x[i] -100)*(pipe_x[i] -100);
	else if(pipe_x[i] + 40< 100)
		d+=(100-pipe_x[i]-40)*(100-pipe_x[i]-40);
	if(y+25 > 77)	 
	 d+=(y+25-77)*(y+25-77); 

	return d <= 625;
}

void Game::saveHighScore(){
  FILE * file;
  file = fopen("score", "w" );
   if (file != NULL) {
        fwrite(&highscore, sizeof(int),1,file);
        fclose(file);
    }
}

int Game::getHighScore(){
	FILE * file = fopen("score", "r");
    int new_val[1];
    if (file != NULL) {
         fread((void *)new_val, sizeof(int), 1, file);
        fclose(file);
    }
    return new_val[0];
}
