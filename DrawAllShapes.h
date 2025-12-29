#pragma once
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>
//#include <stb_image.h>
#include <iostream>




class DrawShapes
{
public:
    static void drawFloor(GLuint texture);
    static void drawHouse(GLuint texture);
    static void DrawDoor(GLuint doorTex);
    static void drawMountains(GLuint mountainTex);
    
};

