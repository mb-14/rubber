#ifndef UTIL_H    
#define UTIL_H
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include<cstdio>
#include<string.h>

GLuint loadTexture(const char * filename,int width,int height);
void printText(int x, int y, float r, float g, float b,float size, const char *text);
#endif 
