#ifndef UTIL_H    
#define UTIL_H
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include<cstdio>
#include<string.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <thread>
GLuint loadTexture(const char * filename,int width,int height);
void printText(int x, int y, float r, float g, float b,float size, const char *text);
void soundInit(int argc, char **argv);
ALuint loadWAV(const char* filename);
void playWAV(ALuint buffer,int index);
#endif 
