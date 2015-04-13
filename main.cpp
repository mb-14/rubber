#include "util.h"
#include "game.h"

using namespace std;
const int window_width = 1000;
const int window_height = 500;
const int update_interval =0;
Game* game;
void update(int value);
void draw();
void draw_pipe(int);
void enable2D(int width, int height);
void user_input(unsigned char,int, int);
void loadTextures();
GLuint loadTexture(const char * filename,int width, int height);
GLuint background,rubber,pipe,ground;
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width,window_height);
    glutCreateWindow("Rubber");
    glutDisplayFunc(draw);
    glutTimerFunc(update_interval, update, 0);
    glutKeyboardFunc(user_input);
    glEnable( GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    // setup scene to 2d mode and set draw color to white
    enable2D(window_width, window_height);
    glColor3f(1.0f, 1.0f, 1.0f);
    game = new Game();
    game->newGame();
    loadTextures();
    // start the whole thing
    glutMainLoop();
    
    return 0;
}

void loadTextures(){
	background = loadTexture("res/background.bmp",349,388);
    rubber = loadTexture("res/rubber.bmp",50,50);
    pipe = loadTexture("res/pipe.bmp",138,793);
    ground = loadTexture("res/ground.bmp",336,112);  
}

void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}


void draw() {
    // clear (has to be done at the beginning)
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   
    glBindTexture(GL_TEXTURE_2D, background);  
   glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.0); glVertex2f(0,112);
      glTexCoord2f(2.86, 0.0); glVertex2f(window_width,112);
      glTexCoord2f(2.86, 1.0); glVertex2f(window_width,window_height);
      glTexCoord2f(0.0, 1.0); glVertex2f(0,window_height);
   glEnd();
   
  glBindTexture(GL_TEXTURE_2D, ground);  
   glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.0); glVertex2f(game->x1,0);
      glTexCoord2f(1.0, 0.0); glVertex2f(window_width+game->x1,0);
      glTexCoord2f(1.0, 1.0); glVertex2f(window_width+game->x1,112);
      glTexCoord2f(0.0, 1.0); glVertex2f(game->x1,112);
   glEnd();
   
 
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.0); glVertex2f(game->x2,0);
      glTexCoord2f(1.0, 0.0); glVertex2f(window_width+game->x2,0);
      glTexCoord2f(1.0, 1.0); glVertex2f(window_width+game->x2,112);
      glTexCoord2f(0.0, 1.0); glVertex2f(game->x2,112);
   glEnd();
   
  
  for(int i=0;i<3;i++)
  	draw_pipe(i);
  glBindTexture(GL_TEXTURE_2D,0);
  printText(490,450,1.0f,1.0f,1.0f,2,to_string(game->score).c_str());
  
 glBindTexture(GL_TEXTURE_2D, rubber); 
  glPushMatrix();
  glTranslatef(100, 137+game->y, 0);
  glRotatef(game->angle, 0, 0, 1);     
	glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.0); glVertex2f(-25,-25);
      glTexCoord2f(1.0, 0.0); glVertex2f(25,-25);
      glTexCoord2f(1.0, 1.0); glVertex2f(25,25);
      glTexCoord2f(0.0, 1.0); glVertex2f(-25,25);
   glEnd();
  glPopMatrix();
  
  if(game->gameOver){
  	 glBindTexture(GL_TEXTURE_2D,0);
  printText(350,350,1.0f,1.0f,1.0f,3,"GAME OVER");
  if(game->score >= game->highscore){
  printText(410,320,1.0f,1.0f,1.0f,1.2,("High Score: "+to_string(game->score)).c_str());
  game->highscore = game->score;
  game->saveHighScore();
  }
  else{
  printText(410,320,1.0f,1.0f,1.0f,1.2,("High Score: "+to_string(game->highscore)).c_str());
  }
  printText(330,290,1.0f,1.0f,1.0f,1.2,"Press space to start a new game");
  
  }
    // swap buffers (has to be done at the end)
    glutSwapBuffers();
    if(!game->gameOver)
    	game->update();
	 
}


void draw_pipe(int i){
	 glBindTexture(GL_TEXTURE_2D, pipe);
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.71); glVertex2f(game->pipe_x[i],112);
      glTexCoord2f(1.0, 0.71); glVertex2f(40+game->pipe_x[i],112);
      glTexCoord2f(1.0, 1.0); glVertex2f(40+game->pipe_x[i],189);
      glTexCoord2f(0.0, 1.0); glVertex2f(game->pipe_x[i],189);
   glEnd();
}

void update(int value) {
    // Call update() again in 'interval' milliseconds
    glutPostRedisplay();
    glutTimerFunc(update_interval, update, 0);
  
    // Redisplay frame
    
}

void user_input(unsigned char key, int x, int y) {
	if(key==' '){
	if(game->gameOver)
		game->newGame();
	else	
		game->jump=true;
	}

}


