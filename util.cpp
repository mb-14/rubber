#include "util.h"

using namespace std;

GLuint loadTexture( const char * filename,int width,int height){
  GLuint texture;
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
  if ( file == NULL ) {
  cout<<"error";
  return 0;
  };
  fseek ( file , 56 , SEEK_SET );
  data = (unsigned char *)malloc( width * height * 4 );
  fread( data, width * height * 4, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*4;
   unsigned char B,R;
   B = data[index+1];
   R = data[index+3];
   data[index+1] = R;
   data[index+3] = B;

}
glGenTextures(1, &texture );
glBindTexture(GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,GL_RGBA, GL_UNSIGNED_BYTE, data );
free(data);

return texture;
}

void printText(int x, int y, float r, float g, float b, float size, const char *text)
{
  
  glLineWidth(2.0f*size);
  int len, i;
  len = (int)strlen(text);
  //Draw shadow
  glPushMatrix();
  glTranslatef(x+2, y-2, 0);
  glScalef(0.15f*size, 0.15f*size, 0.15*size);
  glColor3f(0.1f,0.1f,0.1f);
   for (i = 0; i < len; i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
  }
  glPopMatrix();
  
  
  glPushMatrix();
  glTranslatef(x, y, 0);
   glScalef(0.15*size, 0.15*size, 0.15*size);
  glColor3f( r, g, b );
  for (i = 0; i < len; i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
  }
  glPopMatrix();
 
  
}



ALuint source[3];
ALint source_state[3];

void soundInit(int argc, char **argv){
 		alutInit(0, NULL);
    // Capture errors
    alGetError();
		alGenSources(3, source);
	}


ALuint loadWAV(const char* filename){
	ALuint buffer = alutCreateBufferFromFile(filename);
	return buffer;
}



void playWAVTask(ALuint buffer, int index){
	alSourcei(source[index], AL_BUFFER, buffer);
	alSourcePlay(source[index]);
	alGetSourcei(source[index], AL_SOURCE_STATE, &source_state[index]);

	while (source_state[index] == AL_PLAYING) {
		alGetSourcei(source[index], AL_SOURCE_STATE, &source_state[index]);
	}
}

void playWAV(ALuint buffer, int index){
  thread(playWAVTask, buffer, index).detach();
}
